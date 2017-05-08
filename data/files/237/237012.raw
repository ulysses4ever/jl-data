#!/usr/bin/env julia

abstract Statement

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

defn = Definition("Hello there")
println("$(defn.relations[1].string)")
   
    
