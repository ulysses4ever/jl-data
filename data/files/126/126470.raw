include("/Users/feifeihuang/Astro585_teacher/Lab5/HW5_Q2_ecc_anom.jl");
include("/Users/feifeihuang/Astro585_teacher/Lab5/HW5_Q2_lookup_table.jl");

using PyPlot;

function plot_with_table(a::Real,b::Real,n::Integer)
    x = linspace(a,b,n);
    table = make_table_linear(y->ecc_anom(y,0.25,tol = 1.e-12),a,b,n);
    scatter(x,lookup!(table,x,zeros(n)),color = "red");
    title("Plot with table");
    xlabel("M");
    ylabel("E");
    savefig("/Users/feifeihuang/lab5/problem_2d_table.png");
    end

function plot_directly(a::Real,b::Real,n::Integer)
    x = linspace(a,b,n);
    scatter(x,ecc_anom(x,0.25,tol = 1.e-12),color = "black");
    title("Plot directly");
    #plot(mean_anom(x),x);
    savefig("/Users/feifeihuang/lab5/problem_2d_directly.png");
    end

plot_directly(-2*pi,4*pi,128);
#plot_with_table(-2*pi,4*pi,128);

#println("time for plotting direclty: ", @elapsed(plot_directly(-2*pi,4*pi,128)), "\n")
#println("time for plotting with table: ", @elapsed(plot_with_table(-2*pi,4*pi,128)));
