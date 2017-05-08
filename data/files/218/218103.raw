module NumericIntegration

export trapezoidal

function trapezoidal(f::Function, a::Real, b::Real, k::Real, er::Real)
    n = trapezoidal_error(a, b, k, er)
    deltax = (b - a) / n
    return (.5 * deltax * trapezoidal_algorithm(f, a, b, n, deltax)), n
end

function trapezoidal_algorithm(f::Function, a::Real, b::Real, n::Real, deltax::Real)
    area = 0.0
    area += f(a)
    area += trapezoidal_loop(f, a, n, deltax)
    area += f(b)
  return area
end

function trapezoidal_loop(f::Function, a::Real, n::Real, deltax::Real)
    @parallel (+) for i = 1:(n - 1)
        2 * f(a + i * deltax)
    end
end

function trapezoidal_error(a::Real, b::Real, k::Real, er::Real)
    return convert(Integer, ceil(sqrt((k * (b - a)^3) / (12 * er))))
end

end # module
