using Criterion

function test_svd(k::Integer)
    for _ in k
        svd(zeros(300, 300))
    end 
end 


bench = Criterion.Benchmark("test_svd", 1, test_svd)
env = Criterion.measure_environment()
#times = Criterion.run_benchmakr(env, bench, false)
times, sample_analysis, outliers = Criterion.run_analyze_one(env, "test_svd", bench)

r = Report(1, "svd/svd1", times, sample_analysis, outliers) 
report(r)


#using Winston
#p = FramedPlot()
#setattr(p, "title", "Benchmark Times (sec)")
#setattr(p, "ylabel", "counts")
#setattr(p, "xlabel", "times (sec)")
#add(p, Histogram(hist(times, 100)...))
#add(p, LineX(sa.mean.point, "color", "red"))
#add(p, LineX(sa.mean.lbound, "type", "dot"))
#add(p, LineX(sa.mean.ubound, "type", "dot"))
#Winston.display(p)

