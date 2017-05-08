require("matrix_maker.jl")

model      = make_matrix_2
n          = 1000
total_reps = 10000
chunk      = 50
reps       = int(total_reps/chunk)

info("Creating " * string(total_reps) *
	 " random graphs on "* string(n)* " vertices")

h = degree_tally(model, n, reps, chunk)

# h /= sum(h)
# plot(0:n, h)
# xlabel("Out-degree")
# ylabel("Probability")
# title(string(total_reps) * " random graphs on " * string(n) * " vertices")
# grid()
# savefig("out-deg-distro.pdf")

for k=0:n
    println(k,",\t", h[k+1])
end

