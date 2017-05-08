module GaussianMixtureRegressors

using AutomotiveDrivingModels
using GaussianMixtures
using Distributions

import AutomotiveDrivingModels: AbstractVehicleBehavior, select_action, calc_action_loglikelihood, train, observe

export
    GMRBehavior,

    select_action,
    calc_action_loglikelihood,
    train

type GMRBehavior <: AbstractVehicleBehavior

    # pre-computed conditional values
    vec_A::Vector{Matrix{Float64}} # [n_components [2×I]] μ₁₋₂ = μ₁ + Σ₁₂ * Σ₂₂⁻¹ * (x₂ - μ₂) = A*x₂ + b     (I is number of indicators)
    vec_b::Vector{Vector{Float64}} # [n_components [2]]
    vec_C::Vector{Matrix{Float64}} # [n_components [2×2]] Σ₁₋₂ = Σ₁₁ - Σ₁₂ * Σ₂₂⁻¹ * Σ₂₁
    model::MixtureModel{MvNormal} # with full cov so we can easily replace / update

    indicators::Vector{AbstractFeature}

    # # preallocated memory
    # X::Vector{Float64} # [n_indicators]
    # A::Vector{Float64} # [2]

    # function GMRBehavior(
    #     forest::Ensemble,
    #     indicators::Vector{AbstractFeature}
    #     )

    #     X = Array(Float64, length(indicators))
    #     A = Array(Float64, 2)

    #     new(forest, indicators, X, A)
    # end
end

function _condition_on_observations()
    μ₁ = μ[1:2]
    μ₂ = μ[3:end]
    Σ₁₁ = Σ[1:2,1:2]
    Σ₁₂ = Σ[1:2,3:end]
    Σ₂₂ = Σ[3:end,3:end]

    μ₁₋₂ = μ₁ + Σ₁₂ * Σ₂₂⁻¹ * (x₂ - μ₂)
         = μ₁ + A*x₂ - A*μ₂
         = b + A*x₂ # (precompute)
    Σ₁₋₂ = Σ₁₁ - Σ₁₂ * Σ₂₂⁻¹ * Σ₂₁ # this can be precomputed

end

function select_action(
    basics::FeatureExtractBasicsPdSet,
    behavior::GMRBehavior,
    carind::Int,
    validfind::Int
    )

    # condition on the mixture

    # Pick a component based on its conditional probability
    component_index = rand(1:behavior.n_components)

    # Sample from said component

    # # pick a tree at random
    # tree_index = rand(1:length(behavior.forest.trees))

    # # sample from the MvNorm for said tree
    # Features.observe!(behavior.X, basics, carind, validfind, behavior.indicators)
    # leaf = apply_tree(behavior.forest.trees[tree_index], behavior.X)::MvNormLeaf
    # normal  = leaf.m

    # Distributions._rand!(normal, behavior.A)

    # action_lat = behavior.A[1]
    # action_lon = behavior.A[2]
    action_lat = 0.0
    action_lon = 0.0

    (action_lat, action_lon)
end

function _calc_action_loglikelihood(
    behavior::GMRBehavior,
    action_lat::Float64,
    action_lon::Float64
    )

    # behavior.A[1] = action_lat
    # behavior.A[2] = action_lon

    # ntrees = length(behavior.forest.trees)
    # log_ntrees = log(ntrees)

    # total_probability_density = 0.0
    # logl = 0.0
    # for tree in behavior.forest.trees
    #     leaf = apply_tree(tree, behavior.X)::MvNormLeaf
    #     normal  = leaf.m

    #     p = pdf(normal, behavior.A)/ntrees

    #     if total_probability_density == 0.0
    #         logl = logpdf(normal, behavior.A) - log_ntrees
    #     elseif p < total_probability_density
    #         # NOTE: log(a + b) = log a + log(1 + b/a)
    #         logl = logl + log1p(p/total_probability_density)
    #     else
    #         # NOTE: log(a + b) = log b + log(1 + a/b)
    #         logl = (logpdf(normal, behavior.A) - log_ntrees) + log1p(total_probability_density/p)
    #     end
    #     total_probability_density += p
    # end

    # logl
    0.0
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

    # frameind = validfind2frameind(basics.pdset, validfind)
    # Features.observe!(behavior.X, basics, carind, frameind, behavior.indicators)

    # _calc_action_loglikelihood(behavior, action_lat, action_lon)
    0.0
end
function calc_action_loglikelihood(
    behavior::GMRBehavior,
    features::DataFrame,
    frameind::Integer,
    )

    # action_lat = features[frameind, symbol(FUTUREDESIREDANGLE_250MS)]::Float64
    # action_lon = features[frameind, symbol(FUTUREACCELERATION_250MS)]::Float64

    # _calc_action_loglikelihood(behavior, action_lat, action_lon)
    0.0
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
    kind::Symbol=:full,
    args::Dict=Dict{Symbol,Any}()
    )

    for (k,v) in args
        if k == :indicators
            indicators = v
        elseif k == :n_components
            n_components = v
        elseif k == :kind
            kind = v
        else
            warn("Train GMRBehavior: ignoring $k")
        end
    end

    nframes = size(trainingframes, 1)

    features = append!([FUTUREDESIREDANGLE_250MS, FUTUREACCELERATION_250MS], indicators)
    @assert(length(unique(features)) == length(features))

    # Construct an m×d matrix where
    #   m - number of data samples
    #   d - dimension of the feature + target vector
    X = Array(Float64, nframes, length(indicators))

    df_ncol = ncol(trainingframes)
    for row = 1 : nframes

        X[row, 1] = trainingframes[row, :f_des_angle_250ms]
        X[row, 2] = trainingframes[row, :f_accel_250ms]

        for (col, feature) in enumerate(indicators)
            val = trainingframes[row, symbol(feature)]
            # if isinf(val)
                # X[total, col+2] = replace_na(feature, basics, carind, validfind)
            # end
            X[row, col+2] = val
        end
    end

    model = GMM(n_components, X, kind=kind)

    GMRBehavior(model, indicators)
end

end # end module