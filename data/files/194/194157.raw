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

type GMRBehavior{F} <: AbstractVehicleBehavior

    targets::ModelTargets{F}
    indicators::Vector{F}
    extractor::FeaturesNew.FeatureSubsetExtractor
    processor::FeaturesNew.DataPreprocessor
    processor_target::FeaturesNew.DataPreprocessor

    vec_A::Vector{Matrix{Float64}} # [n_components [2×I]] μ₁₋₂ = μ₁ + Σ₁₂ * Σ₂₂⁻¹ * (x₂ - μ₂) = A*x₂ + b     (I is number of indicators)
    vec_b::Vector{Vector{Float64}} # [n_components [2]]

    mixture_Act_given_Obs::MixtureModel{Multivariate,Continuous,MvNormal} # p(action|obs), mean and weighting must be updated with each observation, cov is pre-computed
    mixture_Obs::MixtureModel{Multivariate,Continuous,MvNormal} # p(obs), all pre-computed, should never be edited

    GMRBehavior() = new() # dummy constructor
    function GMRBehavior(
        gmm::GMM{Float64},
        targets::ModelTargets{AbstractFeature},
        indicators::Vector{AbstractFeature},
        )

        #=
        INPUT: gmm::GMM, from fitting a Gaussian Mixture Model using GaussianMixtures.jl
                         on X = [m×[n_targets, n_indicators]] such that the targets are [lat,lon] in the first two components
        =#

        n_targets = 2
        n_indicators = gmm.d - n_targets
        n_components = gmm.n
        @assert(length(indicators) == n_indicators)
        @assert(!in(FUTUREDESIREDANGLE_250MS, indicators))
        @assert(!in(FUTUREACCELERATION_250MS, indicators))

        vec_A = Array(Matrix{Float64}, n_components) # μ₁₋₂ = μ₁ + Σ₁₂ * Σ₂₂⁻¹ * (x₂ - μ₂) = A*x₂ + b
        vec_b = Array(Vector{Float64}, n_components)
        vec_G = Array(MvNormal, n_components)
        vec_H = Array(MvNormal, n_components)

        for i = 1 : n_components
            # println(typeof(gmm.μ))
            # println(i, "  ", n_components, "  ", size(gmm.μ))
            μ₁ = vec(gmm.μ[i,1:n_targets])
            μ₂ = vec(gmm.μ[i,n_targets+1:end])

            # # NOTE: gmm.Σ stores a list of chol(inv(Σ), Val{:U})
            # Ui = gmm.Σ[i] # upper triangular matrix such that inv(Σ) = U'*U
            # U = inv(Ui) # upper triangular matrix such that Σ = U*U'

            # Σ = Symmetric(U*U')
            # Σ₁₁ = Σ[1:2, 1:2]
            # Σ₁₂ = Σ[1:2,2+1:end] # a full matrix
            # Σ₂₂ = Symmetric(Σ[2+1:end,2+1:end])
            # iΣ₂₂ = inv(Σ₂₂)::Symmetric

            # A = (Σ₁₂ * iΣ₂₂)::Matrix{Float64}
            # vec_A[i] = A
            # vec_b[i] = vec(μ₁ - A*μ₂)
            # C = Symmetric(Σ₁₁ - Σ₁₂ * iΣ₂₂ * (Σ₁₂'))

            # vec_G[i] = MvNormal(Array(Float64, n_targets), full(C)) # p(action|obs), mean and weighting must be updated with each observation, cov is pre-computed
            # vec_H[i] = MvNormal(μ₂, full(Σ₂₂)) # p(obs), all pre-computed, should never be edited

            Σ = GaussianMixtures.covar(gmm.Σ[i])

            # ensure it is PosDef by a small margin
            ensure_posdef!(Σ, DEFAULT_MIN_EIGENVALUE)

            Σ₁₁ = Σ[1:n_targets,1:n_targets]
            Σ₁₂ = Σ[1:n_targets,n_targets+1:end]
            Σ₂₂ = Σ[n_targets+1:end,n_targets+1:end]
            iΣ₂₂ = inv(Σ₂₂)

            A = Σ₁₂ * iΣ₂₂
            vec_A[i] = A
            vec_b[i] = vec(μ₁ - A*μ₂)
            C = Σ₁₁ - Σ₁₂ * iΣ₂₂ * (Σ₁₂')

            try
                vec_G[i] = MvNormal(Array(Float64, n_targets), ensure_posdef!(C, DEFAULT_MIN_EIGENVALUE)) # p(action|obs), mean and weighting must be updated with each observation, cov is pre-computed
                vec_H[i] = MvNormal(μ₂, ensure_posdef!(Σ₂₂, DEFAULT_MIN_EIGENVALUE)) # p(obs), all pre-computed, should never be edited
            catch
                println("Σ:", eig(C)[1])
                println(Σ)

                println("C:", eig(C)[1])
                println(C)

                println("Σ₂₂:", eig(C)[1])
                println(Σ₂₂)

                error("uh-oh")
            end
        end

        retval = new()

        retval.targets = targets
        retval.indicators = indicators
        retval.processor = FeaturesNew.ChainedDataProcessor(retval.indicators)

        retval.preprocess_target = FeaturesNew.ChainedDataProcessor(2)

        retval.vec_A = vec_A
        retval.vec_b = vec_b

        retval.mixture_Act_given_Obs = MixtureModel(vec_G, fill(1/n_components, n_components)) # p(action|obs), mean and weighting must be updated with each observation, cov is pre-computed
        retval.mixture_Obs = MixtureModel(vec_H, gmm.w) # p(obs), all pre-computed, should never be edited

        retval
    end
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
        @assert(!in(FUTUREDESIREDANGLE_250MS, indicators))
        @assert(!in(FUTUREACCELERATION_250MS, indicators))

        vec_A = Array(Matrix{Float64}, n_components) # μ₁₋₂ = μ₁ + Σ₁₂ * Σ₂₂⁻¹ * (x₂ - μ₂) = A*x₂ + b
        vec_b = Array(Vector{Float64}, n_components)
        vec_G = Array(MvNormal, n_components)
        vec_H = Array(MvNormal, n_components)

        for i = 1 : n_components

            μ₁ = vec(means[i,1:n_targets])
            μ₂ = vec(means[i,n_targets+1:end])

            Σ = reshape(covars[i, :, :], (n_targets + n_indicators,n_targets + n_indicators))

            Σ₁₁ = Σ[1:n_targets,1:n_targets]
            Σ₁₂ = Σ[1:n_targets,n_targets+1:end]
            Σ₂₂ = Σ[n_targets+1:end,n_targets+1:end]
            iΣ₂₂ = inv(Σ₂₂)

            A = Σ₁₂ * iΣ₂₂
            vec_A[i] = A
            vec_b[i] = vec(μ₁ - A*μ₂)
            C = Σ₁₁ - Σ₁₂ * iΣ₂₂ * (Σ₁₂')

            vec_G[i] = MvNormal(Array(Float64, n_targets), C) # p(action|obs), mean and weighting must be updated with each observation, cov is pre-computed
            vec_H[i] = MvNormal(μ₂, Σ₂₂) # p(obs), all pre-computed, should never be edited
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

type GMR_PreallocatedData <: AbstractVehicleBehaviorPreallocatedData

    YX::Matrix{Float64} # [2+p × nframes]
                        # this includes both targets as 1st two columns (lat, lon)
                        # and then the predictors

    extractor::FeaturesNew.FeatureSubsetExtractor
    preprocess::FeaturesNew.DataPreprocessor
    preprocess_target::FeaturesNew.DataPreprocessor

    function GMR_PreallocatedData(dset::ModelTrainingData, params::GMR_TrainParams)

        retval = new()

        nframes = size(dset.dataframe, 1)
        p = length(params.indicators)

        retval.YX = Array(Float64, 2 + p, nframes)

        retval
    end
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

        # println("\nORIGINAL")
        # for j in 1 : nindicators
        #     arr = X[j,:]
        #     lo, hi = extrema(arr)
        #     μ = mean(arr)
        #     σ = std(arr)
        #     @printf("%20s: %12.6f  %12.6f  %12.6f  %12.6f\n", string(symbol(indicators[j])), lo, hi, μ, σ)
        # end

        ###########################

        preprocess_target = FeaturesNew.ChainedDataProcessor(2)
        push!(preprocess_target, Y, FeaturesNew.DataClamper)
        FeaturesNew.process!(Y, preprocess_target.processors[end]) # process in place
        # push!(preprocess_target, Y, FeaturesNew.DataScaler) # ensure data is standardized before running PCA
        # FeaturesNew.process!(Y, preprocess_target.processors[end]) # process in place

        extractor = FeaturesNew.FeatureSubsetExtractor(Array(Float64, nindicators), indicators)
        preprocess = FeaturesNew.ChainedDataProcessor(extractor)
        push!(preprocess, X, FeaturesNew.DataNaReplacer, extractor.indicators)
        FeaturesNew.process!(X, preprocess.processors[end]) # process in place
        push!(preprocess, X, FeaturesNew.DataClamper, 3) # 5-sigma
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
    basics::FeatureExtractBasicsPdSet,
    behavior::GMRBehavior,
    carind::Int,
    validfind::Int
    )

    # pull observations
    Features.observe!(behavior.processor.x, basics, carind, validfind, behavior.indicators, replace_na=true)
    FeaturesNew.process!(behavior.processor)

    for i in 1 : length(behavior.processor.x)
        behavior.processor.x[i] = clamp(behavior.processor.x[i], -100.0, 100.0)
    end


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

    # return the selected action
    action_lat = behavior.processor_target.z[1]
    action_lon = behavior.processor_target.z[2]

    (action_lat, action_lon)
end
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

function _calc_action_loglikelihood(behavior::GMRBehavior)

    # NOTE(tim): this assumes that:
    #   - observations have already been pulled and are in behavior.processor.z
    #   - action_lat and action_lon are already processed and in behavior.processor_target.z

    mixture_Act_given_Obs = behavior.mixture_Act_given_Obs
    mixture_Obs = behavior.mixture_Obs
    n_components = length(mixture_Obs.components)

    # condition on the mixture
    total_prior_sum = 0.0
    for i = 1 : n_components

        # println(mixture_Obs.components[i])

        mixture_Act_given_Obs.prior.p[i] = mixture_Obs.prior.p[i] * pdf(mixture_Obs.components[i], behavior.processor.z)
        total_prior_sum += mixture_Act_given_Obs.prior.p[i]

        mixture_Act_given_Obs.components[i].μ[:] = behavior.vec_b[i] + behavior.vec_A[i]*behavior.processor.z
    end
    # if abs(total_prior_sum) < TOLERANCE_ZERO_PROB_WEIGHT
    if total_prior_sum == 0.0

        # println("indicators: ", map(i->symbol(i), behavior.indicators))
        # println("n_components: ", n_components)
        # println("action: ", behavior.a)
        # println("means:  ")
        # for i in 1 : n_components
        #     println("\t", mixture_Act_given_Obs.components[i].μ)
        # end
        # if length(mixture_Obs.components[1].μ) == 2
        #     println("obs means: ")
        #     for i in 1 : n_components
        #         for j = 1 : length(mixture_Obs.components[i].μ)
        #             @printf("\t[%8.3f] ± [%10.7f  %10.7f]  %10.7f\n", mixture_Obs.components[i].μ[j], mixture_Obs.components[i].Σ.mat[j,1],
        #                                                               mixture_Obs.components[i].Σ.mat[j,2], log(pdf(mixture_Obs.components[i], behavior.processor.z)))
        #         end
        #     end
        # end
        # println("obs: ", behavior.processor.z)
        # println("prior:  ", mixture_Act_given_Obs.prior.p)
        # mixture_Act_given_Obs.prior.p[:] ./= total_prior_sum
        # println("prob:   ", pdf(mixture_Act_given_Obs, behavior.a))
        # println("logl:   ", logpdf(mixture_Act_given_Obs, behavior.a))
        # println("  ")

        # sleep(100)

        println("INF1: ")
        println("\t indicators: ", behavior.processor.z)
        println("\t targets: ",    behavior.processor_target.z)

        return -Inf
    end
    for i = 1 : n_components
        mixture_Act_given_Obs.prior.p[i] /= total_prior_sum
    end

    # println("processor: ", behavior.processor.z)
    # println("target: ", behavior.processor_target)
    # println("x: ", behavior.processor_target.x)
    # println("z: ", behavior.processor_target.z)

    # println("n_components: ", n_components)
    # println("means:  ")
    # for i in 1 : n_components
    #     println("\t", mixture_Act_given_Obs.components[i].μ)
    # end
    # if length(mixture_Obs.components[1].μ) == 2
    #     println("obs means: ")
    #     for i in 1 : n_components
    #         for j = 1 : length(mixture_Obs.components[i].μ)
    #             @printf("\t[%8.3f] ± [%10.7f  %10.7f]  %10.7f\n", mixture_Obs.components[i].μ[j], mixture_Obs.components[i].Σ.mat[j,1],
    #                                                               mixture_Obs.components[i].Σ.mat[j,2], log(pdf(mixture_Obs.components[i], behavior.processor.z)))
    #         end
    #     end
    # end
    # println("prior:  ", mixture_Act_given_Obs.prior.p)
    # mixture_Act_given_Obs.prior.p[:] ./= total_prior_sum
    # println("prob:   ", pdf(mixture_Act_given_Obs, behavior.processor_target.z))
    # println("logl:   ", logpdf(mixture_Act_given_Obs, behavior.processor_target.z))
    # println("  ")

    # compute logl
    logl = logpdf(mixture_Act_given_Obs, behavior.processor_target.z)

    if isinf(logl)
        println("INF2: ", behavior.processor.z, "  action: ",  behavior.processor_target.z)
    end

    logl
end
function calc_action_loglikelihood(
    basics::FeatureExtractBasicsPdSet,
    behavior::GMRBehavior,
    carind::Int,
    validfind::Int,
    action_lat::Float64,
    action_lon::Float64
    )

    #=
    Compute the log-likelihood of the action taken during a single frame
    given the VehicleBehaviorGaussian.
    =#

    Features.observe!(behavior.processor.x, basics, carind, validfind, behavior.indicators, replace_na=true)
    FeaturesNew.process!(behavior.processor)

    for i in 1 : length(behavior.processor.x)
        behavior.processor.x[i] = clamp(behavior.processor.x[i], -100.0, 100.0)
    end

    behavior.processor_target.x[1] = action_lat
    behavior.processor_target.x[2] = action_lon
    FeaturesNew.process!(behavior.processor_target)

    _calc_action_loglikelihood(behavior)
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

    behavior.processor_target.x[1] = action_lat
    behavior.processor_target.x[2] = action_lon
    FeaturesNew.process!(behavior.processor_target)

    @printf("calc logl: (%8.3f, %8.3f) -> %12.6f\n", behavior.processor_target.z[1], behavior.processor_target.z[2], _calc_action_loglikelihood(behavior))

    _calc_action_loglikelihood(behavior)
end
function calc_action_loglikelihood(
    behavior::GMRBehavior,
    features::DataFrame,
    frameind::Integer,
    )

    behavior.processor_target.x[1] = features[frameind, symbol(behavior.targets.lat)]::Float64
    behavior.processor_target.x[2] = features[frameind, symbol(behavior.targets.lon)]::Float64
    FeaturesNew.process!(behavior.processor_target)

    FeaturesNew.observe!(behavior.extractor, features, frameind)
    FeaturesNew.process!(behavior.processor)

    # TODO(tim): remove this once we are done with Pdsets
    for i in 1 : length(behavior.processor.x)
        behavior.processor.x[i] = clamp(behavior.processor.x[i], -100.0, 100.0)
    end

    _calc_action_loglikelihood(behavior)
end

function _greedy_select_next_indicator(
    YX_orig::Matrix{Float64}, # [m, 2+I], the original dataset
    targets::ModelTargets{AbstractFeature},
    indicators::Vector{AbstractFeature}, # all indicators
    chosen_indicators::Vector{Int}, # indeces of chosen indicators
    gmm::PyObject,
    current_model::GMRBehavior,
    current_model_logl::Float64,
    assign_test::BitVector,
    preallocated_data::GMR_PreallocatedData,
    )

    m = size(YX_orig, 1)
    I = length(chosen_indicators)
    YX = Array(Float64, m, 2 + I + 1) # TODO(tim): preallocate?
    copy!(YX, 1, YX_orig, 1, 2m) # copy the first two columns - the 2 target features
    for (x,y) in enumerate(chosen_indicators)
        col_start_X = (2+x-1)*m + 1
        col_start_orig = (2+y-1)*m + 1
        copy!(YX, col_start_X, YX_orig, col_start_orig, m) # copy in the chosen indicator columns
    end

    train_indicators = indicators[chosen_indicators]
    push!(train_indicators, indicators[1])

    # TODO(tim): this could be parallelized if we preallocate

    # try all possible next features
    col_start_X = (2+I+1-1)*m + 1

    for (y,f) in enumerate(indicators)

        if !in(y, chosen_indicators)


            # select indicator
            train_indicators[end] = f

            # copy in the chosen indicator columns
            col_start_orig = (2+y-1)*m + 1
            copy!(YX, col_start_X, YX_orig, col_start_orig, m)

            # fit a model
            gmm[:fit](YX[!assign_test,:])
            if !gmm[:converged_]
                continue
            end

            behavior = GMRBehavior{AbstractFeature}(gmm, targets, train_indicators)

            # calc logl
            logl = 0.0
            for frameind in 1 : m
                if assign_test[frameind]

                    behavior.processor_target.z[1] = YX_orig[frameind, 1]
                    behavior.processor_target.z[2] = YX_orig[frameind, 2]

                    for (i,j) in enumerate(chosen_indicators)
                        behavior.processor.z[i] = YX_orig[frameind, j+2]
                    end
                    behavior.processor.z[end] = YX_orig[frameind, y+2]

                    logl += _calc_action_loglikelihood(behavior)
                end
            end

            # check if it is beter
            if logl > current_model_logl
                current_model_logl = logl
                current_model = behavior

                @assert(!in(chosen_indicators, y))
                if length(chosen_indicators) == I
                    push!(chosen_indicators, y)
                else
                    chosen_indicators[end] = y
                end
            end
        end
    end

    (chosen_indicators, current_model_logl, current_model)
end
function _greedy_select_next_indicator(
    YX_orig::Matrix{Float64}, # [m, 2+I], the original dataset
    targets::ModelTargets{FeaturesNew.AbstractFeature},
    indicators::Vector{FeaturesNew.AbstractFeature}, # all indicators (TODO: get rid of this)
    chosen_indicators::Vector{Int}, # indeces of chosen indicators
    gmm::PyObject,
    current_model::GMRBehavior,
    current_model_logl::Float64,
    assign_test::BitVector,
    preallocated_data::GMR_PreallocatedData,
    )

    m = size(YX_orig, 1)
    I = length(chosen_indicators)
    YX = Array(Float64, m, 2 + I + 1) # TODO(tim): preallocate?
    copy!(YX, 1, YX_orig, 1, 2m) # copy the first two columns - the 2 target features
    for (x,y) in enumerate(chosen_indicators)
        col_start_X = (2+x-1)*m + 1
        col_start_orig = (2+y-1)*m + 1
        copy!(YX, col_start_X, YX_orig, col_start_orig, m) # copy in the chosen indicator columns
    end

    @assert(!any(v->v== Inf, YX))
    @assert(!any(v->v==-Inf, YX))
    @assert(!any(v->v== NaN, YX))

    train_indicator_indeces = Array(Int, length(chosen_indicators) + 1)
    train_indicator_indeces[1:end-1] = chosen_indicators

    # TODO(tim): this could be parallelized if we preallocate

    # try all possible next features
    col_start_X = (2+I+1-1)*m + 1

    for y in 1 : size(YX_orig, 2)-2

        if !in(y, chosen_indicators)


            # select indicator
            train_indicator_indeces[end] = y

            # copy in the chosen indicator columns
            col_start_orig = (2+y-1)*m + 1
            copy!(YX, col_start_X, YX_orig, col_start_orig, m)

            YX_test = YX[!assign_test,:]

            # fit a model
            gmm[:fit](YX_test)
            if !gmm[:converged_]
                println("DID NOT CONVERGE")
                continue
            end

            behavior = GMRBehavior{FeaturesNew.AbstractFeature}(gmm, targets, train_indicator_indeces,
                            preallocated_data.extractor, preallocated_data.preprocess,
                            preallocated_data.preprocess_target)

            # calc logl

            # count = 0


            logl = 0.0
            for frameind in 1 : m
                if assign_test[frameind]

                    behavior.processor_target.z[1] = YX_orig[frameind, 1]
                    behavior.processor_target.z[2] = YX_orig[frameind, 2]

                    for (i,j) in enumerate(train_indicator_indeces)
                        behavior.processor.z[i] = YX_orig[frameind, j+2]
                    end

                    logl += _calc_action_loglikelihood(behavior)

                    # count += 1
                    # if count < 20
                    #     @printf("YX test: %12.6f  %12.6f  ", YX_orig[frameind, 1], YX_orig[frameind, 2])
                    #     for (i,j) in enumerate(train_indicator_indeces)
                    #         @printf("%12.6f  ", YX_orig[frameind, j+2])
                    #     end
                    #     println(_calc_action_loglikelihood(behavior))
                    # end
                end
            end

            # @printf("%20s   logl: %12.6f\n", string(symbol(indicators[y])), logl)

            # check if it is beter
            if logl > current_model_logl
                current_model_logl = logl
                current_model = behavior

                @assert(!in(chosen_indicators, y))
                if length(chosen_indicators) == I
                    push!(chosen_indicators, y)
                else
                    chosen_indicators[end] = y
                end
            end
        end
    end

    # println("chosen_indicators: ", indicators[chosen_indicators])
    # println("current_model_logl: ", current_model_logl)

    (chosen_indicators, current_model_logl, current_model)
end

function train(
    training_data::ModelTrainingData,
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

    # -------------------------------------------------------------
    # Allocate the GMM

    n_components = params.n_components # int, optional. Number of mixture components. Defaults to 1.
    covariance_type = "full" # string, optional. ‘spherical’, ‘tied’, ‘diag’, ‘full’. Defaults to ‘diag’.
    random_state = 1 # RandomState or an int seed (None by default)
    min_covar = params.min_covar # float, optional

    gmm = mixture.GMM(n_components=n_components, covariance_type=covariance_type,
                      random_state=random_state, min_covar=min_covar)

    # -------------------------------------------------------------
    # Assign a train/test split

    prev_logl = -Inf
    assign_test = falses(nframes_actually_used)
    fraction_test = params.fraction_test # amount of points to use for test
    for i = 1 : nframes_actually_used
        assign_test[i] = rand() < fraction_test
    end

    # -------------------------------------------------------------
    # Optimize the model

    chosen_indicators, current_model_logl, current_model = _greedy_select_next_indicator(
                YX, targets, indicators, Int[], gmm, GMRBehavior{AbstractFeature}(),
                prev_logl, assign_test, preallocated_data)

    while prev_logl < current_model_logl && length(chosen_indicators) < max_n_indicators
        prev_logl = current_model_logl
        chosen_indicators, current_model_logl, current_model = _greedy_select_next_indicator(
                                                        YX, taregts, indicators, chosen_indicators,
                                                        gmm, current_model, prev_logl, assign_test,
                                                        preallocated_data)
    end
    @assert(!isinf(current_model_logl))

    # println("n chosen indicators: ", length(chosen_indicators))
    # println(map(f->symbol(f), indicators[chosen_indicators]))

    current_model
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

    # -------------------------------------------------------------
    # Allocate the GMM

    n_components = params.n_components # int, optional. Number of mixture components. Defaults to 1.
    covariance_type = "full" # string, optional. ‘spherical’, ‘tied’, ‘diag’, ‘full’. Defaults to ‘diag’.
    random_state = 1 # RandomState or an int seed (None by default)
    min_covar = params.min_covar # float, optional

    gmm = mixture.GMM(n_components=n_components, covariance_type=covariance_type,
                      random_state=random_state, min_covar=min_covar)

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
                YX, targets, indicators, Int[], gmm, GMRBehavior{FeaturesNew.AbstractFeature}(),
                prev_logl, assign_test, preallocated_data)

    # println("\nchosen_indicators: ", chosen_indicators, "  ", current_model_logl)

    # while prev_logl < current_model_logl && length(chosen_indicators) < max_n_indicators
    #     prev_logl = current_model_logl
    #     chosen_indicators, current_model_logl, current_model = _greedy_select_next_indicator(
    #                                                     YX, targets, indicators, chosen_indicators, gmm,
    #                                                     current_model, prev_logl, assign_test, preallocated_data)
    #     println("chosen_indicators: ", chosen_indicators, "  ", current_model_logl)
    # end
    # @assert(!isinf(current_model_logl))

    # println("n chosen indicators: ", length(chosen_indicators))
    # println(map(f->symbol(f), indicators[chosen_indicators]))

    current_model
end

end # end module