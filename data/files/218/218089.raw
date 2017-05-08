abstract Benchmarkable

immutable Benchmark <: Benchmarkable
    name :: String
    ntimes :: Integer
    run :: Function
end
Base.show(b::Benchmark) = let name = b.name
			  print("Benchmark $name")
			  end

immutable BenchmarkGroup <: Benchmarkable
    name :: String
    benchmarks :: Vector{Benchmark}
end
Base.show(b::BenchmarkGroup) = let name = b.name
			       print("Benchmark Group $name")
			       end
function bench(name::String, 
	       ntimes::Integer,
	       action::Function)
    Benchmark(name, ntimes, action)
end


function bgroup(name::String,
		benchmarks::Vector{Benchmarkable})
    BenchMarkGroup(name, benchmarks)
end

typealias Sample Vector{Float64}

immutable Payload
    sample   :: Sample 
    analysis :: SampleAnalysis
    outliers :: Outliers
end

immutable Result
    info :: String 
    payload :: Payload
end 
