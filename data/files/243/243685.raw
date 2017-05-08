# Tests for math primitives.

using GP

n1 = Num(-1)
n2 = Num(0)
n3 = Num(1.5)

@test evaluate(n1, Binds()) == -1
@test evaluate(n2, Binds()) == 0
@test evaluate(n3, Binds()) == 1.5

@test evaluate(Sum(n1, n2)) == -1
@test evaluate(Sum(n1, n3)) == 0.5
@test evaluate(Sum(n2, n3)) == 1.5

@test evaluate(Prod(n1, n2)) == 0
@test evaluate(Prod(n1, n3)) == -1.5
@test evaluate(Prod(n2, n3)) == 0

@test evaluate(Diff(n1, n2)) == -1
@test evaluate(Diff(n1, n3)) == -2.5
@test evaluate(Diff(n2, n3)) == -1.5

@test evaluate(Quo(n1, n2)) == -Inf
@test evaluate(Quo(n1, n3)) == -1/1.5
@test evaluate(Quo(n2, n3)) == 0

@test evaluate(Neg(n1)) == 1
@test evaluate(Neg(n2)) == 0
@test evaluate(Neg(n3)) == -1.5

@test evaluate(Max(n1, n2)) == 0
@test evaluate(Max(n1, n3)) == 1.5
@test evaluate(Max(n2, n3)) == 1.5

@test evaluate(Min(n1, n2)) == -1
@test evaluate(Min(n1, n3)) == -1
@test evaluate(Min(n2, n3)) == 0
