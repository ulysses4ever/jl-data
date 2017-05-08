include("/Users/feifeihuang/Astro585_teacher/Lab5/HW5_Q2_ecc_anom.jl");
include("/Users/feifeihuang/Astro585_teacher/Lab5/HW5_Q2_lookup_table.jl");

using PyPlot;

#function mean_anom(ecc_anom::Float64)        # calculate mean anomaly from ecc_anomaly
#    return ecc_anom - 0.25*sin(ecc_anom);
#    end

function plot_with_table(a::Real,b::Real,n::Integer = 1000)
    x = linspace(a,b,n);
    table = make_table_linear(y->ecc_anom(y,0.25,tol = 1.e-12),a,b,n);
    for i = 1:n
        plot(x[i],lookup(table,x[i]));          # plot eccen_anomaly as a funtion of mean anomaly
        end
    savefig("/Users/feifeihuang/lab5/problem_2d_table.png");
    end

function plot_directly(a::Real,b::Real,n::Integer = 1000)
    x = linspace(a,b,n);
    plot(x,ecc_anom(x,0.25,tol = 1.e-12));
    savefig("/Users/feifeihuang/lab5/problem_2d_directly.png");
    end


plot_with_table(-2*pi,4*pi,1000);
plot_directly(-2*pi,4*pi,1000);
println("time for plotting with table: ", @elapsed(plot_with_table(-2*pi,4*pi,1000)), "\n", "time for plotting directly: ", @elapsed(plot_directly(-2*pi,4*pi,1000)));
