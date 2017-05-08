#!/usr/bin/env julia

# The fundamental problem of this design lies in the
# distinction between statements and questions (or problems).

# On the one hand, there seems to be a fundamental distinction
# between a statement of fact and a question about those
# facts. On the other hand, all questions are statements,
# in a sense.

# The compromise is to make questions/problems be
# functions of statements, returning statements. However,
# what if you want to ask a question about a question?

module typedefs

abstract Statement

abstract Problem

abstract Expression <: Statement
abstract Operator <: Expression
abstract Variant <: Expression
abstract Invariant <: Expression
abstract Value <: Invariant

abstract Relation <: Statement
type Equality <: Relation
    end
type Inequality <: Relation
    end
type LessThan <: Relation
    end
type GreaterThan <: Relation
    end
type DummyRelation <: Relation
    string::String
end

type System <: Statement
    relations::Array{Relation}
end

abstract Model <: Statement

type Definition <: Model
    relations::Array{Relation}

    Definition(system::System) =  new(system.relations)
    Definition(relations::Array{Relation}) = new(relations)
    Definition(input::String) = new([DummyRelation(input)])
end

end

defn = Definition("Hello there")
println("$(defn.relations[1].string)")
   
    
