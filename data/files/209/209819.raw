p = pwd()
cd(Pkg.dir("EiSCor/deps/eiscor-master"))
run(`make`)
@osx? run(`cp libeiscor.dylib.0.1.0 ../libeiscor.dylib`) : nothing
@linux? run(`cp libeiscor.so.0.1.0 ../libeiscor.so`) : nothing
@windows? run(`cp libeiscor.dll.0.1.0 ../libeiscor.dll`) : nothing
cd(p)
