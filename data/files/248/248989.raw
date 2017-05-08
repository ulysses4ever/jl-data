module FormulationLattice

import Base: &, |
export Literal, @Literal, @Literals, And, ∧, Or, ∨,
       isliteral, iscnf, isdnf, basicstep, dnf

abstract Clause
Base.show(io::IO, x::Clause) = print(io, x)

# TODO: add negation
immutable Literal <: Clause
    name::UTF8String
end

default_names = ["A","B","C","D","E","F","G","H","I","J","K"]
let counter = 0
    Literal() = (counter += 1; Literal(default_names[counter]))
end

macro Literal(name)
    @assert isa(name, Symbol)
    :($(esc(name)) = Literal($(string(name))))
end

macro Literals(args...)
    names = if isa(args,Symbol)
        [args]
    elseif isa(args,Expr)
        @assert args.head == :tuple
        args.args
    else
        if isa(args,Tuple{Expr})
            args[1].args
        else
            [args...]
        end
    end

    @assert all(x -> (isa(x,Symbol)), names)
    code = Expr(:block)
    lastline = Expr(:tuple)
    for name in names
        push!(code.args, :($(esc(name)) = Literal($(string(name)))))
        push!(lastline.args, :($(esc(name))))
    end
    :($code; $lastline)
end

Base.print(io::IO, l::Literal) = print(io, l.name)

# percolate
percolate{T<:Clause}(::Type{T}, cl) = Clause[cl]
percolate(::Type{Literal}, l::Literal) = Clause[l]
function percolate{T<:Clause}(::Type{T}, cl::T)
    x = map(x -> percolate(T, x), cl.clauses)
    vcat(x...)
end

immutable And <: Clause
    clauses::Vector{Clause}
end

(&)(clauses::Clause...) = And(clauses...)
const ∧ = &

immutable Or <: Clause
    clauses::Vector{Clause}
end
Or( clauses::Clause...) = Or(collect(clauses))
(|)(clauses::Clause...) = Or(clauses...)
const ∨ = |

for (T,connector) in [(:And," ∧ "), (:Or," ∨ ")]; @eval begin
    # helper that percolates like clauses up to toplevel, e.g.
    # A ∧ (B ∧ C) to A ∧ B ∧ C
    function $T(clauses::Clause...)
        length(clauses) > 1 || error("Unary $($T) not allowed")
        terms = Clause[]
        for cl in clauses
            append!(terms, percolate($T, cl))
        end
        $T(terms)
    end

    function Base.print(io::IO, cl::$T)
        numclause = length(cl.clauses)
        if numclause == 0
            print(io,)
        elseif numclause == 1
            print(io,cl.clauses[1])
        else
            inner = join(map(x->sprint(print,x), cl.clauses), $connector)
            print(io, string("(", inner, ")"))
        end
    end
end; end

isliteral(c::Clause) = isa(c, Literal)
isand(c::Clause)     = isa(c,And)
isor(c::Clause)      = isa(c,Or)

Base.copy(x::Literal)      = Literal(copy(x.name))
Base.copy{C<:Clause}(x::C) = C(copy(x.clauses))

# Not sure if this logic holds exactly as I want:
# will probably want to simplify expressions like
# (A ⋁ (B ⋁ C)) ⋀ D
# to
# (A ⋁ B ⋁ C) ⋀ D
# Probably add "sanitizers" to inner constructors to clauses above?
iscnf(c::Literal) = true
iscnf(c::Or)      = all(isliteral, c.clauses)
iscnf(c::And)     = all(c.clauses) do cl
    isliteral(cl) | (isor(cl) && all(isliteral, cl.clauses))
end

isdnf(c::Literal) = true
isdnf(c::Or)      = all(c.clauses) do cl
    isliteral(cl) | (isand(cl) && all(isliteral, cl.clauses))
end
isdnf(c::And)     = all(isliteral, c.clauses)

include("formulations.jl")

function dnf(c::Clause, formtrack=FormulaState[])
    # Compute disjunctive normal form of clause c
    cl = c
    push!(formtrack, FormulaState(cl))
    while !isdnf(cl)
        cl = basicstep(cl)
        push!(formtrack, FormulaState(cl))
    end
    cl
end

function basicstep(c::Or)
    isdnf(c) && return c
    n = length(c.clauses)
    idx = findfirst(x -> !isdnf(x), c.clauses)
    newterm = basicstep(c.clauses[idx])
    before = c.clauses[1:(idx-1)]
    after  = c.clauses[(idx+1):n]
    ret = Or(before..., newterm, after...)
    ret
end

function basicstep(c::And)
    idx = findfirst(x -> isa(x,Or), c.clauses)
    ret = _basicstep(c, idx)
    ret
end

function _basicstep(c::And, idx::Int)
    n = length(c.clauses)
    @assert 1 ≤ idx ≤ n
    cl = c.clauses[idx]
    remaining = c.clauses[setdiff(1:n, idx)]
    @assert isa(cl, Or)
    tip  = cl.clauses[1]
    tail = cl.clauses[2:end]
    before = c.clauses[1:(idx-1)]
    after  = c.clauses[(idx+1):n]
    if length(tail) == 1
        And(before..., tip, after...) ∨ And(before..., tail[1], after...)
    else
        And(before..., tip, after...) ∨ And(before..., Or(tail...), after...)
    end
end

end
