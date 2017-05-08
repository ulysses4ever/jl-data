# Quadratic function

# A generic quadratic equation of the form:
# f = (x) -> ax^2 + bx + c
# f1 = (x) -> 2ax + b

include("derivative.jl")

function quadratic(f)
    f1 = derivative(f)

    c = f(0.0)
    b = f1(0.0)
    a = f(1.0) - b - c

    return (-b + sqrt(b^2 -4a*c + 0im)) / 2a, (-b - sqrt(b^2 -4a*c + 0im)) / 2a

end
