module GindeleRandomForestBehaviors

using AutomotiveDrivingModels

using RandomForestBehaviors.MvDecisionTrees

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
    GindeleRandomForestBehavior,
    GRF_TrainParams,

    select_action,
    calc_action_loglikelihood,
    train

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
type GRF_TrainParams <: AbstractVehicleBehaviorTrainParams

    indicators::Vector{AbstractFeature}

    ntrees::Int # number of trees in the forest
    max_tree_depth::Int # max depth for trees in the forest
    min_samples_split::Int # min num samples in a node for split to be considered
    min_samples_leaves::Int # min num samples in resulting leaves for split to be done
    n_split_tries::Int # number of random split attempts

    min_split_improvement::Float64 # minimum improvement for split to be accepted
    partial_sampling::Float64 # percentage of dataset to sample
    
    function GRF_TrainParams(;
        indicators::Vector{AbstractFeature} = [
                        POSFY, YAW, SPEED, DELTA_SPEED_LIMIT, VELFX, VELFY, SCENEVELFX, TURNRATE,
                        D_CL, D_ML, D_MR, TIMETOCROSSING_LEFT, TIMETOCROSSING_RIGHT,
                        N_LANE_L, N_LANE_R, HAS_LANE_L, HAS_LANE_R, ACC, ACCFX, ACCFY,
                        A_REQ_STAYINLANE,
                     ],
        ntrees::Integer=10,
        max_tree_depth::Integer=5,
        min_samples_split::Integer=100,
        min_samples_leaves::Integer=20,
        n_split_tries::Integer=50,

        min_split_improvement::Float64=0.0,
        partial_sampling::Float64=0.7,
        )

        new(indicators, ntrees, max_tree_depth, min_samples_leaves, min_samples_split,
            n_split_tries, min_split_improvement, partial_sampling)
    end
end
type GRF_PreallocatedData <: AbstractVehicleBehaviorPreallocatedData
    # TODO(tim): put X, y, etc. into here

    function GRF_PreallocatedData(dset::ModelTrainingData, params::GRF_TrainParams)
        new()
    end
end

function preallocate_learning_data(
    dset::ModelTrainingData,
    params::GRF_TrainParams)
    
    GRF_PreallocatedData(dset, params)
end

function _calc_mvnormal(
    basics::FeatureExtractBasicsPdSet,
    behavior::GindeleRandomForestBehavior,
    carind::Int,
    validfind::Int
    )

    Features.observe!(behavior.X, basics, carind, validfind, behavior.indicators, replace_na=true)

    apply_forest!(behavior.μ, behavior.model_μ, behavior.X)
    apply_forest!(behavior.Σ, behavior.model_Σ, behavior.X)

    MvNormal(behavior.μ, behavior.Σ)
end

function select_action(
    basics::FeatureExtractBasicsPdSet,
    behavior::GindeleRandomForestBehavior,
    carind::Int,
    validfind::Int
    )

    normal = _calc_mvnormal(basics, behavior, carind, validfind)

    Distributions._rand!(normal, behavior.A)

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
        if isinf(v)
            error("GindeleRandomForestBehavior.calc_action_loglikelihood: INF v!")
        end
        behavior.X[i] = v
    end

    apply_forest!(behavior.μ, behavior.model_μ, behavior.X)
    apply_forest!(behavior.Σ, behavior.model_Σ, behavior.X)

    mvnorm_model = MvNormal(behavior.μ, behavior.Σ)
    logpdf(mvnorm_model, behavior.A)
end

function train(
    training_data::ModelTrainingData,
    preallocated_data::GRF_PreallocatedData,
    params::GRF_TrainParams,
    fold::Int,
    fold_assignment::FoldAssignment,
    match_fold::Bool,
    )

    indicators = params.indicators
    ntrees = params.ntrees
    max_tree_depth = params.max_tree_depth
    min_samples_split = params.min_samples_split
    min_samples_leaves = params.min_samples_leaves
    n_split_tries = params.n_split_tries
    min_split_improvement = params.min_split_improvement
    partial_sampling = params.partial_sampling

    #######

    build_tree_params = BuildTreeParameters(
        ntrees, max_tree_depth, min_samples_split, min_samples_leaves,
        min_split_improvement, n_split_tries, LossFunction_MSE, MeanVecLeaf)

    trainingframes = training_data.dataframe_nona
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
                v = trainingframes[row, symbol(feature)]
                if isinf(v)
                    error("DynamicForestBehaviors.calc_action_loglikelihood: INF v!")
                end
                X[total, col] = v
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
        ntrees, max_tree_depth, min_samples_split, min_samples_leaves,
        min_split_improvement, n_split_tries, LossFunction_MSE, CovLeaf)

    Σ = build_forest(y, X, ntrees, build_tree_params, partial_sampling)

    GindeleRandomForestBehavior(μ, Σ,  convert(Vector{AbstractFeature}, indicators))
end

end # end module
