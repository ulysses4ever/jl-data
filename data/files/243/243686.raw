# Tests for math primitives.

using GP

n1 = Num(-1)
n2 = Num(0)
n3 = Num(1.5)

@test evaluate(n1) == -1
@test evaluate(n2) == 0
@test evaluate(n3) == 1.5

@test evaluate(Sum(n1, n2)) == -1
@test evaluate(Sum(n1, n3)) == 0.5
@test evaluate(Sum(n2, n3)) == 1.5

@test evaluate(Diff(n1, n2)) == -1
@test evaluate(Diff(n1, n3)) == -2.5
@test evaluate(Diff(n2, n3)) == -1.5

@test evaluate(Neg(n1)) == 1
@test evaluate(Neg(n2)) == 0
@test evaluate(Neg(n3)) == -1.5

@test evaluate(Abs(n1)) == 1
@test evaluate(Abs(n2)) == 0
@test evaluate(Abs(n3)) == 1.5
