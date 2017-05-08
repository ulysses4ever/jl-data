using Base.Test
using AperturePhotometry

data = ones(10, 10)

r = 3.0
@test_approx_eq sum_circle(data, 5.0, 5.0, r) pi*r^2

println("tests passed")
