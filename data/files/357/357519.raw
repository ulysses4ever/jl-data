# correctness
using Photometry

r = 5.
im = ones(Float32, 20, 20)
aper = CircAperture(10, 10, r)
println("Flux = ",aperflux(aper, im))
println("Area = ", pi*r*r)

# benchmarks
using TimeIt

@timeit aperflux(aper, im)
@time aperflux(aper,im)
