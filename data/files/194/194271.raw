module GindeleRandomForestBehaviors

using AutomotiveDrivingModels

using RandomForestBehaviors.MvDecisionTrees

import AutomotiveDrivingModels: AbstractVehicleBehavior, select_action, calc_action_loglikelihood, train, observe

export
    GindeleRandomForestBehavior,

    select_action,
    calc_action_loglikelihood,
    train

const FEATURE_EXTREMUM = 1000.0

type GindeleRandomForestBehavior <: AbstractVehicleBehavior
    model_μ::Ensemble
    model_Σ::Ensemble
    indicators::Vector{AbstractFeature}

    # preallocated memory
    μ::Vector{Float64} # [2]
    Σ::Matrix{Float64} # [2×2]
    X::Vector{Float64} # [n_indicators]
    A::Vector{Float64} # [2]

    function GindeleRandomForestBehavior(
        model_μ::Ensemble,
        model_Σ::Ensemble,
        indicators::Vector{AbstractFeature}
        )

        μ = Array(Float64, 2)
        Σ = Array(Float64, 2, 2)
        X = Array(Float64, length(indicators))
        A = Array(Float64, 2)

        new(model_μ, model_Σ, indicators, μ, Σ, X, A)
    end
end

function _calc_mvnormal(
    basics::FeatureExtractBasicsPdSet,
    behavior::GindeleRandomForestBehavior,
    carind::Int,
    validfind::Int
    )

    Features.observe!(behavior.X, basics, carind, validfind, behavior.indicators)
    for (i,v) in enumerate(behavior.X)
        behavior.X[i] = clamp(v, -FEATURE_EXTREMUM, FEATURE_EXTREMUM)
    end

    apply_forest!(behavior.μ, behavior.model_μ, behavior.X)
    apply_forest!(behavior.Σ, behavior.model_Σ, behavior.X)

    MvNormal(behavior.μ,behavior.Σ)
end

function select_action(
    basics::FeatureExtractBasicsPdSet,
    behavior::GindeleRandomForestBehavior,
    carind::Int,
    validfind::Int
    )

    normal = _calc_mvnormal(basics, behavior, carind, validfind)

    Distributions._rand!(normal, behavior.A)
    logl = logpdf(normal, behavior.A)

    action_lat = behavior.A[1]
    action_lon = behavior.A[2]

    (action_lat, action_lon)
end

function calc_action_loglikelihood(
    basics::FeatureExtractBasicsPdSet,
    behavior::GindeleRandomForestBehavior,
    carind::Int,
    validfind::Int,
    action_lat::Float64,
    action_lon::Float64
    )

    #=
    Compute the log-likelihood of the action taken during a single frame
    given the VehicleBehaviorGaussian.
    =#

    behavior.A[1] = action_lat
    behavior.A[2] = action_lon

    normal = _calc_mvnormal(basics, behavior, carind, validfind)
    logpdf(normal, behavior.A)
end
function calc_action_loglikelihood(
    behavior::GindeleRandomForestBehavior,
    features::DataFrame,
    frameind::Integer,
    )

    behavior.A[1] = features[frameind, symbol(FUTUREDESIREDANGLE_250MS)]::Float64
    behavior.A[2] = features[frameind, symbol(FUTUREACCELERATION_250MS)]::Float64

    for (i,feature) in enumerate(behavior.indicators)
        v = features[frameind, symbol(feature)]::Float64
        behavior.X[i] = clamp(v, -FEATURE_EXTREMUM, FEATURE_EXTREMUM)
    end

    apply_forest!(behavior.μ, behavior.model_μ, behavior.X)
    apply_forest!(behavior.Σ, behavior.model_Σ, behavior.X)

    mvnorm_model = MvNormal(behavior.μ, behavior.Σ)

    # can I compute logl without calling logpdf on MvNormal?
    logpdf(mvnorm_model, behavior.A)
end

function train(::Type{GindeleRandomForestBehavior}, trainingframes::DataFrame;
    indicators::Vector{AbstractFeature} = [
                    POSFY, YAW, SPEED, DELTA_SPEED_LIMIT, VELFX, VELFY, SCENEVELFX, TURNRATE,
                    D_CL, D_ML, D_MR, TIMETOCROSSING_LEFT, TIMETOCROSSING_RIGHT,
                    N_LANE_L, N_LANE_R, HAS_LANE_L, HAS_LANE_R, ACC, ACCFX, ACCFY,
                    A_REQ_STAYINLANE,
                 ],

    ntrees::Integer=10,
    max_depth::Integer=5,
    min_samples_split::Integer=100,
    min_samples_leaves::Integer=20,
    min_split_improvement::Float64=0.0,
    partial_sampling::Float64=0.7,

    args::Dict=Dict{Symbol,Any}()
    )

    for (k,v) in args
        if k == :indicators
            indicators = v
        elseif k == :ntrees
            ntrees = v
        elseif k == :max_depth
            max_depth = v
        elseif k == :min_samples_split
            min_samples_split = v
        elseif k == :min_samples_leaves
            min_samples_leaves = v
        elseif k == :min_split_improvement
            min_split_improvement = v
        elseif k == :partial_sampling
            partial_sampling = v
        else
            warn("Train GindeleRandomForestBehavior: ignoring $k")
        end
    end

    build_tree_params = BuildTreeParameters(
        ntrees, max_depth, min_samples_split, min_samples_leaves,
        min_split_improvement, LossFunction_MSE, MeanVecLeaf)

    nframes = size(trainingframes, 1)

    X = Array(Float64, nframes, length(indicators))
    y = Array(Float64, 2, nframes)

    df_ncol = ncol(trainingframes)
    df_names = names(trainingframes)

    total = 0
    for row = 1 : nframes

        action_lat = trainingframes[row, :f_des_angle_250ms]
        action_lon = trainingframes[row, :f_accel_250ms]

        if !isinf(action_lat) && !isinf(action_lon) &&
            !any(feature->isnan(trainingframes[row,symbol(feature)]), indicators)

            total += 1

            for (col, feature) in enumerate(indicators)
                val = trainingframes[row, symbol(feature)]
                X[total, col] = clamp(val, -FEATURE_EXTREMUM, FEATURE_EXTREMUM)
            end

            y[1, total] = action_lat
            y[2, total] = action_lon
        end
    end
    y = y[:, 1:total]::Matrix{Float64}
    X = X[1:total, :]::Matrix{Float64}

    μ = build_forest(y, X, ntrees, build_tree_params, partial_sampling)

    mean_vector = Array(Float64, 2)
    for i = 1 : size(y, 1)
        y[:,i] -= apply_forest!(mean_vector, μ, vec(X[i,:])) # subtract the predicted mean
    end

    build_tree_params = BuildTreeParameters(
        ntrees, max_depth, min_samples_split, min_samples_leaves,
        min_split_improvement, LossFunction_LOGL_MEAN_SUBTRACTED, CovLeaf)

    Σ = build_forest(y, X, ntrees, build_tree_params, partial_sampling)

    GindeleRandomForestBehavior(μ, Σ, indicators)
end

end # end module