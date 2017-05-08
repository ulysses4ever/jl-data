info("Starting process with $(nprocs()) processors")
@everywhere using SimpleRandom
@everywhere include("para-cogen.jl")
@everywhere include("para-clique.jl")

n = 2^15    # number of vertices
chunk = 200	     # work chunk size
reps  = 500      # number rounds
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

file_name = "clique-sizes-$n"

using PyPlot
histplot(data,30)
title("$total random cographs on $n vertices")
xlabel("Clique Sizes")
ylabel("Count")
savefig(file_name*".pdf")

F = open("$file_name.txt","w")
for x in data
  println(F,x)
end
close(F)
info("Wrote $file_name files")
