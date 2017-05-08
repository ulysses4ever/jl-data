using Optim

function f(x::Vector)
    return (1.0 - x[1])^2 + 100.0 * (x[2] - x[1]^2)^2
end

tic()
res = optimize(f, [-1.2, 1.0], method = Optim.NelderMead(), show_trace = true)
@show res
toc()
