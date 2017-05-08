using Units
using Base.Test


q1 = Quantity(1, Meter)
q2 = 1 * Meter
@test isequal(q1, q2)
@test 2 * q1
@test q1 * q2
@test q1 / q2
@test q1^2

q1 = 1 * Meter
q2 = 1 * Second
@test_throws UnitError q1 + q2
