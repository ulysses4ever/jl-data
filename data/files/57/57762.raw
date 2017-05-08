type Foo
    x::Int
end

function plot_err(x::Foo)
    check_defined_err(:PyPlot)
    d = 1:x.x
    plot(d, d.^2)
end

function plot_eval(x::Foo)
    if !isdefined(:PyPlot)
        eval(Expr(:using, :PyPlot))
    end
    d = 1:x.x
    PyPlot.plot(d, d.^2)
end

a = Foo(10)
try
    plot_err(a)
catch err
    println(err)
end

using PyPlot

plot_eval(a)
