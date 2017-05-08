module Cuhre

tagfile = Pkg.dir("Cuhre", "deps", "installed_vers")
cubavers = readchomp(tagfile)
const libcuba = Pkg.dir("Cuhre", "deps", "Cuba-$cubavers", "libcuba")

function cuhre(ndim::Int32, ncomp::Int32, integrand::Function, userdata::Any,
               epsrel::Float64, epsabs::Float64, flags::Int32, mineval::Int32,
               maxeval::Int32)
    # Call to Cuhre(const int ndim, const int ncomp, integrand_t integrand,
    #               void *userdata, const int nvec, const double epsrel,
    #               const double epsabs, const int flags, const int mineval,
    #               const int maxeval, const int key, const char *statefile,
    #               void *spin, int *nregions, int *neval, int *fail,
    #               double integral[], double error[], double prob[])
    #
    # A function f of type integrand_t has the signature:
    # int f(const int *ndim, const double x[], const int *ncomp,
    #       double f[], void *userdata)
    integrand_wrap = cfunction(integrand, Int32, (Ptr{Int32}, Ptr{Float64},
                               Ptr{Int32}, Ptr{Float64}, Ptr{Void}))
    # One x value per f(x, v) evaluation.
    nvec = 1
    # Use default integration rule.
    key = 0   
    # Generate random string for statefile name.
    statefile_name_len = 40
    statefile = randstring(statefile_name_len)
    # Let Cuhre handle starting/stopping integration processes.
    spin = -1
    # Return values: integers.
    nregions, neval, fail = 0, 0, 0
    # Return values: double arrays.
    integral = zeros(Float64, ncomp)
    error = zeros(Float64, ncomp)
    prob = zeros(Float64, ncomp)

    ccall((:Cuhre, libcuba), Int32, (Int32, Int32, Ptr{Void}, Ptr{Void}, Int32,
          Float64, Float64, Int32, Int32, Int32, Int32, Ptr{Char}, Ptr{Void},
          Ptr{Int32}, Ptr{Int32}, Ptr{Int32}, Ptr{Float64}, Ptr{Float64},
          Ptr{Float64}), ndim, ncomp, integrand_wrap, userdata, nvec, epsrel,
          epsabs, flags, mineval, maxeval, key, statefile, spin, nregions,
          neval, fail, integral, error, prob)

    return (nregions, neval, fail, integral, error, prob)
end

end
