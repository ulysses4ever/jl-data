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

type DynamicForestBehavior <: AbstractVehicleBehavior
    forest::Ensemble
    indicators::Vector{AbstractFeature}

    # preallocated memory
    X::Vector{Float64} # [n_indicators]
    A::Vector{Float64} # [2]

    function DynamicForestBehavior(
        forest::Ensemble,
        indicators::Vector{AbstractFeature}
        )

        X = Array(Float64, length(indicators))
        A = Array(Float64, 2)

        new(forest, indicators, X, A)
    end
end

ntrees(behavior::DynamicForestBehavior) = length(behavior.forest)

function select_action(
    basics::FeatureExtractBasicsPdSet,
    behavior::DynamicForestBehavior,
    carind::Int,
    validfind::Int
    )

    # pick a tree at random
    tree_index = rand(1:length(behavior.forest))

    # sample from the MvNorm for said tree
    frameind = validfind2frameind(basics.pdset, validfind)
    Features.observe!(behavior.X, basics, carind, frameind, indicators)
    leaf = apply_tree(behavior.forest[tree_index], behavior.X)::MvNormLeaf
    normal  = leaf.m

    _rand!(normal, behavior.A)
    logl = logpdf(normal, behavior.A)

    action_lat = behavior.A[1]
    action_lon = behavior.A[2]

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

    frameind = validfind2frameind(basics.pdset, validfind)
    Features.observe!(behavior.X, basics, carind, frameind, indicators)

    behavior.A[1] = action_lat
    behavior.A[2] = action_lon

    ntrees = length(behavior.forest)
    logl = -ntrees*log(ntrees) # term for the probability of selecting a given mixture component (uniform)
    for tree_index in 1 : ntrees
        leaf = apply_tree(behavior.forest[tree_index], behavior.X)::MvNormLeaf
        normal  = leaf.m
        logl += logpdf(normal, behavior.A)
    end
    logl
end
function calc_action_loglikelihood(
    behavior::DynamicForestBehavior,
    features::DataFrame,
    frameind::Integer,
    )

    # TODO(tim): make this more memory efficient by preallocating

    behavior.A[1] = features[frameind, symbol(FUTUREDESIREDANGLE_250MS)]::Float64
    behavior.A[2] = features[frameind, symbol(FUTUREACCELERATION_250MS)]::Float64

    for (i,feature) in enumerate(behavior.indicators)
        v = features[frameind, symbol(feature)]::Float64
        behavior.X[i] = clamp(v, -FEATURE_EXTREMUM, FEATURE_EXTREMUM)
    end

    behavior.A[1] = action_lat
    behavior.A[2] = action_lon

    ntrees = length(behavior.forest)
    logl = -ntrees*log(ntrees) # term for the probability of selecting a given mixture component (uniform)
    for tree_index in 1 : ntrees
        leaf = apply_tree(behavior.forest[tree_index], behavior.X)::MvNormLeaf
        normal  = leaf.m
        logl += logpdf(normal, behavior.A)
    end
    logl
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

    ntrees::Integer=10,
    max_depth::Integer=5,
    min_samples_split::Integer=100,
    min_samples_leaves::Integer=20,
    min_split_improvement::Float64=0.0,
    partial_sampling::Float64=0.7,
    feautre_extremem::Float64=1000.0,

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
        elseif k == :feautre_extremem
            feautre_extremem = v
        else
            warn("Train DynamicForestBehavior: ignoring $k")
        end
    end

    build_tree_params = BuildTreeParameters(
        nsubfeatures=int(sqrt(length(indicators))),
        max_depth=max_depth,
        min_samples_split=min_samples_split,
        min_samples_leaves=min_samples_leaves,
        min_split_improvement=min_split_improvement,
        loss_function=LossFunction_LOGL,
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
    ensemble = build_forest(y, X, ntrees, build_tree_params, partial_sampling)

    DynamicForestBehavior(ensemble, indicators)
end

end # end module