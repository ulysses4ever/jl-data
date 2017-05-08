push!(LOAD_PATH, "/Users/skohn/Programming/projects/Units.jl/src")
using Base.Test
using units

# Tests of BaseUnit

# Factory constructors
@test m == Meter{1}()
@test m^3 == Meter{3}()
@test m^-2.5 == Meter{-2.5}()

# Existence of other units
@test s == Second{1}()
@test kg == Kilogram{1}()
@test rad == Radian{1}()

# In-unit arithmetic
@test m * m == Meter{2}()
@test m / m^3 == Meter{-2}()
@test reciprocal(m) == m^-1

# Tests of Unit

# Constructor
@test Unit(m^5.2) == Unit{Tuple{Meter{5.2}}}()
@test Unit(m^2) == Unit{Tuple{Meter{2}}}()

# In-unit arithmetic
@test m * s == Unit{Tuple{Meter{1}, Second{1}}}()
@test m * s == s * m
@test (m * s) * m == Unit{Tuple{Meter{2}, Second{1}}}()
@test m * (s * m) == Unit{Tuple{Meter{2}, Second{1}}}()
@test (m * s) * m == m * (s * m)
@test m * s * s == Unit{Tuple{Meter{1}, Second{2}}}()
@test reciprocal(m*s) == Unit{ Tuple{Meter{-1}, Second{-1}}}()
@test m / s == Unit{Tuple{Meter{1}, Second{-1}}}()
@test Unit(m) * Unit(s^-1) == m/s
@test m/(kg * s^-1) == Unit{Tuple{Kilogram{-1}, Meter{1}, Second{1}}}()
