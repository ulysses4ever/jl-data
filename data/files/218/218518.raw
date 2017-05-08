# quadratic.jl
include("derivative.jl")

f = (x) -> 3x^2 + 4x + 1

function quadratic(f)
    f1 = derivative(f) # compute derivative of f
    c = f(0.0) # get y intercept
    b = f1(0.0) # get y intercept of derivative
    a = f(1.0) - b - c

    # Quadratic formula
    # multiple values being returned separated by a comma
    return (-b + sqrt(b^2 -4a*c)) / 2a, (-b - sqrt(b^2 -4a*c + 0im)) / 2a
end
