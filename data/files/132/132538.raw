using MMA
using Base.Test

# write your own tests here
@test variance([1, 1, 1]) == 0
@test variance([1, 2, 4, 5]) == 2.5
@test_approx_eq(std_dev([1, 1, 1]), 0)
@test_approx_eq(std_dev([1, 3]), 1)
@test_approx_eq(dist([3, 0], [0, 4]), 5)
@test_approx_eq(rms([1, 1, 3, 5]), 3)
@test_approx_eq(angle([1, 0], [0, 1]), pi/2)
