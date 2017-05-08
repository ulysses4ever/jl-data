module FormulationLattice

import Base: &, |
export Literal, And, Or, isliteral, iscnf, isdnf, basicstep

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

isliteral(c::Clause) = isa(c, Literal)

Base.print(io::IO, l::Literal) = print(io, l.name)

type And <: Clause
    clauses::Vector{Clause}
end
And(clauses::Clause...) = And(collect(clauses))
(&)(clauses::Clause...) = And(clauses...)
const ⋀ = &

type Or <: Clause
    clauses::Vector{Clause}
end
Or( clauses::Clause...) = Or(collect(clauses))
(|)(clauses::Clause...) = Or(clauses...)
const ⋁ = |

for (T,connector) in [(:And," ⋀ "), (:Or," ⋁ ")]; @eval begin
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

# Not sure if this logic holds exactly as I want:
# will probably want to simplify expressions like
# (A ⋁ (B ⋁ C)) ⋀ D
# to
# (A ⋁ B ⋁ C) ⋀ D
# Probably add "sanitizers" to inner constructors to clauses above?
iscnf(c::Clause) = false
iscnf(c::And) = all(cl -> (isdnf(cl) | isliteral(cl)), c.clauses)

isdnf(c::Clause) = false
isdnf(c::Or) = all(cl -> (iscnf(cl) | isliteral(cl)), c.clauses)

function cnf(c::Clause)
    # Compute disjunctive normal form of clause c
    cl = c
    while !isdnf(cl)
        # compute basic step?
    end
    cl
end

function basicstep(c::And, idx::Int)
    n = length(c.clauses)
    @assert 1 ≤ idx ≤ n
    cl = c.clauses[idx]
    remaining = c.clauses[setdiff(1:n, idx)]
    @assert isa(cl, Or)
    tip  = cl.clauses[1]
    tail = cl.clauses[2:end]
    Or(vcat([(tip & x) for x in remaining], [(tail & x) for x in remaining]))
end

end
