using Orthopolys
using Polynomials
using Base.Test


# Test hermiteH()
Hs = Dict(
    0  => Poly([1]),
    1  => Poly([0,2]),
    2  => Poly([-2,0,4]),
    3  => Poly([0,-12,0,8]),
    4  => Poly([12,0,-48,0,16]),
    10 => Poly([-30240,0,302400,0,-403200,0,161280,0,-23040,0,1024])
)

for (n,p)=Hs
    @test p==hermiteH(n)
end


# Test hermiteHe()
Hes = Dict(
    0 => Poly([1]),
    1  => Poly([0,1]),
    2  => Poly([-1,0,1]),
    3  => Poly([0,-3,0,1]),
    4  => Poly([3,0,-6,0,1]),
    10 => Poly([-945,0,4725,0,-3150,0,630,0,-45,0,1])
)

for (n,p)=Hes
    @test p==hermiteHe(n)
end


# Test legendre()
legendres = Dict(
    0 => Poly([1]),
    1  => Poly([0,1]),
    2  => Poly([-1,0,3]//2),
    3  => Poly([0,-3,0,5]//2),
    4  => Poly([3,0,-30,0,35]//8),
    10 => Poly([-63,0,3465,0,-30030,0,90090,0,-109395,0,46189]//256)
)

for (n,p)=legendres
    @test p==legendre(n)
end
