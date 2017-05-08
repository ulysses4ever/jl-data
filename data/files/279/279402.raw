
module Logic

import Base

export
    Formula,
    Variable,
    Negation,
    Conjunction,
    Disjunction,
    truth


# TODO: Split experssions to atomic and compound and use string() accordingly.
# TODO: Support literal boolean values. True is a formula.

abstract Formula

type Variable <: Formula
    name::String
    value::Bool
end

type Negation <: Formula
    formula::Formula
end

type Conjunction <: Formula
    left::Formula
    right::Formula
end

type Disjunction <: Formula
    left::Formula
    right::Formula
end

type Implication <: Formula
    left::Formula
    right::Formula
end

type Equivalence <: Formula
    left::Formula
    right::Formula
end

typealias Mapping Dict{String, Bool}


string(f::Variable)    = f.name
string(f::Negation)    = "¬$(f.formula)"
string(f::Conjunction) = "$(parenthesize(f.left)) ∧ $(parenthesize(f.right))"
string(f::Disjunction) = "$(parenthesize(f.left)) ∨ $(parenthesize(f.right))"
string(f::Implication) = "$(parenthesize(f.left)) → $(parenthesize(f.right))"
string(f::Equivalence) = "$(parenthesize(f.left)) ↔ $(parenthesize(f.right))"



parenthesize{T <: Union(Variable, Negation)}(f::T) = string(f)
parenthesize(f::Formula) = "($(f))"


Base.show(io::IO, f::Formula) = print(io, string(f))


(~) (f1::Formula)              = Negation(f1)
(|) (f1::Formula, f2::Formula) = Disjunction(f1, f2)
(&) (f1::Formula, f2::Formula) = Conjunction(f1, f2)
(>>)(f1::Formula, f2::Formula) = Implication(f1, f2)
(==)(f1::Formula, f2::Formula) = Equivalence(f1, f2)


truth(f::Variable)    =   f.value
truth(f::Negation)    = ! truth(f.formula)
truth(f::Conjunction) =   truth(f.left) && truth(f.right)
truth(f::Disjunction) =   truth(f.left) || truth(f.right)
truth(f::Implication) = ! truth(f.left) || truth(f.right)
truth(f::Equivalence) =   truth(f.left) == truth(f.right)
truth(f::Formula)     =   error("default fallback")


values(f::Formula) = 

is_tautology(f:Formula) = all(values(f))

is_contradiction(f:Formula) = ! any(values(f))

is_contingent(f::Formula) = ! (is_tautology(f) || is_contingent(f))



function test()
    a = Variable("a", true)
    b = Variable("b", false)

    f1 = ((b & (b | a)) & (b | a)) >> a
    f2 = (~a | b) == (a >> b)
    f3 = (~a | b) | b
    f4 = (~a == b) & a

    @assert truth(f1) == true
    @assert truth(f2) == true

    println("a = $(a.value ? 'T' : 'F')")
    println("b = $(b.value ? 'T' : 'F')")
    println(truth(f1) ? "T" : "F", ": ", f1)
    println(truth(f2) ? "T" : "F", ": ", f2)
    println(truth(f3) ? "T" : "F", ": ", f3)
    println(truth(f4) ? "T" : "F", ": ", f4)
end

test()

end # module

