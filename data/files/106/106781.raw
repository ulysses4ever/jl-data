abstract SMDP
valueiteration(mdp::SMDP) = error("Not implemented")

abstract Clock
type FClock <: Clock
    time::Int
end
type IClock <: Clock end

type SimpleMDP{T <: Clock} <: SMDP
    R::SparseMatrixCSC{Float64,Int64}
    P::SparseMatrixCSC{Float64,Int64}
    indvec::Vector
    β::Float64
    time::T
end

type GraphMDP <: SMDP
end

type EnsembleMDP{T <: SMDP}
    mdp::Vector{T}
end

function valueiteration(mdp::SimpleMDP{IClock};
  Vstart=zeros(Float64, length(mdp.indvec)), eps=1e-6)
    n = length(mdp.indvec)
    V0 = copy(Vstart)
    V1 = copy(Vstart)
    policy_t = zeros(Int, n)

    ER = sum(mdp.R .* mdp.P,2)
    β = mdp.β
    P = mdp.P
    indvec = mdp.indvec

    while true
        θ = ER + β*P*V1
        copy!(V0, V1)

        lb = 1
        ub = indvec[1]
        policy_t[1] = indmax(θ[lb:ub])
        V1[1] = θ[policy_t[1]]
        for i=2:n
            lb = ub+1
            ub = indvec[i]
            policy_t[i] = indmax(θ[lb:ub]) + (lb-1)
            V1[i] = θ[policy_t[i]]
        end
        if sum((V1 - V0).^2) < β*eps/(1-β)
            break
        end
    end
    (V1, policy_t)
end

function valueiteration(mdp::SimpleMDP{FClock};
  Vstart=zeros(Float64, length(mdp.indvec)), eps=1e-6)
    n = mdp.time.time
    m = length(mdp.indvec)
    V0 = copy(Vstart)
    V1 = copy(Vstart)
    V = zeros(Float64, n,m)
    V[1,:] = V1
    policy_t = zeros(Int, n,m)

    ER = sum(mdp.R .* mdp.P,2)
    P = mdp.P
    β = mdp.β
    indvec = mdp.indvec

    i = n
    while i > 0
        θ = ER + β*P*V1
        copy!(V0, V1)

        lb = 1
        ub = indvec[1]
        policy_t[i,1] = indmax(θ[lb:ub])
        V1[1] = θ[policy_t[i,1]]
        for j=2:m
            lb = ub+1
            ub = indvec[j]
            policy_t[i,j] = indmax(θ[lb:ub]) + (lb-1)
            V1[j] = θ[policy_t[i,j]]
        end
        V[i,:] = V1
        i-=1
    end
    (V, policy_t)
end

function policyiteration(mdp::SimpleMDP{IClock};
  Pstart=mdp.indvec, eps=1e-6)
    n = length(Pstart)
    policy_t  = copy(Pstart)
    policy_t1 = ones(n)

    I = eye(n)
    V = zeros(n)

    ER = sum(mdp.R .* mdp.P,2)
    P = mdp.P
    β = mdp.β
    indvec = mdp.indvec

    while true
        V = (I - β*P[policy_t, :])\ER[policy_t]
        copy!(policy_t1, policy_t)

        # Greedy Policy Improvement
        θ = ER + β*P*V
        lb = 1
        ub = indvec[1]
        policy_t[1] = indmax(θ[lb:ub])
        for i=2:n
            lb = ub+1
            ub = indvec[i]
            policy_t[i] = indmax(θ[lb:ub]) + (lb-1)
        end
        if policy_t == policy_t1
          break
         end
    end
    (V, policy_t)
end
