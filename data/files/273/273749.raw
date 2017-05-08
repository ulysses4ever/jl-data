println("Starting runtests.jl ...")
using ImagePlot
using Base.Test

# using TestImages
# img = plot(testimage("lighthouse"), 30*randn(2,10000).+[80;600])
# img = plot(img, [60 60 90; 580 620 600], radius = 6, fillcolor = "black")

s = (300,200,3)
a = rand(Float32, 300,200)
a3 = rand(Float32, s...)
p = randn(2,10)+50

img = plot(a, p)
@test size(img) == s

img = plot(a3, p)
@test size(img) == s

img = plot(a, p, 1:10)
@test size(img) == s
  
img = plot(a, p, [1,2,3,1,2,3,1,2,3,4])
@test size(img) == s
  
println("runtests done.")

