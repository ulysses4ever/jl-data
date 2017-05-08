# This is an example of using Julia's own random number generator
# with UNURAN.
using UNURAN

# We need the global because we can't use closures in cfunctions.
g_RNG=MersenneTwister[]

# Use a macro to make a function for each generator
# so that it can be wrapped with a cfunction call.
for dsfmt_idx = 1:3
  fdsfmtname=symbol(:julia_dsfmt, dsfmt_idx)
  @eval begin
    function $fdsfmtname( state::Ptr{UInt8} )
        convert(Cdouble, rand(g_RNG[($dsfmt_idx)]))::Cdouble
    end
  end
end

# The macro makes this:
# function julia_dsfmt1( state::Ptr{UInt8} )
#     convert(Cdouble, rand(g_RNG[1]))::Cdouble
# end
# function julia_dsfmt2( state::Ptr{UInt8} )
#     convert(Cdouble, rand(g_RNG[2]))::Cdouble
# end
# function julia_dsfmt3( state::Ptr{UInt8} )
#     convert(Cdouble, rand(g_RNG[3]))::Cdouble
# end

function UseJuliaRand()
    seed=42424242
    mt=MersenneTwister(seed)
    global g_RNG
    g_RNG=randjump(mt, 3) # Makes three lagged random number generators.

    const juliarng_c = cfunction(julia_dsfmt1, Cdouble, (Ptr{UInt8},))
    urng=unur_urng_fvoid_new(juliarng_c, C_NULL)
    for i = 1:10
        v=unur_urng_sample(urng)
        println(v)
    end
end


UseJuliaRand()
