#=
    Jeffrey Sarnoff's preconditions for portable and reliable floating point (first phase)
    Copyright Ⓒ2016 by Jeffrey A. Sarnoff.  All Rights Reserved.  
    
    This material may be used for academic research and non-commerical eleemosynary work.
    Prior written permission is required for all other utilizations (gmail: my.name).
=#
#=
    created 2016-Apr-12
    updated 2017-Feb-21:  provide ldexp() expressions


    sources and refs:

        IEEE754-2008 compliance: Does imprecise double rounding occur?
            the function http://www.vinc17.org/software/test.java
            both results http://www.vinc17.org/research/extended.en.html
            as a gcc bug https://gcc.gnu.org/bugzilla/show_bug.cgi?id=16122

        Floating Point Mulitply and Accumlate: Does FMA augment the product without error?
            fma tests: http://www.vinc17.net/software/fma-tests.c
            this and more:  http://www.vinc17.net/research/fptest.en.html


Each of these tests comes from a 
=#

#=
    x = ldexp(0.5000000000000001, 54)  ~=  9.007199254740994e15
    y = ldexp(0.9999847412109375,  0)  ~=  0.9999847412109375
=#
x = 9007199254740994.0 # 2^53 + 2
y = 1.0 - 1.0/65536.0 

z = x + y
d = z - x

doublerounding_test = (d == 0.0);

function tst_log1p(x::Float64)
    if (1.0 + x == 1.0)
       x
    else
       (log(1.0 + x) * x) / ((1.0 + x) - 1.0)
    end
end

#=
     t = ldexp(0.8589934591570504, -33) ~=  9.999999999500001e-11
=#
extendedprec_test = (tst_log1p(1.0e-10) == t)

#=
      a    =  ldexp(-0.6664298599390178,  -2) ~= -0.16660746498475446
       b   =  ldexp(-0.6133143135258672, -10) ~= -0.0005989397593026047
        c  =  ldexp(-0.8174619441232771, -13) ~= -9.978783497598597e-5

  fma_abc  =  ldexp(-0.8389364027962083, -67) ~= -5.684854190555145e-21
=#

    a   = reinterpret(Float64, 0xbfc55364b6b08299)  # ~ -0.166607465
    b   = reinterpret(Float64, 0xbf43a04556d864ae)  # ~ -0.00059894
    c   = reinterpret(Float64, 0xbF1A28A5F3777D60)  # ~ -9.97878349e-5

fma_abc = reinterpret(Float64, 0xBBBAD89127ADE008)  # ~ -5.69485419e-21

fma_test = (fma(a, b, c) == fma_abc)



function show_results()
    ok = false
    if !doublerounding_test
        println("double rounding occured")
    end
    if !extendedprec_test
        println("extended precision alters result")
    end
    if !fma_test
        println("hardware/software fma does not work properly")
    end
    if (doublerounding_test & extendedprec_test & fma_test)
        ok = true
    else
        println("\n\tCAUTION\n")
    end
    return ok
end

if !show_results()
    throw(ErrorException("The floating point environment is unusable."))
end        
