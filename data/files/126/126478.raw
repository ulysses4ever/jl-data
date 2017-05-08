include("/Users/feifeihuang/Astro585_teacher/Lab5/HW5_Q2_lookup_table.jl");
using PyPlot;

function plot_with_table(a::Real,b::Real,n::Integer = 1000)
    x = linspace(a,b,n);
    table = make_table_linear(y->f1(y),a,b,n);
    plot(x,lookup!(table,x,zeros(n)));
    savefig("/Users/feifeihuang/lab5/problem_2c_table.png");
    end

function plot_directly(a::Real,b::Real,n::Integer = 1000)
    x = linspace(a,b,n);
    for i = 1:n
        plot(x[i],f1(x[i]));
        end
    savefig("/Users/feifeihuang/lab5/problem_2c_directly.png");
    end


function f1(x::Float64)
    I, E = quadgk(sin,0,x);
    return I;
    end

plot_with_table(0.,8.,100);
plot_directly(0.,8.,100);
println("time for plotting with table: ", @elapsed(plot_with_table(0.,8.,1000)), "\n", "time for plotting directly: ", @elapsed(plot_directly(0.,8.,1000)));
