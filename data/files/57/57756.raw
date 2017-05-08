type Foo
    x::Int
end

function check_defined_err(x::Symbol)
    if !isdefined(x)
        error("Module $x not defined. run `using $x` to fix the problem")
    end
end

function check_defined_eval(x::Symbol)

end

function plot_err(x::Foo)
    check_defined_err(:PyPlot)
    d = 1:x.x
    PyPlot.plot(d, d.^2)
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
plot_eval(a)
