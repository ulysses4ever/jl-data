module GaussianMixtureRegressors

# http://cs229.stanford.edu/section/more_on_gaussians.pdf
# http://pypr.sourceforge.net/mog.html

using AutomotiveDrivingModels
using GaussianMixtures
using Distributions

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

type GMRBehavior <: AbstractVehicleBehavior

    vec_A::Vector{Matrix{Float64}} # [n_components [2×I]] μ₁₋₂ = μ₁ + Σ₁₂ * Σ₂₂⁻¹ * (x₂ - μ₂) = A*x₂ + b     (I is number of indicators)
    vec_b::Vector{Vector{Float64}} # [n_components [2]]

    mixture_Act_given_Obs::MixtureModel{Multivariate,Continuous,MvNormal} # p(action|obs), mean and weighting must be updated with each observation, cov is pre-computed
    mixture_Obs::MixtureModel{Multivariate,Continuous,MvNormal} # p(obs), all pre-computed, should never be edited
    indicators::Vector{AbstractFeature} # list of indicator features, in order

    x::Vector{Float64} # observations # [I]
    a::Vector{Float64} # action # [2]

    GMRBehavior() = new() # dummy constructor
    function GMRBehavior(
        gmm::GMM{Float64},
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

            Σ = GaussianMixtures.covar(gmm.Σ[i])

            # ensure it is PosDef by a small margin
            Λ, V = eig(Σ)
            for (j,λ) in enumerate(Λ)
                Λ[j] = max(DEFAULT_MIN_EIGENVALUE, λ)
            end
            Σ[:] = V*diagm(Λ)/V

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

        mixture_Act_given_Obs = MixtureModel(vec_G, fill(1/n_components, n_components)) # p(action|obs), mean and weighting must be updated with each observation, cov is pre-computed
        mixture_Obs = MixtureModel(vec_H, gmm.w) # p(obs), all pre-computed, should never be edited

        x = Array(Float64, n_indicators) # pre-allocated memory for observation
        a = Array(Float64, n_targets) # pre-allocated memory for action

        new(vec_A, vec_b, mixture_Act_given_Obs, mixture_Obs, deepcopy(indicators), x, a)
    end
end

type GMR_TrainParams <: AbstractVehicleBehaviorTrainParams

    targets::ModelTargets
    indicators::Vector{AbstractFeature}

    n_components::Int
    max_n_indicators::Int

    function GMR_TrainParams(;
        targets::ModelTargets = ModelTargets(FUTUREDESIREDANGLE_250MS, FUTUREACCELERATION_250MS),
        indicators::Vector{AbstractFeature} = [
                            POSFY, YAW, SPEED, DELTA_SPEED_LIMIT, VELFX, VELFY, SCENEVELFX, TURNRATE,
                            D_CL, D_ML, D_MR, TIMETOCROSSING_LEFT, TIMETOCROSSING_RIGHT,
                            N_LANE_L, N_LANE_R, HAS_LANE_L, HAS_LANE_R, ACC, ACCFX, ACCFY,
                            A_REQ_STAYINLANE,
                            HAS_FRONT, D_X_FRONT, D_Y_FRONT, V_X_FRONT, V_Y_FRONT, TTC_X_FRONT,
                            A_REQ_FRONT, TIMEGAP_X_FRONT,
                         ],

        n_components::Integer=2,
        max_n_indicators::Integer=3,
        )

        new(targets, indicators, n_components, max_n_indicators)
    end
end
type GMR_PreallocatedData <: AbstractVehicleBehaviorPreallocatedData
    # TODO(tim): put X, y, etc. into here

    X::Matrix{Float64}

    function GMR_PreallocatedData(dset::ModelTrainingData, params::GMR_TrainParams)

        nframes = size(dset.dataframe, 1)
        p = length(params.indicators)

        X = Array(Float64, nframes, 2 + p)

        new(X)
    end
end
function preallocate_learning_data(
    dset::ModelTrainingData,
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

    # println("behavior.indicators: ", behavior.indicators)

    # pull observations
    Features.observe!(behavior.x, basics, carind, validfind, behavior.indicators)
    for i in 1 : length(behavior.x)
        behavior.x[i] = clamp(behavior.x[i], -100.0, 100.0)
    end

    # condition on the mixture
    n_components = length(behavior.vec_A)
    mixture_Obs = behavior.mixture_Obs
    mixture_Act_given_Obs = behavior.mixture_Act_given_Obs

    total_prior_sum = 0.0
    for i = 1 : n_components
        mixture_Act_given_Obs.prior.p[i] = mixture_Obs.prior.p[i] * pdf(mixture_Obs.components[i], behavior.x)
        total_prior_sum += mixture_Act_given_Obs.prior.p[i]
    end
    if abs(total_prior_sum) < TOLERANCE_ZERO_PROB_WEIGHT
        return (0.0,0.0)
    end
    # println("w before: ", mixture_Act_given_Obs.prior.p)
    # println("total_prior_sum: ", total_prior_sum)
    for i = 1 : n_components
        mixture_Act_given_Obs.prior.p[i] /= total_prior_sum
    end
    @assert(!isnan(mixture_Act_given_Obs.prior.p[1]))

    # println("w: ", mixture_Act_given_Obs.prior.p)

    # pick a component to sample from
    component_index = rand(mixture_Act_given_Obs.prior)

    # println("component index: ", component_index)

    component = mixture_Act_given_Obs.components[component_index]

    # println("component before: ", component.μ)

    # modify said component with observation
    component.μ[:] = behavior.vec_b[component_index] + behavior.vec_A[component_index]*behavior.x

    # println("component after: ", component.μ)

    # sample from said component
    Distributions._rand!(component, behavior.a)

    # println("action: ", behavior.a)

    # return the selected action
    action_lat = behavior.a[1]
    action_lon = behavior.a[2]

    # println("calc logl: ", calc_action_loglikelihood( basics, behavior, carind, validfind,
    #                                                  action_lat, action_lon))

    (action_lat, action_lon)
end

function _calc_action_loglikelihood(
    behavior::GMRBehavior,
    action_lat::Float64,
    action_lon::Float64
    )

    # NOTE(tim): this assumes observations have already been pulled and are in behavior.x

    behavior.a[1] = action_lat
    behavior.a[2] = action_lon

    mixture_Act_given_Obs = behavior.mixture_Act_given_Obs
    mixture_Obs = behavior.mixture_Obs
    n_components = length(behavior.vec_A)

    # condition on the mixture
    total_prior_sum = 0.0
    for i = 1 : n_components
        mixture_Act_given_Obs.prior.p[i] = mixture_Obs.prior.p[i] * pdf(mixture_Obs.components[i], behavior.x)
        total_prior_sum += mixture_Act_given_Obs.prior.p[i]

        mixture_Act_given_Obs.components[i].μ[:] = behavior.vec_b[i] + behavior.vec_A[i]*behavior.x
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
        #                                                               mixture_Obs.components[i].Σ.mat[j,2], log(pdf(mixture_Obs.components[i], behavior.x)))
        #         end
        #     end
        # end
        # println("obs: ", behavior.x)
        # println("prior:  ", mixture_Act_given_Obs.prior.p)
        # mixture_Act_given_Obs.prior.p[:] ./= total_prior_sum
        # println("prob:   ", pdf(mixture_Act_given_Obs, behavior.a))
        # println("logl:   ", logpdf(mixture_Act_given_Obs, behavior.a))
        # println("  ")

        # sleep(100)

        return -100.0 # TODO(tim): fix this
        # return -Inf
    end
    for i = 1 : n_components
        mixture_Act_given_Obs.prior.p[i] /= total_prior_sum
    end

    # compute logl
    logl = logpdf(mixture_Act_given_Obs, behavior.a)
    # if length(behavior.x) == 2
    #     println("indicators: ", map(i->symbol(i), behavior.indicators), "   ", @sprintf("[%6.3f, %8.3f]", behavior.x[1], behavior.x[2]), "  ", logl)
    # end
    logl = max(logl, -100.0)

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

    Features.observe!(behavior.x, basics, carind, validfind, behavior.indicators, replace_na=true)

    _calc_action_loglikelihood(behavior, action_lat, action_lon)
end
function calc_action_loglikelihood(
    behavior::GMRBehavior,
    features::DataFrame,
    frameind::Integer,
    )

    action_lat = features[frameind, symbol(FUTUREDESIREDANGLE_250MS)]::Float64
    action_lon = features[frameind, symbol(FUTUREACCELERATION_250MS)]::Float64

    for (i,feature) in enumerate(behavior.indicators)
        behavior.x[i] = features[frameind, symbol(feature)]::Float64
    end

    _calc_action_loglikelihood(behavior, action_lat, action_lon)
end

function _greedy_select_next_indicator(
    X_orig::Matrix{Float64}, # [m, 2+I], the original dataset
    indicators::Vector{AbstractFeature}, # all indicators
    chosen_indicators::Vector{Int}, # indeces of chosen indicators
    n_components::Integer,
    current_model::GMRBehavior,
    current_model_logl::Float64,
    assign_test::BitVector,
    )

    m = size(X_orig, 1)
    I = length(chosen_indicators)
    X = Array(Float64, m, 2 + I + 1) # TODO(tim): preallocate?
    copy!(X, 1, X_orig, 1, 2m) # copy the first two columns - the 2 target features
    for (x,y) in enumerate(chosen_indicators)
        col_start_X = (2+x-1)*m + 1
        col_start_orig = (2+y-1)*m + 1
        copy!(X, col_start_X, X_orig, col_start_orig, m) # copy in the chosen indicator columns
    end

    train_indicators = indicators[chosen_indicators]
    push!(train_indicators, indicators[1])

    # TODO(tim): this could be parallelized

    # println("_greedy_select_next_indicator   ", I)

    # try all possible next features
    col_start_X = (2+I+1-1)*m + 1

    # println("indicators: ", indicators)
    # println("chosen_indicators: ", chosen_indicators)

    for (y,f) in enumerate(indicators)

        if !in(y, chosen_indicators)


            # select indicator
            train_indicators[end] = f

            # print("trying ", train_indicators)

            # copy in the chosen indicator columns
            col_start_orig = (2+y-1)*m + 1
            copy!(X, col_start_X, X_orig, col_start_orig, m)


            # fit a model

            # println("to_pass:")
            # to_pass = X[!assign_test,:]
            # for i in 1 : size(to_pass, 1)
            #     println(to_pass[i,:])
            # end

            (model, successful) = try
                   (GMM(n_components, X[!assign_test,:], kind=:full), true)
                catch
                   (GMM(eye(1)), false)
                end

            if !successful
                # println("unsuccessful")
                continue
            end

            behavior = GMRBehavior(model, train_indicators)

            # calc logl
            logl = 0.0
            for frameind in 1 : m
                if assign_test[frameind]
                    # logl += calc_action_loglikelihood(behavior, trainingframes, frameind)

                    action_lat = X_orig[frameind, 1]
                    action_lon = X_orig[frameind, 2]
                    for (i,j) in enumerate(chosen_indicators)
                        behavior.x[i] = X_orig[frameind, j+2]
                    end

                    logl += _calc_action_loglikelihood(behavior, action_lat, action_lon)
                end
            end
            # if length(train_indicators) == 2 && train_indicators[1] == ACC && train_indicators[2] == TIME_CONSECUTIVE_THROTTLE
            #     behavior.x[:] = [0.5166607680569371,8.25]
            #     print("CHECKING A: ")
            #     println(_calc_action_loglikelihood(behavior, -0.00037922436239100674, 0.680074955467191))
            # end
            # println("\tlogl: ", logl)

            # check if it is beter
            if logl > current_model_logl
                # println(logl, " > ", current_model_logl, "   ", symbol(f))
                current_model_logl = logl
                current_model = behavior

                # if length(current_model.indicators) == 2 && current_model.indicators[1] == ACC && current_model.indicators[2] == TIME_CONSECUTIVE_THROTTLE
                #     current_model.x[:] = [0.5166607680569371,8.25]
                #     print("CHECKING B: ")
                #     print(_calc_action_loglikelihood(current_model, -0.00037922436239100674, 0.680074955467191))
                # end

                @assert(!in(chosen_indicators, y))
                if length(chosen_indicators) == I
                    push!(chosen_indicators, y)
                else
                    chosen_indicators[end] = y
                end
            end

            # println("current indicators: ", map(i->symbol(i), behavior.indicators))
            # println("current chosen:     ", map(i->symbol(i), indicators[chosen_indicators]))
            # println("current model indicators: ", map(i->symbol(i), current_model.indicators))
        end
    end

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

    indicators = params.indicators
    n_components = params.n_components
    max_n_indicators = params.max_n_indicators
    X = preallocated_data.X

    target_lat = params.targets.lat
    target_lon = params.targets.lon
    @assert(!in(target_lat, indicators))
    @assert(!in(target_lon, indicators))

    trainingframes = training_data.dataframe_nona
    nframes = size(trainingframes, 1)
    features = append!([target_lat, target_lon], indicators)

    sym_lat = symbol(target_lat)
    sym_lon = symbol(target_lon)

    # Construct an m×d matrix where
    #   m - number of data samples
    #   d - dimension of the feature + target vector

    nframes_actually_used = 0
    for row = 1 : nframes
        if is_in_fold(fold, fold_assignment.frame_assignment[row], match_fold)

            nframes_actually_used += 1

            X[nframes_actually_used, 1] = trainingframes[row, sym_lat]
            X[nframes_actually_used, 2] = trainingframes[row, sym_lon]

            for (col, feature) in enumerate(indicators)
                val = trainingframes[row, symbol(feature)]
                @assert(!isinf(val))
                X[nframes_actually_used, col+2] = val
            end
        end
    end
    X2 = X[1:nframes_actually_used, :]

    prev_logl = -Inf
    assign_test = falses(nframes_actually_used)
    fraction_test = 0.1 # amount test
    for i = 1 : nframes_actually_used
        assign_test[i] = rand() < fraction_test
    end

    # println("max n indicators: ", max_n_indicators)

    chosen_indicators, current_model_logl, current_model = _greedy_select_next_indicator(
                X2, indicators, Int[], n_components, GMRBehavior(), prev_logl, assign_test)

    # println("logl: ", current_model_logl, "   indicators ", chosen_indicators)
    while prev_logl < current_model_logl && length(chosen_indicators) < max_n_indicators
        prev_logl = current_model_logl
        chosen_indicators, current_model_logl, current_model = _greedy_select_next_indicator(
                                                        X2, indicators, chosen_indicators, n_components,
                                                        current_model, prev_logl, assign_test)
        # println("logl: ", current_model_logl, "   indicators ", chosen_indicators)
    end
    @assert(!isinf(current_model_logl))
    # println(" ")
    # println("sleeping")
    # sleep(10)

    # println(current_model.indicators)

    # println("final indicators: ", map(i->symbol(i), current_model.indicators))
    # println(map(i->symbol(i), indicators[chosen_indicators]))
    # if length(current_model.x) == 2
    #     current_model.x[:] = [0.5166607680569371,8.25]
    #     # current_model.x[:] = [ 0.918,    2.650]  # 3.2000716597634202
    #     println("CHECKING: ", _calc_action_loglikelihood(current_model, -0.00037922436239100674, 0.680074955467191))
    # end

    # model = GMM(n_components, X, kind=Σ_type)
    # current_model = GMRBehavior(model, indicators)

    # println("FINAL MODEL")
    # println(current_model)
    # println("\n\n")

    current_model
end

end # end module