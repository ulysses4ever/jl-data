# Syntax tree data structure support

export Func, Const, ConstRange, State, Binds, Var, EmptyState
export evaluate, symbol

abstract Node
typealias NodeSet Vector{Node}

abstract Func <: Node
# FIXME This is super gross because the user can pass ANY data type
typealias FuncSet Vector{DataType}

abstract Term <: Node
typealias TermSet{T<:Term} Vector{T}

abstract Const <: Term
abstract ConstRange
typealias ConstSet{T<:Const, U<:ConstRange} Union(Vector{T}, U)

typealias Binds Dict{String}{Const}
abstract State
immutable EmptyState <: State
end

# TODO This will need to change once variables can have types
immutable Var <: Term
    sym::String
end
typealias VarSet Vector{Var}

function evaluate(r::Var, b::Binds, s::State) evaluate(b[r.sym], b, s) end
function symbol(r::Var) r.sym end

function evaluate(r::Const, b::Binds, s::State) r.val end
function symbol(r::Const) string(r.val) end

function evaluate(r::Node) evaluate(r, Binds(), EmptyState()) end
function evaluate(r::Node, b::Binds) evaluate(r, b, EmptyState()) end
function evaluate(r::Node, s::State) evaluate(r, Binds(), s) end
function symbol(r::Node) typeof(r) |> string end
