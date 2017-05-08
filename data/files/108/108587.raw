using Base.Test
using Cuhre

# Test for cuhre():
# Integrate ftest = [sin(x[1])^2, cos(x[2])^2 - 1, sin(x[1])] over the region
# x[1] = 0 to 1, x[2] = 0 to 1.

function fTest(ndim::Ptr{Int32}, x::Ptr{Float64}, ncomp::Ptr{Int32}, 
               f::Ptr{Float64}, userdata::Ptr{Void})
    ret::Int32
    ndim_int = unsafe_load(ndim)
    ncomp_int = unsafe_load(ncomp)
    x_v = pointer_to_array(x, (int(ndim_int),))
    f_v = pointer_to_array(f, (int(ncomp_int),))
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

println("cuhre() call complete.")
println("fail = ", fail)
@test fail[1] == 0
println("nregions = ", nregions)
println("neval = ", neval)
println("integral = ", integral)
println("error = ", error)
println("prob = ", prob)
for i = 1:length(expected)
    @test_approx_eq_eps integral[i] expected[i] 2.0*epsabs
end
println("--- cuhre() test passed.")

# Test for cuhreComplex():
# Integrate ftestComplex = [sin(x[1])^2, i*(cos(x[2])^2 - 1), sin(x[1])] over
# the region x[1] = -pi to pi, x[2] = -pi to pi.

function fTestComplex(x, v)
    v[1] = sin(x[1])^2 + 0.0im
    v[2] = 0.0 + (cos(x[2])^2 - 1.0)*1.0im
    v[3] = sin(x[1]) + 0.0im
end
a = [-pi, -pi]
b = [pi*1.0, pi*1.0]
expected = [2.0*pi^2 + 0.0im, 0.0 - 2.0*pi^2*1.0im, 0.0+0.0im]

nregions, neval, fail, integral, error, prob = cuhreComplex(ncomp, fTestComplex,
        epsrel, epsabs, flags, mineval, maxeval, a, b)

println("cuhreComplex() call complete.")
println("fail = ", fail)
@test fail[1] == 0
println("nregions = ", nregions)
println("neval = ", neval)
println("integral = ", integral)
println("error = ", error)
println("prob = ", prob)
for i = 1:length(expected)
    @test_approx_eq_eps real(integral[i]) real(expected[i]) 2.0*epsabs
    @test_approx_eq_eps imag(integral[i]) imag(expected[i]) 2.0*epsabs
end
println("--- cuhreComplex() test passed.")
