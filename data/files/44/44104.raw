info("Starting process with $(nprocs()) processors")
@everywhere using SimpleRandom
@everywhere include("para-cogen.jl")
@everywhere include("para-clique.jl")

n = 100    	# number of vertices
chunk = 10	# work chunk size
reps  = 100    # number rounds 
total = chunk*reps

info("Generating $(total) random cographs on $n vertices.")

data = para_clique_sizes(n, chunk, reps)
info("Finished")

println("Generated $total random cographs on $n vertices.")

println("Max clique size = $(maximum(data))")


using PyPlot
histplot(data,20)
xlabel("$total random cographs on $n vertices")
title("Clique sizes")
ylabel("Count")
savefig("clique-sizes-$n.pdf")
