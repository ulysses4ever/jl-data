module DynamicForestBehaviors

using AutomotiveDrivingModels

using RandomForestBehaviors.MvDecisionTrees
using Distributions.MvNormal

import AutomotiveDrivingModels: AbstractVehicleBehavior, select_action, calc_action_loglikelihood, train, observe, train_special

export
    DynamicForestBehavior,
    AutoregressiveMvNormLeaf,

    select_action,
    calc_action_loglikelihood,
    train

DEFAULT_AUTOREGRESSION_CONSTANT = 0.5
DEFAULT_NUM_AUTOREGRESSION_PREDICTORS = 3
DEFAULT_NUM_PREDICTOR_SAMPLES = 10

################################################################

immutable AutoregressiveMvNormLeaf <: MvDecisionTrees.Leaf
    A::Matrix{Float64} # regression matrix A = UΦᵀ(ΦΦᵀ + γI)⁻¹ where γ is a ridge regularization param, U is column-wise targets, Φ is column-wise features
    m::MvNormal        # μ = Aϕ must be overwritten on each use
    predictor_indeces::Vector{Int} # indeces of predictors
end

function _regress_on_predictor_subset{T<:FloatingPoint, S<:Real}(
    data::MvDecisionTrees.TreeData{T,S},
    assignment_id::Int,
    Γ::Matrix{T}, # ϕ+1 × ϕ+1 diagonal γ matrix (preallocated)
    U::Matrix{T}, #   o × m
    Φ::Matrix{T}, # ϕ+1 × m (is overwritten)
    A::Matrix{T}, #   o × ϕ+1 (is overwritten)
    predictor_indeces::Vector{Int}, # length ϕ
    )

    #=
    Returns the loss when using this predictor set
    Overwrites Φ
    =#

    n = size(data.X,1)
    o, m = size(U)
    ϕ = length(predictor_indeces)
    @assert(size(Φ,1) == ϕ+1)
    @assert(size(Φ,2) == m)
    @assert(size(Γ,1) == size(Γ,2) == ϕ+1 )

    u_index = 0
    for i in 1 : n
        if data.assignment[i] == assignment_id
            u_index += 1
            for (j,k) in enumerate(predictor_indeces)
                Φ[j,u_index] = data.X[i,k] # features : [nrows, nfeatures], Φ: [nfeatures, nrows]
            end
            Φ[ϕ+1,u_index] = 1.0 # constant 1-predictor
        end
    end

    # regress

    A[:] = U*Φ'/(Φ*Φ' + Γ)

    # println("inner")
    # println("\tA:")
    # for i = 1 : size(A,1)
    #     println("\t", A[i,:])
    # end
    # println("\tU:")
    # for i = 1 : size(U,1)
    #     println("\t", U[i,:])
    # end
    # println("\tΦ:")
    # for i = 1 : size(Φ,1)
    #     println("\t", Φ[i,:])
    # end

    # calc residual loss (square deviation)

    loss = 0.0
    for i in 1 : n
        if data.assignment[i] == assignment_id
            for j in 1 : o
                r = data.Y[j,i] - A[j,ϕ+1]
                for k in 1 : ϕ
                    r -= A[j,k]*data.X[i,predictor_indeces[k]]
                end
                loss += r*r # squared error
            end
        end
    end

    loss
end
function MvDecisionTrees.build_leaf{T<:FloatingPoint, S<:Real}(::Type{AutoregressiveMvNormLeaf},
    data::MvDecisionTrees.TreeData{T,S},
    assignment_id::Int,
    γ::T=DEFAULT_AUTOREGRESSION_CONSTANT, # ridge-regularization parameter
    n_autoregression_predictors::Int = DEFAULT_NUM_AUTOREGRESSION_PREDICTORS,
    n_random_predictor_samples::Int = DEFAULT_NUM_PREDICTOR_SAMPLES,
    )

    #=
    Fit the regression matrix A = UΦᵀ(ΦΦᵀ + γI)⁻¹
       γ is a ridge regularization param ≥ 0
         0 → least squares
         large γ → increased penalty on regression coefficients
       U is column-wise targets
       Φ is column-wise features plus a constant 1-feature

    This function picks a set of 'n_autoregression_predictors' predictors used to regress on the targets
    This is done 'n_random_predictor_samples' times
    The best in terms of residual error is kept
    The covariance matrix is static and computed based on the final residual errors
    =#

    @assert(n_autoregression_predictors ≥ 0)
    @assert(n_random_predictor_samples > 0)

    n, o, p = size(data)
    id_count = MvDecisionTrees.get_id_count(data, assignment_id)
    @assert(id_count > 0)

    ##################################
    # pull target matrix

    U = Array(T, o, id_count) # column-wise contatenation of target variables

    u_index = 0
    for i in 1 : n
        if data.assignment[i] == assignment_id
            u_index += 1
            for j in 1 : o
                U[j,u_index] = data.Y[j,i]
            end
        end
    end

    #################################
    # pull predictor matrix

    ϕ = min(n_autoregression_predictors, p) # number of real features
    Φ = Array(T, ϕ+1, id_count) # column-wise contatenation of predictors (also including constant 1-predictor)
    Γ = diagm(fill(γ, (ϕ+1)))
    A = Array(T, o, ϕ+1)
    predictor_indeces = Array(Int, ϕ)

    if ϕ == 0
        _regress_on_predictor_subset(data, assignment_id, Γ, U, Φ, A, predictor_indeces) # just solve for A
    else
        # pick several samples of predictor_indeces
        temp_A = deepcopy(A)
        temp_predictor_indeces = deepcopy(predictor_indeces)
        best_loss = Inf

        # println("tempA")
        # println(temp_A)
        # println("\n")

        for i = 1 : n_random_predictor_samples
            MvDecisionTrees._reservoir_sample!(temp_predictor_indeces, p, ϕ)
            loss = _regress_on_predictor_subset(data, assignment_id, Γ, U, Φ, temp_A, temp_predictor_indeces)
            if loss < best_loss
                best_loss = loss
                copy!(A, temp_A)
                copy!(predictor_indeces, temp_predictor_indeces)
            end

            # println(i, "   ", loss, "   ", best_loss)
            # println(temp_A)
            # println("temp pred inds: ", temp_predictor_indeces)
            # println("pred inds: ", predictor_indeces)
            # println("")
        end

        # in case we found nothing
        if isinf(best_loss)
            fill!(A, 0.0)
            fill!(predictor_indeces, 1)
        end
    end

    # println("A")
    # println(A)
    # println(predictor_indeces)
    # println("")

    ###########################################################3
    # calc covariance

    Σ = zeros(T, o, o)
    r_vec = Array(Float64, o)

    # obtain upper triangle
    for i in 1 : n
        if data.assignment[i] == assignment_id

            for j in 1 : o
                r_vec[j] = data.Y[j,i] - A[j,ϕ+1]
                for k in 1 : ϕ
                    r_vec[j] -= A[j,k]*data.X[i,predictor_indeces[k]]
                end
            end

            for a in 1 : o
                for b in a : o
                    Σ[a,b] += r_vec[a] * r_vec[b]
                end
            end
        end
    end

    if id_count < 2
        warn("Not enough samples to build a covariance matrix")
        for i in 1 : o
            Σ[i,i] = 1.0
        end
    else
        for i in 1 : o*o
            @assert(!isnan(Σ[i]))
            Σ[i] /= (id_count-1)
        end
        MvDecisionTrees._diagonal_shrinkage!(Σ)
        for a in 2:o
            for b in 1:a-1
                Σ[a,b] = Σ[b,a]
            end
        end
    end


    AutoregressiveMvNormLeaf(A, MvNormal(Array(T, o), Σ), predictor_indeces)
end

################################################################

type DynamicForestBehavior <: AbstractVehicleBehavior
    forest::Ensemble
    indicators::Vector{AbstractFeature}

    # preallocated memory
    X::Vector{Float64} # [n_indicators]
    ϕ::Vector{Float64} # [n_predictors+1] (last one is always 1.0)
    A::Vector{Float64} # [2]

    function DynamicForestBehavior(
        forest::Ensemble,
        indicators::Vector{AbstractFeature},
        n_predictors::Int,
        )

        X = Array(Float64, length(indicators))
        ϕ = Array(Float64, n_predictors+1)
        A = Array(Float64, 2)

        new(forest, indicators, X, ϕ, A)
    end
end

function _condition_predictor_mean!(
    normal::MvNormal,
    predictor_indeces::Vector{Int},
    A::Matrix{Float64},
    behavior::DynamicForestBehavior,
    )

    X = behavior.X
    ϕ = behavior.ϕ

    for (i,p) in enumerate(predictor_indeces)
        ϕ[i] = X[p]
    end
    ϕ[end] = 1.0

    normal.μ[:] = A * ϕ

    nothing
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
    X = behavior.X
    Features.observe!(X, basics, carind, validfind, behavior.indicators, replace_na=true)

    leaf = apply_tree(behavior.forest.trees[tree_index], behavior.X)::AutoregressiveMvNormLeaf
    _condition_predictor_mean!(leaf.m, leaf.predictor_indeces, leaf.A, behavior)

    Distributions._rand!(leaf.m, behavior.A)

    action_lat = behavior.A[1]
    action_lon = behavior.A[2]

    (action_lat, action_lon)
end

function _calc_action_loglikelihood(
    behavior::DynamicForestBehavior,
    action_lat::Float64,
    action_lon::Float64
    )

    # NOTE(tim): this assumes behavior.X has already been filled

    behavior.A[1] = action_lat
    behavior.A[2] = action_lon

    ntrees = length(behavior.forest.trees)
    log_ntrees = log(ntrees)

    total_probability_density = 0.0
    logl = 0.0
    for tree in behavior.forest.trees
        leaf = apply_tree(tree, behavior.X)::AutoregressiveMvNormLeaf
        _condition_predictor_mean!(leaf.m, leaf.predictor_indeces, leaf.A, behavior)
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

    Features.observe!(behavior.X, basics, carind, validfind, behavior.indicators, replace_na=true)

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
        if isinf(v)
            warn("DynamicForestBehaviors.calc_action_loglikelihood: INF v!")
        end
        behavior.X[i] = v
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
    autogression_coef::Float64=0.1,
    n_autoregression_predictors=2,
    n_random_predictor_samples=10,

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
        elseif k == :autogression_coef
            autogression_coef = v
        elseif k == :n_autoregression_predictors
            n_autoregression_predictors = v
        elseif k == :n_random_predictor_samples
            n_random_predictor_samples = v
        else
            warn("Train DynamicForestBehavior: ignoring $k")
        end
    end

    global DEFAULT_AUTOREGRESSION_CONSTANT = autogression_coef
    global DEFAULT_NUM_AUTOREGRESSION_PREDICTORS = n_autoregression_predictors
    global DEFAULT_NUM_PREDICTOR_SAMPLES = n_random_predictor_samples

    build_tree_params = BuildTreeParameters(
        int(sqrt(length(indicators))),
        max_depth,
        min_samples_split,
        min_samples_leaves,
        min_split_improvement,
        n_split_tries,
        LossFunction_MSE,
        AutoregressiveMvNormLeaf
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
                v = trainingframes[row, symbol(feature)]
                if isinf(v)
                    warn("DynamicForestBehaviors.calc_action_loglikelihood: INF v!")
                end
                X[total, col] = v
            end

            y[1, total] = action_lat
            y[2, total] = action_lon
        end
    end
    y = y[:, 1:total]::Matrix{Float64}
    X = X[1:total, :]::Matrix{Float64}

    ensemble = build_forest(y, X, ntrees, build_tree_params, partial_sampling)
    DynamicForestBehavior(ensemble, convert(Vector{AbstractFeature}, indicators), n_autoregression_predictors)
end

end # end module