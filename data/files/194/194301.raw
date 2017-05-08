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

type GindeleRandomForestBehavior{F} <: AbstractVehicleBehavior
    model_μ::Ensemble
    model_Σ::Ensemble

    targets::ModelTargets{F}
    indicators::Vector{F}
    extractor::FeaturesNew.FeatureSubsetExtractor
    processor::FeaturesNew.DataPreprocessor
    action_clamper::FeaturesNew.DataClamper

    # preallocated memory
    μ::Vector{Float64} # [2]
    Σ::Matrix{Float64} # [2×2]

    function GindeleRandomForestBehavior(
        model_μ::Ensemble,
        model_Σ::Ensemble,
        targets::ModelTargets{AbstractFeature},
        indicators::Vector{AbstractFeature},
        )

        retval = new()

        retval.model_μ = model_μ
        retval.model_Σ = model_Σ

        retval.μ = Array(Float64, 2)
        retval.Σ = Array(Float64, 2, 2)

        retval.targets = targets
        retval.indicators = indicators
        retval.processor = FeaturesNew.ChainedDataProcessor(retval.indicators)
        retval.action_clamper = FeaturesNew.DataClamper(Array(Float64, 2), [-Inf, -Inf], [Inf, Inf])

        retval
    end
    function GindeleRandomForestBehavior(
        model_μ::Ensemble,
        model_Σ::Ensemble,
        targets::ModelTargets{FeaturesNew.AbstractFeature},
        extractor::FeaturesNew.FeatureSubsetExtractor,
        processor::FeaturesNew.ChainedDataProcessor,
        action_clamper::FeaturesNew.DataClamper,
        )

        retval = new()

        retval.model_μ = model_μ
        retval.model_Σ = model_Σ

        retval.targets = targets
        # copy the processor and ensure that the copied io arrays match up
        retval.extractor = FeaturesNew.FeatureSubsetExtractor(deepcopy(extractor.x), extractor.indicators)
        retval.processor = deepcopy(processor, retval.extractor)
        retval.action_clamper = FeaturesNew.DataClamper(Array(Float64, 2),
                                   deepcopy(action_clamper.f_lo),
                                   deepcopy(action_clamper.f_hi))

        retval.μ = Array(Float64, 2)
        retval.Σ = Array(Float64, 2, 2)

        retval
    end
end
type GRF_TrainParams <: AbstractVehicleBehaviorTrainParams

    targets::ModelTargets
    indicators::Union{Vector{AbstractFeature}, Vector{FeaturesNew.AbstractFeature}}

    ntrees::Int # number of trees in the forest
    max_tree_depth::Int # max depth for trees in the forest
    min_samples_split::Int # min num samples in a node for split to be considered
    min_samples_leaves::Int # min num samples in resulting leaves for split to be done
    n_split_tries::Int # number of random split attempts
    n_PCA_features::Int # 0 means do not use PCA features, otherwise it is the number of PCA features to use

    min_split_improvement::Float64 # minimum improvement for split to be accepted
    partial_sampling::Float64 # percentage of dataset to sample

    function GRF_TrainParams(;
        targets::ModelTargets = ModelTargets{AbstractFeature}(FUTUREDESIREDANGLE_250MS, FUTUREACCELERATION_250MS),
        indicators::Union{Vector{AbstractFeature}, Vector{FeaturesNew.AbstractFeature}} = [
                        POSFY, YAW, SPEED, DELTA_SPEED_LIMIT, VELFX, VELFY, SCENEVELFX, TURNRATE,
                        D_CL, D_ML, D_MR, TIMETOCROSSING_LEFT, TIMETOCROSSING_RIGHT,
                        N_LANE_L, N_LANE_R, HAS_LANE_L, HAS_LANE_R, ACC, ACCFX, ACCFY,
                        A_REQ_STAYINLANE,
                     ],
        ntrees::Integer=10,
        max_tree_depth::Integer=5,
        min_samples_split::Integer=100,
        min_samples_leaves::Integer=20,
        n_split_tries::Integer=10,
        n_PCA_features::Integer=0,
        min_split_improvement::Float64=0.0,
        partial_sampling::Float64=0.7,
        )

        if eltype(indicators) <: FeaturesNew.AbstractFeature
            targets = ModelTargets{FeaturesNew.AbstractFeature}(
                            FeaturesNew.FUTUREDESIREDANGLE,
                            FeaturesNew.FUTUREACCELERATION)
        end

        retval = new()
        retval.targets = targets
        retval.indicators = indicators
        retval.ntrees = ntrees
        retval.max_tree_depth = max_tree_depth
        retval.min_samples_split = min_samples_split
        retval.min_samples_leaves = min_samples_leaves
        retval.n_split_tries = n_split_tries
        retval.n_PCA_features = n_PCA_features
        retval.min_split_improvement = min_split_improvement
        retval.partial_sampling = partial_sampling
        retval
    end
end
type GRF_PreallocatedData <: AbstractVehicleBehaviorPreallocatedData

    # the full dataset matrices pre-extracted
    X::Matrix{Float64} # [nfeatures × nframes]
    Y::Matrix{Float64} # [2 × nframes]

    extractor::FeatureSubsetExtractor
    preprocess::DataPreprocessor
    action_clamper::FeaturesNew.DataClamper

    function GRF_PreallocatedData(dset::ModelTrainingData, params::GRF_TrainParams)
        new()
    end
    function GRF_PreallocatedData(dset::ModelTrainingData2, params::GRF_TrainParams)
        retval = new()

        targets = params.targets
        indicators = params.indicators
        trainingframes = dset.dataframe
        nframes = nrow(trainingframes)
        nindicators = length(indicators)

        X = Array(Float64, nindicators, nframes) # NOTE(tim): initially indicators × nframes, we later transpose it
        Y = Array(Float64, 2, nframes)
        pull_design_and_target_matrices!(X, Y, trainingframes, targets, indicators)

        ######################

        extractor = FeatureSubsetExtractor(Array(Float64, nindicators), indicators)
        preprocess = ChainedDataProcessor(extractor)
        push!(preprocess, X, FeaturesNew.DataNaReplacer, extractor.indicators)
        FeaturesNew.process!(X, preprocess.processors[end]) # process in place
        push!(preprocess, X, FeaturesNew.DataScaler) # ensure data is standardized before running PCA
        FeaturesNew.process!(X, preprocess.processors[end]) # process in place

        if params.n_PCA_features > 0
            # Add a PCA scaler

            push!(preprocess, X, FeaturesNew.DataLinearTransform, params.n_PCA_features)

            Z = Array(Float64, params.n_PCA_features, nframes)
            Z = FeaturesNew.process!(Z, X, preprocess.processors[end])

            retval.X = Z # use the smaller one
        else
            retval.X = X
        end

        retval.Y = Y
        retval.extractor = extractor
        retval.preprocess = preprocess
        retval.action_clamper = FeaturesNew.DataClamper(
                Array(Float64, 2),
                vec(minimum(Y, 2)),
                vec(maximum(Y, 2))
            )

        retval
    end
end

function preallocate_learning_data(
    dset::ModelTrainingData,
    params::GRF_TrainParams)

    GRF_PreallocatedData(dset, params)
end
function preallocate_learning_data(
    dset::ModelTrainingData2,
    params::GRF_TrainParams)

    GRF_PreallocatedData(dset, params)
end

function _calc_mvnormal(behavior::GindeleRandomForestBehavior)

    apply_forest!(behavior.μ, behavior.model_μ, behavior.processor.z)
    apply_forest!(behavior.Σ, behavior.model_Σ, behavior.processor.z)

    MvNormal(behavior.μ, behavior.Σ)
end

function select_action(
    basics::FeatureExtractBasicsPdSet,
    behavior::GindeleRandomForestBehavior,
    carind::Int,
    validfind::Int
    )

    Features.observe!(behavior.processor.x, basics, carind, validfind, behavior.indicators, replace_na=true)
    FeaturesNew.process!(behavior.processor)

    normal = _calc_mvnormal(behavior)

    Distributions._rand!(normal, behavior.action_clamper.x)
    FeaturesNew.process!(behavior.action_clamper)

    action_lat = behavior.action_clamper.x[1]
    action_lon = behavior.action_clamper.x[2]

    (action_lat, action_lon)
end
function select_action(
    behavior::GindeleRandomForestBehavior,
    runlog::RunLog,
    sn::StreetNetwork,
    colset::UInt,
    frame::Int
    )

    FeaturesNew.observe!(behavior.extractor, runlog, sn, colset, frame)
    FeaturesNew.process!(behavior.processor)

    normal = _calc_mvnormal(behavior)

    Distributions._rand!(normal, behavior.action_clamper.x)
    FeaturesNew.process!(behavior.action_clamper)

    action_lat = behavior.action_clamper.x[1]
    action_lon = behavior.action_clamper.x[2]

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

    behavior.action_clamper.x[1] = action_lat
    behavior.action_clamper.x[2] = action_lon

    Features.observe!(behavior.processor.x, basics, carind, validfind, behavior.indicators, replace_na=true)
    FeaturesNew.process!(behavior.processor)

    normal = _calc_mvnormal(behavior)
    logpdf(normal, behavior.action_clamper.x)
end
function calc_action_loglikelihood(
    behavior::GindeleRandomForestBehavior,
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

    behavior.action_clamper.x[1] = action_lat
    behavior.action_clamper.x[2] = action_lon

    FeaturesNew.observe!(behavior.extractor, runlog, sn, colset, frame)
    FeaturesNew.process!(behavior.processor)

    normal = _calc_mvnormal(behavior)
    logpdf(normal, behavior.action_clamper.x)
end
function calc_action_loglikelihood(
    behavior::GindeleRandomForestBehavior,
    features::DataFrame,
    frameind::Integer,
    )

    behavior.action_clamper.x[1] = features[frameind, symbol(behavior.targets.lat)]::Float64
    behavior.action_clamper.x[2] = features[frameind, symbol(behavior.targets.lon)]::Float64

    FeaturesNew.observe!(behavior.extractor, features, frameind)
    FeaturesNew.process!(behavior.processor)

    apply_forest!(behavior.μ, behavior.model_μ, behavior.processor.z)
    apply_forest!(behavior.Σ, behavior.model_Σ, behavior.processor.z)

    mvnorm_model = MvNormal(behavior.μ, behavior.Σ)
    logpdf(mvnorm_model, behavior.action_clamper.x)
end

function train(
    training_data::ModelTrainingData,
    preallocated_data::GRF_PreallocatedData,
    params::GRF_TrainParams,
    fold::Int,
    fold_assignment::FoldAssignment,
    match_fold::Bool,
    )

    targets = params.targets
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
            !any(feature->isnan(trainingframes[row,symbol(feature)]), indicators) &&
            is_in_fold(fold, fold_assignment.frame_assignment[row], match_fold)

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

    GindeleRandomForestBehavior{AbstractFeature}(μ, Σ, targets, convert(Vector{AbstractFeature}, indicators))
end
function train(
    training_data::ModelTrainingData2,
    preallocated_data::GRF_PreallocatedData,
    params::GRF_TrainParams,
    fold::Int,
    fold_assignment::FoldAssignment,
    match_fold::Bool,
    )

    targets = params.targets
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

    X_orig = preallocated_data.X # NOTE: already preprocessed and everything
    Y_orig = preallocated_data.Y

    nframes = calc_fold_size(fold, fold_assignment.frame_assignment, match_fold)
    X = Array(Float64, nframes, size(X_orig, 1)) # NOTE: this is transpose of X_orig
    y = Array(Float64, 2, nframes)

    i = 0
    for (frame, fold_a) in enumerate(fold_assignment.frame_assignment)
        if is_in_fold(fold, fold_a, match_fold)
            i += 1

            for j in 1 : size(X_orig, 1)
                X[i,j] = X_orig[j,frame]
            end

            y[1,i] = Y_orig[1,frame]
            y[2,i] = Y_orig[2,frame]
        end
    end
    @assert(i == nframes)

    μ = build_forest(y, X, ntrees, build_tree_params, partial_sampling)

    mean_vector = Array(Float64, 2)
    for i = 1 : size(y, 1)
        y[:,i] -= apply_forest!(mean_vector, μ, vec(X[i,:])) # subtract the predicted mean
    end

    build_tree_params = BuildTreeParameters(
        ntrees, max_tree_depth, min_samples_split, min_samples_leaves,
        min_split_improvement, n_split_tries, LossFunction_MSE, CovLeaf)

    Σ = build_forest(y, X, ntrees, build_tree_params, partial_sampling)

    extractor = preallocated_data.extractor
    preprocess = preallocated_data.preprocess
    action_clamper = preallocated_data.action_clamper
    GindeleRandomForestBehavior{FeaturesNew.AbstractFeature}(μ, Σ, targets, extractor, preprocess, action_clamper)
end

end # end module
