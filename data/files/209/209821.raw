p = pwd()
cd(Pkg.dir("EiSCor/deps/eiscor-master"))
run(`make`)
is_apple()   ? run(`cp libeiscor.dylib.0.1.0 ../libeiscor.dylib`) : nothing
is_linux()   ? run(`cp libeiscor.so.0.1.0 ../libeiscor.so`) : nothing
is_windows() ? run(`cp libeiscor.dll.0.1.0 ../libeiscor.dll`) : nothing
cd(p)
