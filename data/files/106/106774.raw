module MDP

abstract SMDP
valueiteration(mdp::SMDP, vstart) = error("Not implemented") 

abstract Clock
type FClock <: Clock
    time::Int
end
type IClock <: Clock end

type SimpleMDP{T <: Clock} <: SMDP
    R::SparseMatrixCSC{Float64,Int64}
    P::SparseMatrixCSC{Float64,Int64}
    indvec::Vector
    beta::Float64
    time::T # time= Inf -> Infinite Horizon
end

type GraphMDP <: SMDP
end

type EnsembleMDP{T <: SMDP}
    mdp::Vector{T}
end

valueiter(mdp) = 1
policyiter(mdp) = 1

end # module
