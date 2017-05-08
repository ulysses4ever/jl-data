module GaussianMixtureRegressors

# http://cs229.stanford.edu/section/more_on_gaussians.pdf
# http://pypr.sourceforge.net/mog.html

using AutomotiveDrivingModels
using GaussianMixtures
using Distributions

import AutomotiveDrivingModels: AbstractVehicleBehavior, select_action, calc_action_loglikelihood, train, observe

export
    GMRBehavior,

    select_action,
    calc_action_loglikelihood,
    train

const DEFAULT_MIN_EIGENVALUE = 1e-10

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
            for (i,λ) in enumerate(Λ)
                Λ[i] = max(DEFAULT_MIN_EIGENVALUE, λ)
            end
            Σ[:] = V*diagm(Λ)/V

            Σ₁₁ = Σ[1:n_targets,1:n_targets]
            Σ₁₂ = Σ[1:n_targets,n_targets+1:end]
            Σ₂₂ = Σ[n_targets+1:end,n_targets+1:end]

            C = eye(n_targets)

            try
                iΣ₂₂ = inv(Σ₂₂)
                A = Σ₁₂ * iΣ₂₂

                vec_A[i] = A
                vec_b[i] = vec(μ₁ - A*μ₂)
                C[:] = Σ₁₁ - Σ₁₂ * iΣ₂₂ * (Σ₁₂')
            catch
                vec_A[i] = zeros(n_targets, n_indicators)
                vec_b[i] = zeros(n_indicators)
            end

            vec_G[i] = MvNormal(Array(Float64, n_targets), C) # p(action|obs), mean and weighting must be updated with each observation, cov is pre-computed
            vec_H[i] = MvNormal(μ₂, Σ₂₂) # p(obs), all pre-computed, should never be edited
        end

        mixture_Act_given_Obs = MixtureModel(vec_G, fill(1/n_components, n_components)) # p(action|obs), mean and weighting must be updated with each observation, cov is pre-computed
        mixture_Obs = MixtureModel(vec_H, gmm.w) # p(obs), all pre-computed, should never be edited

        x = Array(Float64, length(indicators)) # pre-allocated memory for observation
        a = Array(Float64, n_targets) # pre-allocated memory for action

        new(vec_A, vec_b, mixture_Act_given_Obs, mixture_Obs, indicators, x, a)
    end
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

DO_IT = true
dont_do_it() = global DO_IT = false

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

        println("action: ", behavior.a)
        println("means:  ")
        for i in 1 : n_components
            println("\t", mixture_Act_given_Obs.components[i].μ)
        end
        println("obs: ", behavior.x)
        println("prior:  ", mixture_Act_given_Obs.prior.p)
        mixture_Act_given_Obs.prior.p[:] ./= total_prior_sum
        println("prob:   ", pdf(mixture_Act_given_Obs, behavior.a))
        println("logl:   ", logpdf(mixture_Act_given_Obs, behavior.a))
        println("  ")

        return -Inf
    end
    for i = 1 : n_components
        mixture_Act_given_Obs.prior.p[i] /= total_prior_sum
    end

    # if DO_IT
    #     println("action: ", behavior.a)
    #     println("means:  ")
    #     for i in 1 : n_components
    #         println("\t", mixture_Act_given_Obs.components[i].μ)
    #     end
    #     println("prior:  ", mixture_Act_given_Obs.prior.p)
    #     println("prob:   ", pdf(mixture_Act_given_Obs, behavior.a))
    #     println("logl:   ", logpdf(mixture_Act_given_Obs, behavior.a))
    #     println("  ")
    #     sleep(0.5)
    # end

    # compute logl
    logpdf(mixture_Act_given_Obs, behavior.a)
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
    Y::Matrix{Float64}, # [m, 2+I]
    trainingframes::DataFrame,
    indicators::Vector{AbstractFeature}, # all indicators
    chosen_indicators::Vector{Int}, # indeces of chosen indicators
    n_components::Integer,
    Σ_type::Symbol,
    current_model::GMRBehavior,
    current_model_logl::Float64,
    assign_test::BitVector,
    )

    m = size(Y, 1)
    I = length(chosen_indicators)
    X = Array(Float64, m, 2 + I + 1)
    copy!(X, 1, Y, 1, 2m) # copy the first two columns - the 2 target features
    for (x,y) in enumerate(chosen_indicators)
        col_start_X = (2+x-1)*m + 1
        col_start_Y = (2+y-1)*m + 1
        copy!(X, col_start_X, Y, col_start_Y, m) # copy in the chosen indicator columns
    end

    train_indicators = indicators[chosen_indicators]
    push!(train_indicators, indicators[1])

    # TODO(tim): this could be parallelized

    # println("_greedy_select_next_indicator   ", I)

    # try all possible next features
    col_start_X = (2+I+1-1)*m + 1
    for (y,f) in enumerate(indicators)
        if !in(y, chosen_indicators)

            # println("trying ", chosen_indicators, "  + ", y)

            # select indicator
            train_indicators[end] = f

            # copy in the chosen indicator columns
            col_start_Y = (2+y-1)*m + 1
            copy!(X, col_start_X, Y, col_start_Y, m)


            # fit a model
            (model, successful) = try
                   (GMM(n_components, X[!assign_test,:], kind=Σ_type), true)
                catch
                   (GMM(eye(1)), false)
                end

            if !successful
                continue
            end

            behavior = GMRBehavior(model, train_indicators)

            # calc logl
            logl = 0.0
            for frameind = 1 : m
                if assign_test[frameind]
                    logl += calc_action_loglikelihood(behavior, trainingframes, frameind)
                end
            end
            # println("\tlogl: ", logl)

            # check if it is beter
            if logl > current_model_logl
                # println(logl, " > ", current_model_logl, "   ", symbol(f))
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

function train(::Type{GMRBehavior}, trainingframes::DataFrame;
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
    Σ_type::Symbol=:full,
    args::Dict=Dict{Symbol,Any}()
    )

    # TODO: replace na

    for (k,v) in args
        if k == :indicators
            indicators = v
        elseif k == :n_components
            n_components = v
        elseif k == :kind
            Σ_type = v
        elseif k == :max_n_indicators
            max_n_indicators = v
        else
            warn("Train GMRBehavior: ignoring $k")
        end
    end

    @assert(!in(FUTUREDESIREDANGLE_250MS, indicators))
    @assert(!in(FUTUREACCELERATION_250MS, indicators))

    nframes = size(trainingframes, 1)
    features = append!([FUTUREDESIREDANGLE_250MS, FUTUREACCELERATION_250MS], indicators)

    # Construct an m×d matrix where
    #   m - number of data samples
    #   d - dimension of the feature + target vector
    X = Array(Float64, nframes, 2 + length(indicators))

    for row = 1 : nframes

        X[row, 1] = trainingframes[row, :f_des_angle_250ms]
        X[row, 2] = trainingframes[row, :f_accel_250ms]

        for (col, feature) in enumerate(indicators)
            val = trainingframes[row, symbol(feature)]
            X[row, col+2] = clamp(val, -100.0, 100.0)
        end
    end

    prev_logl = -Inf
    assign_test = falses(nframes)
    fraction_test = 0.1 # amount test
    for i = 1 : nframes
        assign_test[i] = rand() < fraction_test
    end

    chosen_indicators, current_model_logl, current_model = _greedy_select_next_indicator(
                X, trainingframes, indicators, Int[], n_components, Σ_type, GMRBehavior(), prev_logl, assign_test)
    @assert(!isinf(current_model_logl))

    println("logl: ", current_model_logl, "   indicators ", chosen_indicators)
    while prev_logl < current_model_logl && length(chosen_indicators) < max_n_indicators
        prev_logl = current_model_logl
        chosen_indicators, current_model_logl, current_model = _greedy_select_next_indicator(
                                                        X, trainingframes, indicators, chosen_indicators, n_components,
                                                        Σ_type, current_model, prev_logl, assign_test)
        println("logl: ", current_model_logl, "   indicators ", chosen_indicators)
    end
    println(" ")

    # println(current_model.indicators)

    # model = GMM(n_components, X, kind=Σ_type)
    # current_model = GMRBehavior(model, indicators)

    current_model
end

end # end module