let old = pwd()
    cd(joinpath(dirname(@__FILE__), "..", "deps", "decNumber"))
    run(`gcc decNumber.c decContext.c decSingle.c decDouble.c decQuad.c -O3 -fPIC -shared -o ../libDecNumber.dylib`)
    cd(old)
end
