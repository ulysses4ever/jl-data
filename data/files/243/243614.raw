# Math primitives.

export Num, Sum, Prod, Diff, Quo, Neg, Max, Min

# ---------
# Constants
# ---------

immutable Num <: Const
    val::Number
end

# ---------
# Functions
# ---------

immutable Sum{N} <: Func
    args::NTuple{N,Node}
end
Sum(args...) = Sum(args)

immutable Prod{N} <: Func
    args::NTuple{N,Node}
end
Prod(args...) = Prod(args)

immutable Diff <: Func
    args::NTuple{2,Node}
end
Diff(args...) = Diff(args)

immutable Quo <: Func
    args::NTuple{2,Node}
end
Quo(args...) = Quo(args)

immutable Neg <: Func
    args::NTuple{1,Node}
end
# TODO Find a more elegant way of handling single-attribute constructors
Neg(arg::Node) = Neg((arg,))

immutable Max{N} <: Func
    args::NTuple{N,Node}
end
Max(args...) = Max(args)

immutable Min{N} <: Func
    args::NTuple{N,Node}
end
Min(args...) = Min(args)

# -------
# Methods
# -------

function evaluate(r::Sum, b::Binds, s::State)
    sum([evaluate(c, b, s) for c=r.args])
end
function evaluate(r::Prod, b::Binds, s::State)
    prod([evaluate(c, b, s) for c=r.args])
end
function evaluate(r::Diff, b::Binds, s::State)
    evaluate(r.args[1], b, s) - evaluate(r.args[2], b, s)
end
function evaluate(r::Quo, b::Binds, s::State)
    evaluate(r.args[1], b, s) / evaluate(r.args[2], b, s)
end
function evaluate(r::Neg, b::Binds, s::State)
    evaluate(r.args[1], b, s) * -1
end
function evaluate(r::Max, b::Binds, s::State)
    maximum([evaluate(c, b, s) for c=r.args])
end
function evaluate(r::Min, b::Binds, s::State)
    minimum([evaluate(c, b, s) for c=r.args])
end

function symbol(r::Sum) "+" end
function symbol(r::Prod) "*" end
function symbol(r::Diff) "-" end
function symbol(r::Quo) "/" end
function symbol(r::Neg) "-" end
function symbol(r::Max) "MAX" end
function symbol(r::Min) "MIN" end
