using Criterion

function test1_svd(k::Integer)
    for _ in k
        svd(zeros(20, 20))
    end 
end 

function test2_svd(k::Integer)
    for _ in k
        svd(ones(20, 20))
    end 
end 

function test3_svd(k::Integer)
    for _ in k
        svd(ones(10, 10))
    end 
end 


env = Criterion.measure_environment()

bench1 = Criterion.Benchmark("test1_svd", 1, test1_svd)
times, sample_analysis, outliers = Criterion.run_analyze_one(env, "test1_svd", bench1)
r1 = Criterion.Report(1, "test1/svd", times, sample_analysis, outliers) 

bench2 = Criterion.Benchmark("test2_svd", 2, test2_svd)
times, sample_analysis, outliers = Criterion.run_analyze_one(env, "test2_svd", bench2)
r2 = Criterion.Report(2, "test2/svd", times, sample_analysis, outliers) 

bench3 = Criterion.Benchmark("test3_svd", 2, test3_svd)
times, sample_analysis, outliers = Criterion.run_analyze_one(env, "test3_svd", bench3)
r3 = Criterion.Report(3, "test3/svd", times, sample_analysis, outliers) 


Criterion.report([r1, r2, r3])


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

