x = 9007199254740994.0; # 2^53 + 2
y = 1.0 - 1.0/65536.0;
z = x + y;
d = z - x;
doublerounding_test = (d == 0.0);

function tst_log1p(x::Float64)
    if (1.0 + x == 1.0)
       x
    else
       (log(1.0 + x) * x) / ((1.0 + x) - 1.0)
    end
end;

extendedprec_test = (tst_log1p(1.0e-10) == 9.999999999500001e-11);

a = reinterpret(Float64, 0xbF1A28A5F3777D60); # ~ -9.97878E-5
b = reinterpret(Float64, 0xbf43a04556d864ae); # ~ -5.989E-004
c = reinterpret(Float64, 0xbfc55364b6b08299); # ~ -0.166
abc_with_fma    = reinterpret(Float64, 0xBBBAD89127ADE008); # ~ -5.694854e-21

fma_version_test = VERSION >= v"0.4.0-dev+2823";
fma_test = fma_version_test ? (fma(b,c,a) == abc_with_fma) : false;

function show_result()
    if !doublerounding_test
        println("double rounding occured")
    end
    if !extendedprec_test
        println("extended precision alters result")
    end
    if fma_version_test & !fma_test
        println("hardware/software fma does not work properly")
    end
    if (doublerounding_test & extendedprec_test & fma_test)
        println("\n\t\t\t The numerics tested work properly.\n")
    elseif ((doublerounding_test & extendedprec_test) && !fma_version_test)
        println("\n\t\t\t The numerics tested work properly.\n The version you are using does not support fma.\n")
    end
end;

if true show_result() end; # run the tests   
