# Math primitives.

export Num, Sum, Diff, Neg, Abs

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
evaluate(t::Sum) = evaluate(t.args[1]) + evaluate(t.args[2])
arity(f::FuncType{Sum}) = 2

immutable Diff <: Func
    args::ArgList{2}
end
Diff(args...) = Diff(args)
evaluate(t::Diff) = evaluate(t.args[1]) - evaluate(t.args[2])
arity(f::FuncType{Diff}) = 2

immutable Neg <: Func
    args::ArgList{1}
end
Neg(arg) = Neg((arg,))
evaluate(t::Neg) = -1 * evaluate(t.args[1])
arity(f::FuncType{Neg}) = 1

immutable Abs <: Func
    args::ArgList{1}
end
Abs(arg) = Abs((arg,))
evaluate(t::Abs) = abs(evaluate(t.args[1]))
arity(f::FuncType{Abs}) = 1
