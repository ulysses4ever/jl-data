require("matrix_maker.jl")

model      = make_matrix_2
n          = 200
total_reps = 100000
chunk      = 100
reps       = int(total_reps/chunk)

info("Creating " * string(total_reps) *
	 " random graphs on "* string(n)* " vertices")

tic();
h = degree_tally(model, n, reps, chunk)
toc();

# h /= sum(h)
# plot(0:n, h)
# xlabel("Out-degree")
# ylabel("Probability")
# title(string(total_reps) * " random graphs on " * string(n) * " vertices")
# grid()
# savefig("out-deg-distro.pdf")

for val in h
	println(val)
end

