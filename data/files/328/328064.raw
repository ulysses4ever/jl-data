using Splines
using Base.Test

do_plots = haskey(ENV, "do_plots")

if do_plots
    using PyPlot

    function plot_bsplines(k,t,x)
        B = Splines.bsplvb(k,t,x)
        plot(x,B)
    end

    function plot_spline{T,C}(f::Splines.Spline{T,C},x,label,style="-")
        B = Splines.bsplvb(f.k,f.t,x)
        y = B*f.α
        plot(x,y,style,label=label)
    end
end

include("bsplines_test.jl")
include("diff_test.jl")
