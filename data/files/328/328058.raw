if do_plots
    x = linspace(0,1,1000)
    function knotseq_test(k,t,name)
        figure()
        plot_bsplines(k, t, x)
        savefig("/tmp/Splines.jl-bsplines-test-$(name).pdf")
    end
    knotseq_test(3, Splines.Knotseqs.linear(0,1,10), "linear")
    knotseq_test(3, Splines.Knotseqs.arcsin(0,1,10), "arcsin")
    knotseq_test(3, Splines.Knotseqs.exponential(0,1,10), "exponential")
end
