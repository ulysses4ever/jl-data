# Math primitives.

export Num, Sum, Diff, Neg, Abs, MATH_FUNCS

# ---------
# Constants
# ---------

immutable Num <: Const
    val::Number
end

# ---------
# Functions
# ---------

immutable Sum <: Func
    args::ArgList{2}
end
Sum(args...) = Sum(args)
evaluate(t::Sum, b::Bindings, s::State) = evaluate(t.args[1], b, s) + evaluate(t.args[2], b, s)
arity(f::FuncType{Sum}) = 2

immutable Diff <: Func
    args::ArgList{2}
end
Diff(args...) = Diff(args)
evaluate(t::Diff, b::Bindings, s::State) = evaluate(t.args[1], b, s) - evaluate(t.args[2], b, s)
arity(f::FuncType{Diff}) = 2

immutable Neg <: Func
    args::ArgList{1}
end
Neg(arg) = Neg((arg,))
evaluate(t::Neg, b::Bindings, s::State) = -1 * evaluate(t.args[1], b, s)
arity(f::FuncType{Neg}) = 1

immutable Abs <: Func
    args::ArgList{1}
end
Abs(arg) = Abs((arg,))
evaluate(t::Abs, b::Bindings, s::State) = abs(evaluate(t.args[1], b, s))
arity(f::FuncType{Abs}) = 1

# ------------------
# Convenience groups
# ------------------

const MATH_FUNCS = functypes(Sum, Diff, Neg, Abs)
