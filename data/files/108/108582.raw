using Base.Test
using Cuhre

function fTest(ndim, x, ncomp, f, userdata)
    ret::Int32
    x_v = pointer_to_array(x, (int(ndim),))
    f_v = pointer_to_array(f, (int(ncomp),))
    f_v[1] = sin(x_v[1])^2
    f_v[2] = cos(x_v[2])^2 - 1.0
    f_v[3] = sin(x_v[1])
    ret = 0
    return ret
end

ndim = 2
ncomp = 3
userdata = 0
epsrel = 1e-9
epsabs = 1e-9
flags = 1
mineval = 10
maxeval = 10^9
nregions, neval, fail, integral, error, prob = cuhre(ndim, ncomp, fTest,
        userdata, epsrel, epsabs, flags, mineval, maxeval)
expected = [0.272675643293580, -0.272675643293580, 0.459697694131860]

@test fail == 0
println(nregions, neval)
println(integral)
println(error)
println(prob)
for i = 1:length(expected)
    @test_approx_eq_eps integral[i] expected[i] 2.0*epsabs
end
println("cuhre() test passed.")
