println("Starting runtests.jl ...")
using ImagePlot
using Base.Test

# using TestImages
# img = plot(testimage("lighthouse"), 30*randn(2,10000).+[80;600])
# img = plot(img, [60 60 90; 580 620 600], radius = 6, fillcolor = "black")

img = plot(rand(Float32, 300,200), randn(2,10)+50)
@test size(img) == (300,200,3)

img = plot(rand(Float32, 300,200,3), randn(2,10)+50)
@test size(img) == (300,200,3)
println("runtests done.")
