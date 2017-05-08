push!(LOAD_PATH, "../src")
using Base.Test
using units

# Tests of BaseUnit

# Factory constructors
@test 1m == Meter{Int, 1}(1)
@test 1.0m == Meter{Float64, 1}(1.0)
@test 1m^3 == Meter{Int, 3}(1)
@test 1m^-2.5 == Meter{Int, -2.5}(1)

# Existence of other units
@test 1s == Second{Int, 1}(1)
@test 1kg == Kilogram{Int, 1}(1)
@test 1rad == Radian{Int, 1}(1)

# In-unit arithmetic
@test 1m + 1m == Meter{Int, 1}(2)
@test 1m - 1m == Meter{Int, 1}(0)
# TODO: numeric type promotion
#@test 1m + (1//2)m == Meter{Rational{Int}, 1}(3//2)
@test_throws MethodError 1m^2 + 5m == Meter{Int, 1}(2)
@test_throws MethodError 1m + 2s == Meter{Int, 1}(2)
@test 1m * 5m == Meter{Int, 2}(5)
@test 1m * 5.0m == Meter{Float64, 2}(5.0)
@test 5m / 2.0m^3 == Meter{Float64, -2}(2.5)
@test reciprocal(4.0m) == 0.25m^-1
@test 2 * 1.0m == Meter{Float64, 1}(2.0)
@test 1.0m * 2 == Meter{Float64, 1}(2.0)

# Tests of Unit
@test Unit((0.5)m^5.2) == Unit{Tuple{Meter{Float64, 5.2}}, Float64}(0.5)
@test 1m * 4s == Unit{Tuple{Meter{Int, 1}, Second{Int, 1}}, Int}(4)
@test 1m * 4.0s == Unit{Tuple{Meter{Int, 1}, Second{Float64, 1}},
    Float64}(4.0)
@test (1m * 4.0s) * 2m == Unit{Tuple{Meter{Float64, 2}, Second{Float64,
    1}}, Float64}(8.0)
@test 1m * (4.0s * 2m) == Unit{Tuple{Second{Float64, 1}, Meter{Float64,
    2}}, Float64}(8.0)
@test 1m * 4.0s * 2s == Unit{Tuple{Meter{Int, 1}, Second{Float64, 2}},
    Float64}(8.0)
@test reciprocal(Unit{Tuple{Meter{Float64, 1}}, Float64}(4.0)) == Unit{
    Tuple{Meter{Float64, -1}}, Float64}(0.25)
@test 1.0m / 2.0s == Unit{Tuple{Meter{Float64, 1}, Second{Float64, -1}},
    Float64}(0.5)
@test Unit(1.0m) * Unit(0.5s^-1) == Unit{Tuple{Meter{
    Float64, 1}, Second{Float64, -1}}, Float64}(0.5)
@test 1.0m / 2.0s^-1 == Unit{Tuple{Meter{Float64, 1}, Second{Float64, 1}},
    Float64}(0.5)

# Interaction with dimensionless quantities
@test 1Dimensionless == Dimensionless{Int, 1}(1)
# TODO: Convert between unit^0 and Dimensionless, and any Dimensionless
# and pure numeric types
#@test 5m / 2.0m + 2.5 == 5.0
#@test 5m / 2.0m == ???
