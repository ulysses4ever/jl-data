# sample_file.jl

# Compute some data
x = [1:10]
y = 2x

# Plot out some results
println("This is some output!")
println("Number of x values is ", length(x))

# Let's plot our results
using PGFPlots
p = Plots.Linear(x,y)
a = Axis(p)
save("sample_file_plot.pdf", a)
