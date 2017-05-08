module Cuhre

export cuhre, cuhreComplex

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
    if ndim <= 1
        error("Cuhre requires number of integration regions dimensions > 1.")
    end
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

    ccall((:Cuhre, libcuba), Int32, (Int32, Int32, Ptr{Void}, Any,
          Float64, Float64, Int32, Int32, Int32, Int32, Ptr{Int8}, 
          Ptr{Int32}, Ptr{Int32}, Ptr{Int32}, Ptr{Float64}, Ptr{Float64},
          Ptr{Float64}), ndim, ncomp, integrand_wrap, userdata, epsrel,
          epsabs, flags, mineval, maxeval, key, statefile, nregions,
          neval, fail, integral, error, prob)

    return (nregions, neval, fail, integral, error, prob)
end

# Integrate the given integrand in the region specified by (a, b), where
# a and b are vectors of the same length.
#
# integrandComplex has the signature f(x, v), where x and v are
# Julia vectors of Float64's (of length ndim) and Complex{Float64}'s (of
# length ncomp) respectively. f(x, v) evaluates f(x) and stores
# the result in v.
#
# Passes integrandComplex into cuhre() in a way compatible with ccall (i.e.
# functions used with cfunction must be in global scope) using the technique
# described in: http://julialang.org/blog/2013/05/callback/
function cuhreComplex(ncomp::Int, integrandComplex::Function, epsrel::Float64,
                      epsabs::Float64, flags::Int, mineval::Int, maxeval::Int,
                      a::Vector{Float64}, b::Vector{Float64})
    if length(a) != length(b)
        error("length(a) and length(b) must be the same in cuhreComplex().")
    end

    ndim = length(a)
    ncompReal = 2*ncomp
    userdata = Any[integrandComplex, a, b]
    nregions, neval, fail, integral, error, prob = cuhre(ndim, ncompReal,
            integrandComplex_wrap, userdata, epsrel, epsabs, flags, mineval,
            maxeval)

    integralComplex = zeros(Complex{Float64}, ncomp)
    errorComplex = zeros(Float64, ncomp)
    probComplex = zeros(Float64, ncomp)
    for i = 1:ncomp
        integralComplex[i] = integral[2*i-1] + 1.0im*integral[2*i]
        errorComplex[i] = error[2*i-1] + error[2*i]
        probComplex[i] = prob[2*i-1] + prob[2*i]
    end
    return nregions, neval, fail, integralComplex, errorComplex, probComplex
end

function integrandComplex_wrap(ndim::Ptr{Int32}, x::Ptr{Float64},
                               ncompReal::Ptr{Int32}, f::Ptr{Float64},
                               userdata::Ptr{Void})
    ret::Int32
    ndim_int = unsafe_load(ndim)
    ncomp_int = unsafe_load(ncompReal)
    x_v = pointer_to_array(x, (int(ndim_int),))
    f_v = pointer_to_array(f, (int(ncomp_int),))

    userDataList = unsafe_pointer_to_objref(userdata)::Vector{Any}
    integrandComplex = userDataList[1]::Function
    a, b = userDataList[2]::Vector{Float64}, userDataList[3]::Vector{Float64}

    # TODO - is there a good thread-safe way to avoid allocation here?
    x, Jacobian = convertBounds(x_v, a, b)
    v = zeros(Complex{Float64}, ncomp_int)
    #integrandComplex = unsafe_pointer_to_objref(userdata)::Function
    integrandComplex(x, v)
    for i = 1:ncomp_int/2
        f_v[2*i-1] = real(v[i]) * Jacobian
        f_v[2*i] = imag(v[i]) * Jacobian
    end
    ret = 0
    return ret
end

# Convert x_v in the hypercube [0..1, 0..1, ...] to the corresponding point
# in the region defined by [a1..b1, a2..b2, ...]. Also return the Jacobian
# of this transformation, equal to (b1 - a1)*(b2 - a2)*...
function convertBounds(x_v, a, b)
    ndim = length(x_v)
    x = zeros(Float64, ndim)
    Jacobian = 1.0
    for i = 1:ndim
        x[i] = a[i] + (b[i] - a[i])*x_v[i]
        Jacobian *= (b[i] - a[i])
    end
    return x, Jacobian
end

end
