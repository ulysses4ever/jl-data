# Boolean circuits implementation

export Boolean, Nand, BOOL_FUNCS, BOOL_CONSTS

# ---------
# Constants
# ---------

immutable Boolean <: Const
    val::Bool
end

# ---------
# Functions
# ---------

immutable Nand <: Func
    args::ArgList{2}
end
Nand(args...) = Nand(args)
evaluate(t::Nand, b::Bindings, s::State) = ! (evaluate(t.args[1], b, s) && evaluate(t.args[2], b, s))
arity(f::FuncType{Nand}) = 2

# ------------------
# Convenience groups
# ------------------

const BOOL_FUNCS = functypes(Nand)
const BOOL_CONSTS = consts(Boolean(true), Boolean(false))
