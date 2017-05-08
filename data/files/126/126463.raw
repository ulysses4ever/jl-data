include("/Users/feifeihuang/Astro585_teacher/Lab5/HW5_Q2_ecc_anom.jl");
include("/Users/feifeihuang/Astro585_teacher/Lab5/HW5_Q2_lookup_table.jl");

using PyPlot;

function plot_with_table(a::Real,b::Real,n::Integer = 1000)
    x = linspace(a,b,n);
    table = make_table_linear(y->ecc_anom(y,0.25,tol = 1.e-12),y->decc_anom_dM(y,0.25,tol = 1e-12),a,b,n);
    scatter(x,lookup!(table,x,zeros(n)),color = "red");
    title("Plot with table");
    xlabel("M");
    ylabel("E");
    savefig("/Users/feifeihuang/lab5/problem_2f_table.png");
    end

function plot_directly(a::Real,b::Real,n::Integer = 1000)
    x = linspace(a,b,n);
    plot(x,ecc_anom(x,0.25,tol = 1.e-12));
    savefig("/Users/feifeihuang/lab5/problem_2f_directly.png");
    end


plot_with_table(-2*pi,4*pi,128);
#plot_directly(-2*pi,4*pi,128);

#println("time for plotting with table: ", @elapsed(plot_with_table(-2*pi,4*pi,128)), "\n")
#println("time for plotting directly: ", @elapsed(plot_directly(-2*pi,4*pi,128)));
