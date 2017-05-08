module GaussianMixtureRegressors

# http://cs229.stanford.edu/section/more_on_gaussians.pdf
# http://pypr.sourceforge.net/mog.html

using AutomotiveDrivingModels
using GaussianMixtures
using Distributions
using PyCall

@pyimport sklearn.mixture as mixture

import AutomotiveDrivingModels:
    AbstractVehicleBehavior,
    AbstractVehicleBehaviorPreallocatedData,
    AbstractVehicleBehaviorTrainParams,

    preallocate_learning_data,
    select_action,
    calc_action_loglikelihood,
    train,
    observe

export
    GMRBehavior,
    GMR_TrainParams,

    select_action,
    calc_action_loglikelihood,
    train

const DEFAULT_MIN_EIGENVALUE = 1e-6

function ensure_posdef!(Σ::Matrix{Float64}, min_eigenvalue::Float64)

    @assert(size(Σ, 1) == size(Σ, 2))

    Λ, V = eig(Σ)
    for (j,λ) in enumerate(Λ)
        Λ[j] = max(DEFAULT_MIN_EIGENVALUE, λ)
    end
    Σ[:] = V*diagm(Λ)/V

    Σ
end

type GMR_TrainParams <: AbstractVehicleBehaviorTrainParams

    targets::ModelTargets
    indicators::Union{Vector{AbstractFeature},Vector{FeaturesNew.AbstractFeature}}

    n_components::Int
    max_n_indicators::Int
    n_PCA_features::Int # 0 means do not use PCA features, otherwise it is the number of PCA features to use
    fraction_test::Float64
    min_covar::Float64

    function GMR_TrainParams(;
        targets::ModelTargets = ModelTargets{AbstractFeature}(FUTUREDESIREDANGLE_250MS, FUTUREACCELERATION_250MS),
        indicators::Union{Vector{AbstractFeature}, Vector{FeaturesNew.AbstractFeature}} = [
                            POSFY, YAW, SPEED, DELTA_SPEED_LIMIT, VELFX, VELFY, SCENEVELFX, TURNRATE,
                            D_CL, D_ML, D_MR, TIMETOCROSSING_LEFT, TIMETOCROSSING_RIGHT,
                            N_LANE_L, N_LANE_R, HAS_LANE_L, HAS_LANE_R, ACC, ACCFX, ACCFY,
                            A_REQ_STAYINLANE,
                            HAS_FRONT, D_X_FRONT, D_Y_FRONT, V_X_FRONT, V_Y_FRONT, TTC_X_FRONT,
                            A_REQ_FRONT, TIMEGAP_X_FRONT,
                         ],
        n_components::Integer=2,
        max_n_indicators::Integer=3,
        n_PCA_features::Integer=0,
        fraction_test::Real = 0.1,
        min_covar::Real = 0.001,
        )

        if eltype(indicators) <: FeaturesNew.AbstractFeature
            targets = ModelTargets{FeaturesNew.AbstractFeature}(
                            FeaturesNew.FUTUREDESIREDANGLE,
                            FeaturesNew.FUTUREACCELERATION)
        end

        retval = new()

        retval.targets = targets
        retval.indicators = indicators
        retval.n_components = n_components
        retval.max_n_indicators = max_n_indicators
        retval.n_PCA_features = n_PCA_features
        retval.fraction_test = fraction_test
        retval.min_covar = min_covar

        retval
    end
end
function Base.print(io::IO, θ::GMR_TrainParams)
    println(io, "GMR Train Params")
    println(io, "\ttargets: ", θ.targets)
    println(io, "\tindicators: ", map(f->symbol(f), θ.indicators))
    println(io, "\tn_components:     ", θ.n_components)
    println(io, "\tmax_n_indicators: ", θ.max_n_indicators)
    println(io, "\tn_PCA_features:   ", θ.n_PCA_features)
    println(io, "\tmin_covar:        ", θ.min_covar)
end

type GMR_PreallocatedData <: AbstractVehicleBehaviorPreallocatedData

    YX::Matrix{Float64} # [2+p × nframes]
                        # this includes both targets as 1st two columns (lat, lon)
                        # and then the predictors

    extractor::FeaturesNew.FeatureSubsetExtractor
    preprocess::FeaturesNew.DataPreprocessor
    preprocess_target::FeaturesNew.DataPreprocessor

    function GMR_PreallocatedData(dset::ModelTrainingData2, params::GMR_TrainParams)

        retval = new()

        targets = params.targets
        indicators = params.indicators
        trainingframes = dset.dataframe
        nframes = nrow(trainingframes)
        nindicators = length(indicators)


        X = Array(Float64, nindicators, nframes)
        Y = Array(Float64, 2, nframes)

        pull_design_and_target_matrices!(X, Y, trainingframes, targets, indicators)

        ###########################

        preprocess_target = FeaturesNew.ChainedDataProcessor(2)
        push!(preprocess_target, Y, FeaturesNew.DataClamper)
        FeaturesNew.process!(Y, preprocess_target.processors[end]) # process in place
        # push!(preprocess_target, Y, FeaturesNew.DataScaler) # ensure data is standardized before running PCA
        # FeaturesNew.process!(Y, preprocess_target.processors[end]) # process in place

        @assert(findfirst(v->isnan(v), Y) == 0)
        @assert(findfirst(v->isinf(v), Y) == 0)

        extractor = FeaturesNew.FeatureSubsetExtractor(Array(Float64, nindicators), indicators)
        preprocess = FeaturesNew.ChainedDataProcessor(extractor)
        push!(preprocess, X, FeaturesNew.DataNaReplacer, extractor.indicators)
        FeaturesNew.process!(X, preprocess.processors[end]) # process in place

        @assert(findfirst(v->isnan(v), X) == 0)
        @assert(findfirst(v->isinf(v), X) == 0)

        push!(preprocess, X, FeaturesNew.DataClamper)
        FeaturesNew.process!(X, preprocess.processors[end]) # process in place
        push!(preprocess, X, FeaturesNew.DataScaler) # ensure data is standardized before running PCA
        FeaturesNew.process!(X, preprocess.processors[end]) # process in place

        if params.n_PCA_features > 0
            # Add a PCA scaler
            push!(preprocess, X, FeaturesNew.DataLinearTransform, params.n_PCA_features)

            Z = Array(Float64, params.n_PCA_features, nframes)
            Z = FeaturesNew.process!(Z, X, preprocess.processors[end])

            retval.YX = vcat(Y, Z)
        else
            retval.YX = vcat(Y, X)
        end

        retval.extractor = extractor
        retval.preprocess = preprocess
        retval.preprocess_target = preprocess_target

        retval
    end
end

type GMRBehavior <: AbstractVehicleBehavior

    #=
    The GMR behavior does Gaussian Mixture Regression

    1 - fit a joint GMM over (lat,lon,p₁,p₁,...,pₙ)

        pdf({a,P}) = pdf(x) = ∑ wⱼ N(μⱼ,Σⱼ)

    2 - convert to a conditional: (lat,lon | p₁,p₁,...,pₙ)

        pdf(a|P) = ∑ βⱼ(p) N(μⱼ_ₚ, Σⱼ_ₚ)

            μⱼ_ₚ = μₐ + Σₐₚ/Σₚₚ (p - μₚ)
            Σⱼ_ₚ = Σₐₐ - (Σₐₚ/Σₚₚ)Σₚₐ
            βⱼ(p) ∝ wⱼ N(μₚ, Σₚₚ)
    =#

    targets::ModelTargets{FeaturesNew.AbstractFeature}
    extractor::FeaturesNew.FeatureSubsetExtractor # - note that the extractor and processor are linked internally
    processor::FeaturesNew.DataPreprocessor
    processor_target::FeaturesNew.DataPreprocessor

    # μ₁₋₂ = μ₁ + Σ₁₂ * Σ₂₂⁻¹ * (x₂ - μ₂) = A*x₂ + b
    vec_A::Vector{Matrix{Float64}} # [n_components [2×nindicators]]
    vec_b::Vector{Vector{Float64}} # [n_components [2]]

    # pdf(a|p), means μⱼ_ₚ and weights βⱼ(p) are functions of p and must be updated every time, covariance is constant
    mixture_Act_given_Obs::MixtureModel{Multivariate,Continuous,MvNormal}

    # pdf(p), all pre-computed. Used to compute βⱼ(p)
    mixture_Obs::MixtureModel{Multivariate,Continuous,MvNormal} # p(obs), all pre-computed, should never be edited

    GMRBehavior() = new() # dummy constructor
    function GMRBehavior(
        gmm::PyObject,
        targets::ModelTargets{FeaturesNew.AbstractFeature},
        chosen_indicators::Vector{Int},
        extractor::FeaturesNew.FeatureSubsetExtractor,
        processor::FeaturesNew.ChainedDataProcessor,
        processor_target::FeaturesNew.ChainedDataProcessor,
        )

        weights = gmm[:weights_]::Vector{Float64} # [n_components]
        means = gmm[:means_]::Matrix{Float64} # [n_components, n_features]
        covars = gmm[:covars_]::Array{Float64, 3} # shape depends on covariance_type
        @assert(gmm[:covariance_type] == "full")
        # (n_components, n_features)             if 'spherical',
        # (n_features, n_features)               if 'tied',
        # (n_components, n_features)             if 'diag',
        # (n_components, n_features, n_features) if 'full'

        n_targets = 2
        n_indicators = size(means, 2) - n_targets
        n_components = length(weights)
        indicators = extractor.indicators[chosen_indicators]
        @assert(length(chosen_indicators) == n_indicators)

        vec_A = Array(Matrix{Float64}, n_components) # μ₁₋₂ = μ₁ + Σ₁₂ * Σ₂₂⁻¹ * (x₂ - μ₂) = A*x₂ + b
        vec_b = Array(Vector{Float64}, n_components)
        vec_G = Array(MvNormal, n_components)
        vec_H = Array(MvNormal, n_components)

        for i = 1 : n_components

            μₐ = vec(means[i,1:n_targets])
            μₚ = vec(means[i,n_targets+1:end])

            Σ = reshape(covars[i, :, :], (n_targets + n_indicators,n_targets + n_indicators))

            Σₐₐ = Σ[1:n_targets,1:n_targets]
            Σₐₚ = Σ[1:n_targets,n_targets+1:end]
            Σₚₚ = Σ[n_targets+1:end,n_targets+1:end]
            iΣₚₚ = inv(Σₚₚ)

            A = Σₐₚ * iΣₚₚ
            vec_A[i] = A
            vec_b[i] = vec(μₐ - A*μₚ)
            C = Σₐₐ - Σₐₚ * iΣₚₚ * ((Σₐₚ)')

            vec_G[i] = MvNormal(Array(Float64, n_targets), C) # p(action|obs), mean and weighting must be updated with each observation, cov is pre-computed
            vec_H[i] = MvNormal(μₚ, Σₚₚ) # p(obs), all pre-computed, should never be edited
        end

        retval = new()

        retval.targets = targets
        retval.extractor = FeaturesNew.FeatureSubsetExtractor(deepcopy(extractor.indicators))

        retval.processor = deepcopy(processor, retval.extractor)
        push!(retval.processor, DataSubset, chosen_indicators)

        retval.processor_target = deepcopy(processor_target)

        retval.vec_A = vec_A
        retval.vec_b = vec_b

        retval.mixture_Act_given_Obs = MixtureModel(vec_G, fill(1/n_components, n_components)) # p(action|obs), mean and weighting must be updated with each observation, cov is pre-computed
        retval.mixture_Obs = MixtureModel(vec_H, weights) # p(obs), all pre-computed, should never be edited

        retval
    end
    function GMRBehavior(
        gmm::PyObject,
        targets::ModelTargets{FeaturesNew.AbstractFeature},
        chosen_indicators::Vector{Int},
        preallocated_data::GMR_PreallocatedData,
        )

        GMRBehavior(gmm, targets, chosen_indicators,
                    preallocated_data.extractor,
                    preallocated_data.preprocess,
                    preallocated_data.preprocess_target)
    end
end
function Base.print(io::IO, GM::GMRBehavior)

    num_components = ncomponents(GM.mixture_Obs)
    n_indicators = length(GM.processor.z)

    println(io, "Gaussian Mixture Regression Model")
    println(io, "\ttargets: ", GM.targets)
    println(io, "\tncomponents: ", num_components)
    println(io, "\tpdf(p)")
    for i in 1 : num_components
        w = GM.mixture_Obs.prior.p[i]
        μ = GM.mixture_Obs.components[i].μ
        Σ = GM.mixture_Obs.components[i].Σ

        for j in 1 : n_indicators
            if j != n_indicators
                @printf(io, "\t                       [%10.6f]      [", μ[j])
                for k in 1 : n_indicators
                    @printf(io, "%10.6f", Σ.mat[j,k])
                    if k != n_indicators
                        print(io, "  ")
                    end
                end
                println(io, "]")
            else
                @printf(io, "\t%2d: w = %10.6f μ = [%10.6f]  Σ = [", i, w, μ[j])
                for k in 1 : n_indicators
                    @printf(io, "%10.6f", Σ.mat[j,k])
                    if k != n_indicators
                        print(io, "  ")
                    end
                end
                println(io, "]")
            end
        end
    end
    println(io, "\tpdf(a|p)")
    for i in 1 : num_components
        A = GM.vec_A[i]
        b = GM.vec_b[i]
        Σ = GM.mixture_Act_given_Obs.components[i].Σ
        @printf(io, "\t        [%10.6f]     [%10.6f]      [%10.6f  %10.6f]\n", A[1,1], b[1], Σ.mat[1,1], Σ.mat[1,2])
        @printf(io, "\t%2d: A = [%10.6f] b = [%10.6f]  Σ = [%10.6f  %10.6f]\n", i, A[2,1], b[2], Σ.mat[2,1], Σ.mat[2,2])
    end
end

function preallocate_learning_data(
    dset::ModelTrainingData,
    params::GMR_TrainParams)

    GMR_PreallocatedData(dset, params)
end
function preallocate_learning_data(
    dset::ModelTrainingData2,
    params::GMR_TrainParams)

    GMR_PreallocatedData(dset, params)
end


const TOLERANCE_ZERO_PROB_WEIGHT = 1e-20

function select_action(
    behavior::GMRBehavior,
    runlog::RunLog,
    sn::StreetNetwork,
    colset::UInt,
    frame::Int
    )

    FeaturesNew.observe!(behavior.extractor, runlog, sn, colset, frame)
    FeaturesNew.process!(behavior.processor)

    # condition on the mixture
    n_components = length(behavior.vec_A)
    mixture_Obs = behavior.mixture_Obs
    mixture_Act_given_Obs = behavior.mixture_Act_given_Obs

    total_prior_sum = 0.0
    for i = 1 : n_components
        mixture_Act_given_Obs.prior.p[i] = mixture_Obs.prior.p[i] * pdf(mixture_Obs.components[i], behavior.processor.z)
        total_prior_sum += mixture_Act_given_Obs.prior.p[i]
    end
    if abs(total_prior_sum) < TOLERANCE_ZERO_PROB_WEIGHT
        return (0.0,0.0)
    end

    for i = 1 : n_components
        mixture_Act_given_Obs.prior.p[i] /= total_prior_sum
    end
    @assert(!isnan(mixture_Act_given_Obs.prior.p[1]))


    # pick a component to sample from
    component_index = rand(mixture_Act_given_Obs.prior)
    component = mixture_Act_given_Obs.components[component_index]

    # modify said component with observation
    component.μ[:] = behavior.vec_b[component_index] + behavior.vec_A[component_index]*behavior.processor.z

    # sample from said component
    Distributions._rand!(component, behavior.processor_target.x)
    FeaturesNew.process!(behavior.processor_target)

    # # reverse the scaling
    # scale_index = findfirst(dp->isa(dp, DataScaler), behavior.processor_target.processors)
    # scaler = behavior.processor_target.processors[scale_index]::DataScaler

    # copy!(scaler.x, behavior.processor_target.z)
    # FeaturesNew.reverse(scaler)
    # copy!(behavior.processor_target.z, scaler.x)

    # return the selected action
    action_lat = behavior.processor_target.z[1]
    action_lon = behavior.processor_target.z[2]

    (action_lat, action_lon)
end

function _set_and_process_action!(behavior::GMRBehavior, action_lat::Float64, action_lon::Float64)
    behavior.processor_target.x[1] = action_lat
    behavior.processor_target.x[2] = action_lon
    FeaturesNew.process!(behavior.processor_target)
    behavior.processor_target
end
function _calc_action_loglikelihood(behavior::GMRBehavior)

    # NOTE(tim): this assumes that:
    #   - observations have already been pulled and are in behavior.processor.z
    #   - action_lat and action_lon are already processed and in behavior.processor_target.z

    mixture_Act_given_Obs = behavior.mixture_Act_given_Obs
    mixture_Obs = behavior.mixture_Obs
    n_components = length(mixture_Obs.components)

    a = behavior.processor_target.z
    f = behavior.processor.z

    for j in 1 : n_components

        # compute the β value, unweighted
        # βⱼ(f) ∝ wⱼ Nⱼ(μₚ, Σₚ)
        wⱼ = mixture_Obs.prior.p[j]
        Nⱼ = mixture_Obs.components[j]
        mixture_Act_given_Obs.prior.p[j] = wⱼ * pdf(Nⱼ, f)

        # compute the conditional mean
        #  μₐ_ₚ = A⋅f + b
        A = behavior.vec_A[j]
        b = behavior.vec_b[j]
        mixture_Act_given_Obs.components[j].μ[:] = A*f + b
    end

    # normalize the β values
    sum_β = sum(mixture_Act_given_Obs.prior.p)
    mixture_Act_given_Obs.prior.p[:] = mixture_Act_given_Obs.prior.p ./ sum_β

    if findfirst(v->isinf(v), mixture_Act_given_Obs.prior.p) != 0 || findfirst(v->isnan(v), mixture_Act_given_Obs.prior.p) != 0

        @printf("j  %10s  %10s\n", "wⱼ", "pdf(Nⱼ, f)")
        for j in 1 : n_components
            wⱼ = mixture_Obs.prior.p[j]
            Nⱼ = mixture_Obs.components[j]
            @printf("%2d  %10.6f  %10.6f\n", j, wⱼ, pdf(Nⱼ, f))
        end
        # sleep(100)

        println("INF1: ")
        println("\t a|p prior:  ", mixture_Act_given_Obs.prior.p)
        println("\t sum_β:      ", sum_β)
        println("\t indicators: ", f)
        println("\t targets:    ",    a)

        sleep(0.01)

        return -Inf
    end

    # compute logl using the built-in mixture
    logl = logpdf(mixture_Act_given_Obs, a)

    if isinf(logl) || isnan(logl)
        println(mixture_Act_given_Obs.prior.p)
        println(sum_β)
        println("INF2: obs: ", f, "  action: ",  a)
        sleep(0.01)
    end

    logl
end

function calc_action_loglikelihood(
    behavior::GMRBehavior,
    runlog::RunLog,
    sn::StreetNetwork,
    colset::UInt,
    frame::Int,
    action_lat::Float64,
    action_lon::Float64,
    )

    #=
    Compute the log-likelihood of the action taken during a single frame
    given the VehicleBehaviorGaussian.
    =#

    FeaturesNew.observe!(behavior.extractor, runlog, sn, colset, frame)
    FeaturesNew.process!(behavior.processor)

    _set_and_process_action!(behavior, action_lat, action_lon)

    _calc_action_loglikelihood(behavior)
end
function calc_action_loglikelihood(
    behavior::GMRBehavior,
    features::DataFrame,
    frameind::Integer,
    )

    FeaturesNew.observe!(behavior.extractor, features, frameind)
    FeaturesNew.process!(behavior.processor)

    action_lat = features[frameind, symbol(behavior.targets.lat)]::Float64
    action_lon = features[frameind, symbol(behavior.targets.lon)]::Float64
    _set_and_process_action!(behavior, action_lat, action_lon)

    _calc_action_loglikelihood(behavior)
end

function _greedy_select_next_indicator(
    YX_orig::Matrix{Float64}, # [m, 2+p], the original dataset
    targets::ModelTargets{FeaturesNew.AbstractFeature},
    indicators::Vector{FeaturesNew.AbstractFeature}, # all indicators (TODO: get rid of this)
    chosen_indicators::Vector{Int}, # indeces of chosen indicators
    gmm::PyObject,
    current_model::GMRBehavior,
    current_model_logl::Float64,
    assign_test::BitVector, # if true, item is in <test>, and otherwise is in <train>
    preallocated_data::GMR_PreallocatedData,
    )

    m = size(YX_orig, 1)
    p = size(YX_orig, 2) - 2
    n = length(assign_test) - sum(assign_test)
    I = length(chosen_indicators)
    YX = Array(Float64, n, 2 + I + 1)

    @assert(findfirst(v->isnan(v), YX_orig) == 0)
    @assert(findfirst(v->isinf(v), YX_orig) == 0)

    # copy data into YX
    j = 0
    for i in 1 : m
        if !assign_test[i]
            j += 1
            YX[j, 1] = YX_orig[i, 1]
            YX[j, 2] = YX_orig[i, 2]
            YX[j, 2+I+1] = 0.0 # set to zero for now
            for (x,y) in enumerate(chosen_indicators)
                YX[j, 2+x] = YX_orig[i, y]
            end
        end
    end

    @assert(j == n)
    @assert(findfirst(v->isnan(v), YX) == 0)
    @assert(findfirst(v->isinf(v), YX) == 0)

    println("passed!"); sleep(0.01)

    train_indicator_indeces = [chosen_indicators; typemax(Int)]

    # Try all possible next features
    # TODO(tim): parallelize?

    something_converged = false
    something_chosen = false

    for y in 1 : p
        if !in(y, chosen_indicators)

            # select indicator
            train_indicator_indeces[end] = y

            # copy in the chosen indicator columns
            j = 0
            for i in 1 : m
                if assign_test[i]
                    j += 1
                    YX[j, 2+I+1] = YX_orig[i, y+2]
                end
            end

            # fit a model
            gmm[:fit](YX)
            if !gmm[:converged_]
                println(symbol(indicators[y]), "did not converge")
                continue
            end

            something_converged = true
            behavior = GMRBehavior(gmm, targets, train_indicator_indeces, preallocated_data)

            # compute test logl
            logl = 0.0
            for i in 1 : m
                if assign_test[i]

                    behavior.processor_target.z[1] = YX_orig[i, 1] # lat, already processed
                    behavior.processor_target.z[2] = YX_orig[i, 2] # lon, already processed

                    for (i,y₂) in enumerate(train_indicator_indeces)
                        behavior.processor.z[i] = YX_orig[i, y₂+2] # feature, already processed
                    end

                    logl += _calc_action_loglikelihood(behavior)

                    # count += 1
                    # if count < 20
                    #     @printf("YX test: %12.6f  %12.6f  ", YX_orig[i, 1], YX_orig[i, 2])
                    #     for (i,j) in enumerate(train_indicator_indeces)
                    #         @printf("%12.6f  ", YX_orig[i, j+2])
                    #     end
                    #     println(_calc_action_loglikelihood(behavior))
                    # end
                end
            end
            @printf("%25s %10.6f\n", string(symbol(indicators[y]))*":", logl)

            # check if it is beter
            if logl > current_model_logl
                current_model_logl = logl
                current_model = behavior

                @assert(!in(chosen_indicators, y))
                chosen_indicators = copy(train_indicator_indeces)

                something_chosen = true
            end
        end
    end

    if !something_converged
        println("NOTHING CONVERGED")
    end
    if !something_chosen
        println("NOTHING CHOSEN")
    end

    # println("chosen_indicators: ", indicators[chosen_indicators])
    # println("current_model_logl: ", current_model_logl)

    (chosen_indicators, current_model_logl, current_model)
end

function train(
    training_data::ModelTrainingData2,
    preallocated_data::GMR_PreallocatedData,
    params::GMR_TrainParams,
    fold::Int,
    fold_assignment::FoldAssignment,
    match_fold::Bool,
    )

    targets = params.targets
    indicators = params.indicators
    max_n_indicators = params.max_n_indicators

    target_lat = targets.lat
    target_lon = targets.lon
    @assert(!in(target_lat, indicators))
    @assert(!in(target_lon, indicators))

    trainingframes = training_data.dataframe_nona
    nframes = size(trainingframes, 1)
    features = append!([target_lat, target_lon], indicators)

    # [nframes × 2+p]
    YX = copy_matrix_fold(preallocated_data.YX, fold, fold_assignment, match_fold)

    @assert(findfirst(v->isnan(v), YX) == 0)
    @assert(findfirst(v->isinf(v), YX) == 0)

    # -------------------------------------------------------------
    # Allocate the GMM

    n_components = params.n_components # int, optional. Number of mixture components. Defaults to 1.
    covariance_type = "full" # string, optional. ‘spherical’, ‘tied’, ‘diag’, ‘full’. Defaults to ‘diag’.
    random_state = 1 # RandomState or an int seed (None by default)
    min_covar = params.min_covar # float, optional

    gmm = mixture.GMM(n_components=n_components, covariance_type=covariance_type,
                      random_state=random_state, min_covar=min_covar, n_iter=1000)

    # -------------------------------------------------------------
    # Assign a train/test split

    prev_logl = -Inf
    assign_test = falses(size(YX, 1))
    fraction_test = params.fraction_test # amount of points to use for test
    for i = 1 : size(YX, 1)
        assign_test[i] = rand() < fraction_test
    end

    # -------------------------------------------------------------
    # Optimize the model

    chosen_indicators, current_model_logl, current_model = _greedy_select_next_indicator(
                YX, targets, indicators, Int[], gmm, GMRBehavior(),
                prev_logl, assign_test, preallocated_data)

    println("\nchosen_indicators: ", chosen_indicators, "  ", current_model_logl)

    while prev_logl < current_model_logl && length(chosen_indicators) < max_n_indicators
        prev_logl = current_model_logl
        chosen_indicators, current_model_logl, current_model = _greedy_select_next_indicator(
                                                        YX, targets, indicators, chosen_indicators, gmm,
                                                        current_model, prev_logl, assign_test, preallocated_data)
        println("chosen_indicators: ", chosen_indicators, "  ", current_model_logl)
    end
    @assert(!isinf(current_model_logl))

    println("n chosen indicators: ", length(chosen_indicators))
    println(map(f->symbol(f), indicators[chosen_indicators]))

    current_model
end

end # end module