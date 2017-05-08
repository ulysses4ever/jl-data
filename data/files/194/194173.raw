module DynamicForestBehaviors

using AutomotiveDrivingModels

using RandomForestBehaviors.MvDecisionTrees

import AutomotiveDrivingModels: AbstractVehicleBehavior, select_action, calc_action_loglikelihood, train, observe

export
    DynamicForestBehavior,

    select_action,
    calc_action_loglikelihood,
    train,
    ntrees

const FEATURE_EXTREMUM = 1000.0

const TRAIN_MAX_DEPTH = 5
const TRAIN_MIN_SAMPLES_SPLIT = 100
const TRAIN_MIN_SAMPLES_LEAVES = 20
const TRAIN_MIN_SPLIT_IMPROVEMENT = 0.0
const TRAIN_N_TREES = 10
const TRAIN_PARTIAL_SAMPLING = 0.7

type DynamicForestBehavior <: AbstractVehicleBehavior
    forest::Ensemble
    indicators::Vector{AbstractFeature}
end

# function _calc_mvnormal(
#     basics::FeatureExtractBasicsPdSet,
#     behavior::DynamicForestBehavior,
#     carind::Int,
#     frameind::Int
#     )

#     indicators = behavior.indicators
#     observations = Features.observe(basics, carind, frameind, indicators)

#     X = Array(Float64, length(indicators))
#     for (i,feature) in enumerate(indicators)
#         X[i] = clamp(observations[symbol(feature)], -FEATURE_EXTREMUM, FEATURE_EXTREMUM)
#     end

#     μ = vec(apply_forest(behavior.model_μ, X)) #vec(behavior.model_μ[:predict](X))
#     Σ = apply_forest(behavior.model_Σ, X)

#     # println(μ, "  ", typeof(μ))
#     # println(Σ, "  ", typeof(Σ))

#     # MvNormal(μ, full(behavior.model_Σ.Σ))
#     MvNormal(μ,Σ)
# end

ntrees(behavior::DynamicForestBehavior) = length(behavior.forest)

function select_action(
    basics::FeatureExtractBasicsPdSet,
    behavior::DynamicForestBehavior,
    carind::Int,
    validfind::Int
    )

    # pick a tree at random
    tree_index = rand(1:length(behavior.forest))

    # sample from the covariance matrix for said tree
    frameind = validfind2frameind(basics.pdset, validfind)
    observations = Features.observe(basics, carind, frameind, indicators)
    leaf = apply_tree(behavior.forest[tree_index], observations)
    normal  = leaf.majority

    action = rand(normal)
    logl = logpdf(normal, action)

    action_lat = action[1]
    action_lon = action[2]

    (action_lat, action_lon)
end

function calc_action_loglikelihood(
    basics::FeatureExtractBasicsPdSet,
    behavior::DynamicForestBehavior,
    carind::Int,
    validfind::Int,
    action_lat::Float64,
    action_lon::Float64
    )

    #=
    Compute the log-likelihood of the action taken during a single frame
    given the VehicleBehaviorGaussian.
    =#

    # pick a tree at random
    tree_index = rand(1:length(behavior.forest))

    # sample from the covariance matrix for said tree
    frameind = validfind2frameind(basics.pdset, validfind)
    observations = Features.observe(basics, carind, frameind, indicators)
    leaf = apply_tree(behavior.forest[tree_index], observations)
    normal  = leaf.majority

    logpdf(normal, [action_lat, action_lon])
end
function calc_action_loglikelihood(
    behavior::DynamicForestBehavior,
    features::DataFrame,
    frameind::Integer,
    )

    # TODO(tim): make this more memory efficient by preallocating

    action_lat = features[frameind, symbol(FUTUREDESIREDANGLE_250MS)]::Float64
    action_lon = features[frameind, symbol(FUTUREACCELERATION_250MS)]::Float64

    indicators = behavior.indicators

    observations = Array(Float64, length(indicators))
    for (i,feature) in enumerate(indicators)
        v = features[frameind, symbol(feature)]::Float64
        observations[i] = clamp(v, -FEATURE_EXTREMUM, FEATURE_EXTREMUM)
    end

    # pick a tree at random
    tree_index = rand(1:length(behavior.forest))

    # sample from the covariance matrix for said tree
    frameind = validfind2frameind(basics.pdset, validfind)
    observations = Features.observe(basics, carind, frameind, indicators)
    leaf = apply_tree(behavior.forest[tree_index], observations)
    normal  = leaf.majority

    logpdf(normal, [action_lat, action_lon])
end

function train(::Type{DynamicForestBehavior}, trainingframes::DataFrame;
    indicators::Vector{AbstractFeature} = [
                    POSFY, YAW, SPEED, DELTA_SPEED_LIMIT, VELFX, VELFY, SCENEVELFX, TURNRATE,
                    D_CL, D_ML, D_MR, TIMETOCROSSING_LEFT, TIMETOCROSSING_RIGHT,
                    N_LANE_L, N_LANE_R, HAS_LANE_L, HAS_LANE_R, ACC, ACCFX, ACCFY,
                    A_REQ_STAYINLANE,
                    HAS_FRONT, D_X_FRONT, D_Y_FRONT, V_X_FRONT, V_Y_FRONT, TTC_X_FRONT,
                    A_REQ_FRONT, TIMEGAP_X_FRONT,
                 ],
    ntrees::Integer = TRAIN_N_TREES,
    max_depth::Integer = TRAIN_MAX_DEPTH,
    args::Dict=Dict{Symbol,Any}()
    )

    for (k,v) in args
        if k == :indicators
            indicators = v
        elseif k == :ntrees
            ntrees = v
        elseif k == :max_depth
            max_depth = v
        else
            warn("Train DynamicForestBehavior: ignoring $k")
        end
    end

    build_tree_params = BuildTreeParameters(
        nsubfeatures=int(sqrt(length(indicators))),
        max_depth=max_depth,
        min_samples_split=TRAIN_MIN_SAMPLES_SPLIT,
        min_samples_leaves=TRAIN_MIN_SAMPLES_LEAVES,
        min_split_improvement=TRAIN_MIN_SPLIT_IMPROVEMENT,
        loss_function=LossFunction_MSE,
        leaf_type=MvNormLeaf
        )

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

    # TODO(tim): build a forest whose nodes are MvNormals
    μ = build_forest(y, X, ntrees, build_tree_params, TRAIN_PARTIAL_SAMPLING)

    DynamicForestBehavior(μ, Σ, indicators)
end

end # end module