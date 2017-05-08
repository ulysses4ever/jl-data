abstract SMDP
valueiteration(mdp::SMDP) = error("Not implemented")

abstract Clock
type FClock <: Clock
    time::Int
end
type IClock <: Clock end

type SimpleMDP{T <: Clock} <: SMDP
    R::Vector
    P::SparseMatrixCSC{Float64,Int64}
    indvec::Vector
    β::Float64
    time::T
end

function SimpleMDP{T}(R::SparseMatrixCSC{Float64,Int64},
                   P::SparseMatrixCSC{Float64,Int64},
                   indvec::Vector,
                   β::Float64,
                   time::T)
  # convert future state dependent rewards into future
  #   state independent ones
  ER = sum(R .* P, 2)
  SimpleMDP(ER, P, indvec, β, time)
end

# ***** Discrete State Dynamic Programming *****

function valueiteration(mdp::SimpleMDP{IClock};
  Vstart=zeros(Float64, length(mdp.indvec)), eps=1e-6)
    n = length(mdp.indvec)
    V0 = copy(Vstart)
    V1 = copy(Vstart)
    policy_t = zeros(Int, n)

    β = mdp.β
    P = mdp.P
    R = mdp.R
    indvec = mdp.indvec

    while true
        θ = R .+ β*P*V1
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

    β = mdp.β
    P = mdp.P
    R = mdp.R
    indvec = mdp.indvec

    i = n
    while i > 0
        θ = R + β*P*V1
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

    β = mdp.β
    P = mdp.P
    R = mdp.R
    indvec = mdp.indvec

    while true
        V = (I - β*P[policy_t, :])\R[policy_t]
        copy!(policy_t1, policy_t)

        # Greedy Policy Improvement
        θ = R + β*P*V
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

# ***** Continuous State Dynamic Programming *****

type ApproxFunc
  fn::Function
  params
end

function predict(x,f::ApproxFunc)
  n = length(x)
  out = Array(Float64, n)
  for i=1:n
    f.fn(x[i],f.params)
  end
  out
end

function residuals(x, f::ApproxFunc)
  x .- predict(x, f)
end

function fittedvalueiteration(mdp::SimpleMDP{IClock}, func)

end
