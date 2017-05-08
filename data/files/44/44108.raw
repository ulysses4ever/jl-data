info("Starting process with $(nprocs()) processors")
@everywhere using SimpleRandom
@everywhere include("para-cogen.jl")
@everywhere include("para-clique.jl")

n = 100_000    # number of vertices
chunk = 1000	# work chunk size
reps  = 1000    # number rounds
total = chunk*reps

info("Generating $(total) random cographs on $n vertices.")
tic()
data = para_clique_sizes(n, chunk, reps)
info("Finished")
toc()

println("Generated $total random cographs on $n vertices.")

println("Max clique size = $(maximum(data))")
println("Min clique size = $(minimum(data))")
println("Avg clique size = $(mean(data))")

file_name = "clique-sizes-$n.pdf"

using PyPlot
histplot(data,20)
title("$total random cographs on $n vertices")
xlabel("Clique Sizes")
ylabel("Count")
savefig(file_name)
info("Wrote $file_name")
