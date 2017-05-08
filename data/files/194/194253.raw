module GindeleRandomForestBehaviors

using AutomotiveDrivingModels

using RandomForestBehaviors.MvDecisionTrees

import AutomotiveDrivingModels: AbstractVehicleBehavior, select_action, calc_action_loglikelihood, train, observe

export
    GindeleRandomForestBehavior,

    select_action,
    calc_action_loglikelihood,
    train

#################

# function append_to_python_searth_path( str::String )
#     unshift!(PyVector(pyimport("sys")["path"]), str) 
# end
# append_to_python_searth_path("/home/tim/Documents/wheelerworkspace/Bosch/model/")
# @pyimport random_forests as random_forests

#################

const FEATURE_EXTREMUM = 1000.0

const TRAIN_MAX_DEPTH = 5
const TRAIN_MIN_SAMPLES_SPLIT = 100
const TRAIN_MIN_SAMPLES_LEAVES = 20
const TRAIN_MIN_SPLIT_IMPROVEMENT = 0.0
const TRAIN_N_TREES = 10
const TRAIN_PARTIAL_SAMPLING = 0.7

type GindeleRandomForestBehavior <: AbstractVehicleBehavior
    model_μ::Ensemble
    model_Σ::Ensemble
    indicators::Vector{AbstractFeature}
end

function _calc_mvnormal(
    basics::FeatureExtractBasicsPdSet,
    behavior::GindeleRandomForestBehavior,
    carind::Int,
    frameind::Int
    )

    indicators = behavior.indicators
    observations = Features.observe(basics, carind, frameind, indicators)

    X = Array(Float64, length(indicators))
    for (i,feature) in enumerate(indicators)
        X[i] = clamp(observations[symbol(feature)], -FEATURE_EXTREMUM, FEATURE_EXTREMUM)
    end

    μ = vec(apply_forest(behavior.model_μ, X)) #vec(behavior.model_μ[:predict](X))
    Σ = apply_forest(behavior.model_Σ, X)

    # println(μ, "  ", typeof(μ))
    # println(Σ, "  ", typeof(Σ))

    # MvNormal(μ, full(behavior.model_Σ.Σ))
    MvNormal(μ,Σ)
end

function select_action(
    basics::FeatureExtractBasicsPdSet,
    behavior::GindeleRandomForestBehavior,
    carind::Int,
    validfind::Int
    )

    normal = _calc_mvnormal(basics, behavior, carind, validfind)

    action = rand(normal)
    logl = logpdf(normal, action)

    action_lat = action[1]
    action_lon = action[2]

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

    normal = _calc_mvnormal(basics, behavior, carind, validfind)
    logpdf(normal, [action_lat, action_lon])
end

function train(::Type{GindeleRandomForestBehavior}, trainingframes::DataFrame;
    indicators::Vector{AbstractFeature} = [
                    POSFY, YAW, SPEED, DELTA_SPEED_LIMIT, VELFX, VELFY, SCENEVELFX, TURNRATE,
                    D_CL, D_ML, D_MR, TIMETOCROSSING_LEFT, TIMETOCROSSING_RIGHT,
                    N_LANE_L, N_LANE_R, HAS_LANE_L, HAS_LANE_R, ACC, ACCFX, ACCFY,
                    A_REQ_STAYINLANE,
                    HAS_FRONT, D_X_FRONT, D_Y_FRONT, V_X_FRONT, V_Y_FRONT, TTC_X_FRONT,
                    A_REQ_FRONT, TIMEGAP_X_FRONT,
                    HAS_REAR, D_X_REAR, D_Y_REAR, V_X_REAR, V_Y_REAR, TTC_X_REAR,
                    A_REQ_REAR,
                    D_X_LEFT, D_Y_LEFT, V_X_LEFT, V_Y_LEFT, YAW_LEFT,
                    D_X_RIGHT, D_Y_RIGHT, V_X_RIGHT, V_Y_RIGHT, YAW_RIGHT, A_REQ_RIGHT,
                    PASTTURNRATE250MS, PASTACC250MS, PASTVELFY250MS, PASTD_CL250MS,
                    PASTTURNRATE500MS, PASTACC500MS, PASTVELFY500MS, PASTD_CL500MS,
                    PASTTURNRATE750MS, PASTACC750MS, PASTVELFY750MS, PASTD_CL750MS,
                    PASTTURNRATE1S, PASTACC1S, PASTVELFY1S, PASTD_CL1S,
                    TIME_CONSECUTIVE_BRAKE, TIME_CONSECUTIVE_ACCEL, TIME_CONSECUTIVE_THROTTLE,
                        MAXACCFX500MS,     MAXACCFX750MS,     MAXACCFX1S,     MAXACCFX1500MS,     MAXACCFX2S,     MAXACCFX2500MS,     MAXACCFX3S,     MAXACCFX4S,
                        MAXACCFY500MS,     MAXACCFY750MS,     MAXACCFY1S,     MAXACCFY1500MS,     MAXACCFY2S,     MAXACCFY2500MS,     MAXACCFY3S,     MAXACCFY4S,
                     MAXTURNRATE500MS,  MAXTURNRATE750MS,  MAXTURNRATE1S,  MAXTURNRATE1500MS,  MAXTURNRATE2S,  MAXTURNRATE2500MS,  MAXTURNRATE3S,  MAXTURNRATE4S,
                       MEANACCFX500MS,    MEANACCFX750MS,    MEANACCFX1S,    MEANACCFX1500MS,    MEANACCFX2S,    MEANACCFX2500MS,    MEANACCFX3S,    MEANACCFX4S,
                       MEANACCFY500MS,    MEANACCFY750MS,    MEANACCFY1S,    MEANACCFY1500MS,    MEANACCFY2S,    MEANACCFY2500MS,    MEANACCFY3S,    MEANACCFY4S,
                    MEANTURNRATE500MS, MEANTURNRATE750MS, MEANTURNRATE1S, MEANTURNRATE1500MS, MEANTURNRATE2S, MEANTURNRATE2500MS, MEANTURNRATE3S, MEANTURNRATE4S,
                        STDACCFX500MS,     STDACCFX750MS,     STDACCFX1S,     STDACCFX1500MS,     STDACCFX2S,     STDACCFX2500MS,     STDACCFX3S,     STDACCFX4S,
                        STDACCFY500MS,     STDACCFY750MS,     STDACCFY1S,     STDACCFY1500MS,     STDACCFY2S,     STDACCFY2500MS,     STDACCFY3S,     STDACCFY4S,
                     STDTURNRATE500MS,  STDTURNRATE750MS,  STDTURNRATE1S,  STDTURNRATE1500MS,  STDTURNRATE2S,  STDTURNRATE2500MS,  STDTURNRATE3S,  STDTURNRATE4S
                 ],
    args::Dict=Dict{Symbol,Any}()
    )

    for (k,v) in args
        if k == :indicators
            indicators = v
        else
            warn("Train GindeleRandomForestBehavior: ignoring $k")
        end
    end
    
    build_tree_params = BuildTreeParameters(
        nsubfeatures=int(sqrt(length(indicators))),
        max_depth=TRAIN_MAX_DEPTH,
        min_samples_split=TRAIN_MIN_SAMPLES_SPLIT,
        min_samples_leaves=TRAIN_MIN_SAMPLES_LEAVES,
        min_split_improvement=TRAIN_MIN_SPLIT_IMPROVEMENT)

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

    build_tree_params.loss_function = :mse
    μ = build_forest(y, X, TRAIN_N_TREES, build_tree_params, TRAIN_PARTIAL_SAMPLING)
    Δ = deepcopy(y)
    for i = 1 : size(y, 1)
        Δ[:,i] -= apply_forest(μ, vec(X[i,:]))
    end
    build_tree_params.loss_function = :logl
    Σ = build_forest_covariance(Δ, X, TRAIN_N_TREES, build_tree_params, TRAIN_PARTIAL_SAMPLING)

    GindeleRandomForestBehavior(μ, Σ, indicators)
end

end # end module

# trainingframes = DataFrame(acc=[0.0,0.2,0.3], turnrate=[0.0,-0.01,0.01], speed=[29.6, 29.8,29.7], dcl=[0.0,-0.1,0.1])
# rf = train(GindeleRandomForestBehavior, trainingframes)