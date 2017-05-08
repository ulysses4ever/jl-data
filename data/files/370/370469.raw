using LotkaVolterra
using Base.Test

# wstability of competitive lv systems in 2d, from Murray Mathematical Biology, p97
function nondimclv2d(a12,a21)
    ρ=1
    r = [1.,ρ]
    A = -[1 a12; ρ*a21 ρ]
    return GeneralizedLotkaVolterra(r,A)
end

#form solutions
Zs = [nondimclv2d(a12,a21) for a12=[1/3,4/3], a21=[1/3,4/3]]
xs = map(Z->collect(fixedpoints(Z,:stable)),Zs)
#test for correct number
nstable = map(length,xs)
@test nstable[1,1] == 1
@test nstable[1,2] == 1
@test nstable[2,1] == 1
@test nstable[2,2] == 2
#test for correct values
@test_approx_eq xs[1,1][1] [3/4,3/4]
@test_approx_eq xs[1,2][1] [1.,0.]
@test_approx_eq xs[2,1][1] [0.,1.]
@test_approx_eq xs[2,2][1] [1.,0.]
@test_approx_eq xs[2,2][2] [0.,1.]
