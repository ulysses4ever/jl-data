# Tests for evolutionary operators.

using Base.Test
using GP

const fs = functypes(Sum, Diff)
const cs = consts(Num(3), Num(4))
const vs = vars()
const ts = terms(Num(3), Num(4))

const t1 = Sum(Num(1), Diff(Num(1), Num(2)))

srand(0)
t1_ptmut1 = mutpoint(t1, fs, ts, 0.5)
@test t1_ptmut1 == Sum(Num(1),Diff(Num(3),Num(4)))

srand(1)
t1_ptmut2 = mutpoint(t1_ptmut1, fs, ts, 0.5)
@test t1_ptmut2 == Sum(Num(4),Sum(Num(3),Num(4)))

srand(0)
t1_stmut1 = mutsubtree(t1, fs, cs, vs, 1.0)
@test t1_stmut1 == Sum(Num(1),Diff(Num(3),Num(4)))
