import Criterion

function test_svd(k::Integer)
    for _ in k
        svd(zeros(100,100))
    end 
end 

bench = Criterion.Benchmark("test_svd", 1, test_svd)
env = Criterion.measure_environment()
#times = Criterion.run_benchmakr(env, bench, false)
times, sa, out = Criterion.run_analyze_one(env, "test_svd", bench)
