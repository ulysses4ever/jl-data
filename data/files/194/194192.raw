# module DynamicForestBehaviors

# using AutomotiveDrivingModels

# using RandomForestBehaviors.MvDecisionTrees

# import AutomotiveDrivingModels: AbstractVehicleBehavior, select_action, calc_action_loglikelihood, train, observe

# export
#     DynamicForestBehavior,

#     select_action,
#     calc_action_loglikelihood,
#     train

# const FEATURE_EXTREMUM = 1000.0

# type DynamicForestBehavior <: AbstractVehicleBehavior
#     forest::Ensemble
#     indicators::Vector{AbstractFeature}

#     # preallocated memory
#     X::Vector{Float64} # [n_indicators]
#     A::Vector{Float64} # [2]

#     function DynamicForestBehavior(
#         forest::Ensemble,
#         indicators::Vector{AbstractFeature}
#         )

#         X = Array(Float64, length(indicators))
#         A = Array(Float64, 2)

#         new(forest, indicators, X, A)
#     end
# end

# function select_action(
#     basics::FeatureExtractBasicsPdSet,
#     behavior::DynamicForestBehavior,
#     carind::Int,
#     validfind::Int
#     )

#     # pick a tree at random
#     tree_index = rand(1:length(behavior.forest.trees))

#     # sample from the MvNorm for said tree
#     Features.observe!(behavior.X, basics, carind, validfind, behavior.indicators)
#     for i = 1 : length(behavior.X)
#         behavior.X[i] = clamp(behavior.X[i], -FEATURE_EXTREMUM, FEATURE_EXTREMUM)
#     end

#     leaf = apply_tree(behavior.forest.trees[tree_index], behavior.X)::AutoregressiveMvNormLeaf
#     normal  = leaf.m
#     BLAS.gemv!('N', 1.0, leaf.A, behavior.X, 0.0, normal.μ) # μ = leaf.A * behavior.X # predicted mean

#     # println("leaf.A: ", leaf.A)
#     # println("behavior.X: ", behavior.X)
#     # println(normal.μ)

#     Distributions._rand!(normal, behavior.A)

#     println(behavior.A)

#     action_lat = behavior.A[1]
#     action_lon = behavior.A[2]

#     (action_lat, action_lon)
# end

# function _calc_action_loglikelihood(
#     behavior::DynamicForestBehavior,
#     action_lat::Float64,
#     action_lon::Float64
#     )

#     behavior.A[1] = action_lat
#     behavior.A[2] = action_lon

#     total_probability = 0.0
#     logl = 0.0
#     for tree in behavior.forest.trees
#         leaf = apply_tree(tree, behavior.X)::AutoregressiveMvNormLeaf
#         normal  = leaf.m
#         BLAS.gemv!('N', 1.0, leaf.A, behavior.X, 0.0, normal.μ) # μ = leaf.A * behavior.X # predicted mean

#         p = pdf(normal, behavior.A)

#         if total_probability == 0.0
#             total_probability = p
#             logl = logpdf(normal, behavior.A)
#         elseif p < total_probability
#             # NOTE: log(a + b) = log a + log(1 + b/a)
#             logl += log1p(p/total_probability)
#             total_probability += p
#         else
#             logl = logpdf(normal, behavior.A) + log1p(total_probability/p)
#             total_probability += p
#         end
#     end

#     logl
# end
# function calc_action_loglikelihood(
#     basics::FeatureExtractBasicsPdSet,
#     behavior::DynamicForestBehavior,
#     carind::Int,
#     validfind::Int,
#     action_lat::Float64,
#     action_lon::Float64
#     )

#     #=
#     Compute the log-likelihood of the action taken during a single frame
#     given the VehicleBehaviorGaussian.
#     =#

#     frameind = validfind2frameind(basics.pdset, validfind)
#     Features.observe!(behavior.X, basics, carind, frameind, behavior.indicators)
#     for i = 1 : length(behavior.X)
#         behavior.X[i] = clamp(behavior.X[i], -FEATURE_EXTREMUM, FEATURE_EXTREMUM)
#     end

#     _calc_action_loglikelihood(behavior, action_lat, action_lon)
# end
# function calc_action_loglikelihood(
#     behavior::DynamicForestBehavior,
#     features::DataFrame,
#     frameind::Integer,
#     )

#     action_lat = features[frameind, symbol(FUTUREDESIREDANGLE_250MS)]::Float64
#     action_lon = features[frameind, symbol(FUTUREACCELERATION_250MS)]::Float64
#     for i = 1 : length(behavior.X)
#         behavior.X[i] = clamp(behavior.X[i], -FEATURE_EXTREMUM, FEATURE_EXTREMUM)
#     end

#     _calc_action_loglikelihood(behavior, action_lat, action_lon)
# end

# function train(::Type{DynamicForestBehavior}, trainingframes::DataFrame;
#     indicators::Vector{AbstractFeature} = [
#                     POSFY, YAW, SPEED, DELTA_SPEED_LIMIT, VELFX, VELFY, SCENEVELFX, TURNRATE,
#                     D_CL, D_ML, D_MR, TIMETOCROSSING_LEFT, TIMETOCROSSING_RIGHT,
#                     N_LANE_L, N_LANE_R, HAS_LANE_L, HAS_LANE_R, ACC, ACCFX, ACCFY,
#                     A_REQ_STAYINLANE,
#                     HAS_FRONT, D_X_FRONT, D_Y_FRONT, V_X_FRONT, V_Y_FRONT, TTC_X_FRONT,
#                     A_REQ_FRONT, TIMEGAP_X_FRONT,
#                  ],

#     ntrees::Integer=10,
#     max_depth::Integer=5,
#     min_samples_split::Integer=100,
#     min_samples_leaves::Integer=20,
#     min_split_improvement::Float64=0.0,
#     partial_sampling::Float64=0.7,
#     autoregressive_constant::Float64=0.5, # Autoregressive constant

#     args::Dict=Dict{Symbol,Any}()
#     )

#     for (k,v) in args
#         if k == :indicators
#             indicators = v
#         elseif k == :ntrees
#             ntrees = v
#         elseif k == :max_depth
#             max_depth = v
#         elseif k == :min_samples_split
#             min_samples_split = v
#         elseif k == :min_samples_leaves
#             min_samples_leaves = v
#         elseif k == :min_split_improvement
#             min_split_improvement = v
#         elseif k == :partial_sampling
#             partial_sampling = v
#         elseif k == :autoregressive_constant
#             autoregressive_constant = v
#         else
#             warn("Train DynamicForestBehavior: ignoring $k")
#         end
#     end

#     build_tree_params = BuildTreeParameters(
#         int(sqrt(length(indicators))),
#         max_depth,
#         min_samples_split,
#         min_samples_leaves,
#         min_split_improvement,
#         LossFunction_AUTOREGRESSIVE,
#         AutoregressiveMvNormLeaf,
#         )

#     MvDecisionTrees.set_autoregression_constant(autoregressive_constant)

#     nframes = size(trainingframes, 1)

#     X = Array(Float64, nframes, length(indicators))
#     y = Array(Float64, 2, nframes)

#     df_ncol = ncol(trainingframes)
#     df_names = names(trainingframes)

#     total = 0
#     for row = 1 : nframes

#         action_lat = trainingframes[row, :f_des_angle_250ms]
#         action_lon = trainingframes[row, :f_accel_250ms]

#         if !isinf(action_lat) && !isinf(action_lon) &&
#             !any(feature->isnan(trainingframes[row,symbol(feature)]), indicators)

#             total += 1

#             for (col, feature) in enumerate(indicators)
#                 val = trainingframes[row, symbol(feature)]
#                 X[total, col] = clamp(val, -FEATURE_EXTREMUM, FEATURE_EXTREMUM)
#             end

#             y[1, total] = action_lat
#             y[2, total] = action_lon
#         end
#     end
#     y = y[:, 1:total]::Matrix{Float64}
#     X = X[1:total, :]::Matrix{Float64}

#     # TODO(tim): build a forest whose nodes are MvNormals
#     ensemble = build_forest(y, X, ntrees, build_tree_params, partial_sampling)

#     DynamicForestBehavior(ensemble, indicators)
# end

# end # end module

module DynamicForestBehaviors

using AutomotiveDrivingModels

using RandomForestBehaviors.MvDecisionTrees

import AutomotiveDrivingModels: AbstractVehicleBehavior, select_action, calc_action_loglikelihood, train, observe

export
    DynamicForestBehavior,

    select_action,
    calc_action_loglikelihood,
    train

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

function select_action(
    basics::FeatureExtractBasicsPdSet,
    behavior::DynamicForestBehavior,
    carind::Int,
    validfind::Int
    )

    # pick a tree at random
    tree_index = rand(1:length(behavior.forest.trees))

    # sample from the MvNorm for said tree
    Features.observe!(behavior.X, basics, carind, validfind, behavior.indicators)
    leaf = apply_tree(behavior.forest.trees[tree_index], behavior.X)::MvNormLeaf
    normal  = leaf.m

    Distributions._rand!(normal, behavior.A)

    action_lat = behavior.A[1]
    action_lon = behavior.A[2]

    (action_lat, action_lon)
end

function _calc_action_loglikelihood(
    behavior::DynamicForestBehavior,
    action_lat::Float64,
    action_lon::Float64
    )

    behavior.A[1] = action_lat
    behavior.A[2] = action_lon

    ntrees = length(behavior.forest.trees)
    log_ntrees = log(ntrees)

    total_probability_density = 0.0
    logl = 0.0
    for tree in behavior.forest.trees
        leaf = apply_tree(tree, behavior.X)::MvNormLeaf
        normal  = leaf.m

        p = pdf(normal, behavior.A)/ntrees

        if total_probability_density == 0.0
            logl = logpdf(normal, behavior.A) - log_ntrees
        elseif p < total_probability_density
            # NOTE: log(a + b) = log a + log(1 + b/a)
            logl = logl + log1p(p/total_probability_density)
        else
            # NOTE: log(a + b) = log b + log(1 + a/b)
            logl = (logpdf(normal, behavior.A) - log_ntrees) + log1p(total_probability_density/p)
        end
        total_probability_density += p
    end

    logl
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
    Features.observe!(behavior.X, basics, carind, frameind, behavior.indicators)

    _calc_action_loglikelihood(behavior, action_lat, action_lon)
end
function calc_action_loglikelihood(
    behavior::DynamicForestBehavior,
    features::DataFrame,
    frameind::Integer,
    )

    action_lat = features[frameind, symbol(FUTUREDESIREDANGLE_250MS)]::Float64
    action_lon = features[frameind, symbol(FUTUREACCELERATION_250MS)]::Float64

    for (i,feature) in enumerate(behavior.indicators)
        v = features[frameind, symbol(feature)]::Float64
        behavior.X[i] = clamp(v, -FEATURE_EXTREMUM, FEATURE_EXTREMUM)
    end

    _calc_action_loglikelihood(behavior, action_lat, action_lon)
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
    n_split_tries::Integer=50,
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
        elseif k == :n_split_tries
            n_split_tries = v
        else
            warn("Train DynamicForestBehavior: ignoring $k")
        end
    end

    build_tree_params = BuildTreeParameters(
        int(sqrt(length(indicators))),
        max_depth,
        min_samples_split,
        min_samples_leaves,
        min_split_improvement,
        n_split_tries,
        LossFunction_MSE,
        MvNormLeaf
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