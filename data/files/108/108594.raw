module Cuhre

export cuhre

const libcuba = Pkg.dir("Cuhre", "deps", "cuba", "libcuba")

# Call to Cuhre(const int ndim, const int ncomp, integrand_t integrand,
#               void *userdata, const double epsrel, const double epsabs,
#               const int flags, const int mineval, const int maxeval,
#               const int key, const char *statefile, int *nregions,
#               int *neval, int *fail, double integral[], double error[],
#               double prob[])
#
# Always sets key = 0 and randomly generates statefile name.
#
# A function f of type integrand_t has the signature:
# int f(const int *ndim, const double x[], const int *ncomp,
#       double f[], void *userdata)
#
# The integrand provided as an argument to the following function should
# have the Julia-equivalent signature. Within the integrand function,
# x and f must be converted to arrays using pointer_to_array().
function cuhre(ndim::Int, ncomp::Int, integrand::Function, userdata::Any,
               epsrel::Float64, epsabs::Float64, flags::Int, mineval::Int,
               maxeval::Int)
    integrand_wrap = cfunction(integrand, Int32, (Ptr{Int32}, Ptr{Float64},
                               Ptr{Int32}, Ptr{Float64}, Ptr{Void}))
    # Use default integration rule.
    key = 0   
    # Generate random string for statefile name.
    statefile_name_len = 40
    statefile = bytestring(randstring(statefile_name_len))
    # Return values: integers.
    nregions = Int32[0]
    neval = Int32[0]
    fail = Int32[0]
    # Return values: double arrays.
    integral = Array(Float64, ncomp)
    error = Array(Float64, ncomp)
    prob = Array(Float64, ncomp)

    ccall((:Cuhre, libcuba), Int32, (Int32, Int32, Ptr{Void}, Ptr{Void},
          Float64, Float64, Int32, Int32, Int32, Int32, Ptr{Int8}, 
          Ptr{Int32}, Ptr{Int32}, Ptr{Int32}, Ptr{Float64}, Ptr{Float64},
          Ptr{Float64}), ndim, ncomp, integrand_wrap, userdata, epsrel,
          epsabs, flags, mineval, maxeval, key, statefile, nregions,
          neval, fail, integral, error, prob)

    return (nregions, neval, fail, integral, error, prob)
end

end
