# Tests for evolutionary operators.

using GP

funcs = [Sum, Diff, Prod]
terms = [Num(3), Num(4)]

srand(0)
t1 = Sum(Num(1), Diff(Num(1), Num(2)))
t1_mut1 = mutpoint(t1, funcs, terms, 0.5)
t1_mut2 = mutpoint(t1_mut1, funcs, terms, 0.5)

@test t1_mut1 == Sum(Num(1),Diff(Num(3),Num(3)))
@test t1_mut2 == Sum(Num(3),Diff(Num(3),Num(3)))
