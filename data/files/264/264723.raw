function diff_test{T,C}(f::Splines.Spline{T,C}, x, name)
    fp = Splines.∂f∂x(f)
    Bp = Splines.bsplvb(fp.k,fp.t,x)
    fpp = Splines.∂f∂x(fp)
    dx = diff(x[1:2])[1]
    fpn = gradient(Splines.bsplvb(f.k,f.t,x)*f.α, dx)
    dfppn = dx*abs(Bp*fp.α-fpn) # Difference between analytic and numeric derivative
    Δ = vecnorm(dfppn)
    println("Analytic–numeric Δ: $(Δ)")

    if do_plots
        figure(figsize=(8,18))
        ax1=subplot(611)
        margins(0,0.1)
        plot_bsplines(fp.k,fp.t,x)
        title(latexstring("\$B_{i,$(f.k-1)}\$"))
        setp(ax1[:get_xticklabels](),visible=false)

        ax2=subplot(612,sharex=ax1)
        margins(0,0.1)
        plot_bsplines(f.k,f.t,x)
        title(latexstring("\$B_{i,$(f.k)}\$"))
        setp(ax2[:get_xticklabels](),visible=false)

        ax3=subplot(312,sharex=ax2)
        margins(0,0.1)
        plot_spline(f,x,latexstring("\$f(x)\$"))
        plot(x, fpn, label=latexstring("\$\\mathrm{d}f/\\mathrm{d}x\$, numerical"))
        plot_spline(fp,x,latexstring("\$\\mathrm{d}f/\\mathrm{d}x\$, analytical"), "--")
        plot_spline(fpp,x,latexstring("\$\\mathrm{d}^2f/\\mathrm{d}x^2\$, analytical"))
        ylim((-4,4))
        legend(loc=2,ncol=2,framealpha=0.5)
        setp(ax3[:get_xticklabels](),visible=false)

        subplot(615,sharex=ax3)
        semilogy(x,dfppn)
        margins(0.1,1)

        subplot(616)
        margins(0.1,0.1)
        plot(f.α,".-")
        plot(fp.α,".-")
        tight_layout()
        savefig("/tmp/Splines.jl-diff-test-$(name)-$(f.k).pdf")
    end
end

diff_test(Splines.Spline(3, [0.0:3], [1.0]), linspace(-1,4,1000), "simple")
diff_test(Splines.Spline(4, [0.0:5], [1.0,1]), linspace(-1,6,1000), "simple")
diff_test(Splines.Spline(4,
                         [0.0,0,0,0,2,4,6,8,8,8,10,12,12,12,12],
                         [1.0,-1,1,-1,1,-1,1,-1,1,-1,1]),
          linspace(0,12,1000), "discont")
