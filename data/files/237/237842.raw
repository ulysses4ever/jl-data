
# tests for the orientation code

# packages
using PyPlot
using Debug

# local
using Kernel

include("../src/randvonMisesFisher.jl")

#n = 200
n = 1
v1 = randvonMisesFisher(3,n,.1,[1 1 1])
v2 = randvonMisesFisher(3,n,.1,[1 1 1])
v3 = randvonMisesFisher(3,n,.1,[1 1 1])

v = [v1;v2;v3]

# make sure they are all unit vectors
for c=1:n
	for r=1:3
		nrm = norm( vec( v[(r-1)*3+1:(r-1)*3+3,c] ) )
		v[(r-1)*3+1:(r-1)*3+3,c] /= nrm
	end
end

v = v'


println("size(v) = ", size(v))

#lm = LogMap(v',[1 1 1])

#em = ExpMap(lm,[0.8 0.8 0.8])

#K = SphericalCosKernel(v,v)
Kp = SphericalKernel(v,v)

#println("fro: ", vecnorm(K-Kp))
#println("l2: ", norm(K-Kp))

Kp2 = SphericalKernelLowMem(v,v)

println("fro: ", vecnorm(Kp-Kp2))
println("l2: ", norm(Kp-Kp2))

Cov = SphericalCovariance(v)

println("Spherical Feature and Inverse: ")

println("v: ", v)
Phi = SphericalFeature(v)
println("Phi: ", Phi)

X = SphericalFeatureInverse(Phi)
println("v': ", X)

println("fro: ", vecnorm(v-X))
println("l2: ", norm(v-X))



