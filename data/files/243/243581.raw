# Tests for tree initialization functions.

using Base.Test
using GP

fs = functypes(Sum, Diff)
cs = consts(Num(1), Num(2))
vs = vars(Var('x'), Var('y'))

srand(0)
tf1 = treefull(fs, cs, vs, 2)
@test tf1 == Sum(Sum(Var('y'),Var('x')),Sum(Var('y'),Num(2)))

srand(2)
tg1 = treegrow(fs, cs, vs, 2)
@test tg1 == Diff(Diff(Var('x'),Var('x')),Num(2))
