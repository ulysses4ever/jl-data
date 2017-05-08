using JuliaSetPkg
using Base.Test


x=Array(linspace(-1,1,200))
y=Array(linspace(-1,1,200))
R = z -> (z^2 + -0.4+0.6*im )


#test size
A=juliaSet(R,x,y)
nx,ny=size(A)
@test length(x)==nx
@test length(y)==ny

#test fixed point
R = z -> z
A=juliaSet(R,x,y,100)
@test A == zeros(200,200)+101

