# Syntax tree data structure support

export Tree, Func, Term, Const, State, ArgList, FuncType,
       Bindings, EmptyState, Var
export evaluate, arity, functypes, terms, consts, vars

abstract Tree
abstract Func <: Tree
abstract Term <: Tree
abstract Const <: Term
abstract State

typealias ArgList{N} NTuple{N,Tree}
typealias FuncType{T<:Func} Type{T}
typealias Bindings Dict{String}{Tree}
typealias FuncTypes{N} NTuple{N,DataType}
typealias Terms{N} NTuple{N,Term}
typealias Consts{N} NTuple{N,Const}

immutable EmptyState <: State
end

immutable Var <: Const
    sym::Char
end
typealias Vars{N} NTuple{N,Var}

evaluate(t::Tree) = evaluate(t, Bindings(), EmptyState())
evaluate(t::Tree, b::Bindings) = evaluate(t, b, EmptyState())
evaluate(t::Tree, s::State) = evaluate(t, Bindings(), s)
evaluate(t::Const, b::Bindings, s::State) = t.val
evaluate(t::Var, b::Bindings, s::State) = evaluate(b[t.sym], b, s)

arity(t::Func) = length(t.args)
arity(t::Term) = 0

function functypes(fs::DataType...)
    ntuple(length(fs)) do i
        f = fs[i]
        @assert f <: Func
        f
    end
end

# TODO Build all of these using a macro or generalize into a single function?
function terms(ts...)
    ntuple(length(ts)) do i
        t = ts[i]
        @assert typeof(t) <: Term
        t
    end
end

function consts(cs...)
    ntuple(length(cs)) do i
        c = cs[i]
        @assert typeof(c) <: Const
        c
    end
end

function vars(vs...)
    ntuple(length(vs)) do i
        v = vs[i]
        @assert typeof(v) <: Var
        v
    end
end
