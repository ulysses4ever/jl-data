t = ccall( (:clock, "libc"), Int32, ())
println(t)

k = ccall( (:testfn, "/home/shagun/Brown/trial/libshared"), Uint8, (Uint32,), 128)
println(k)

l = ccall( (:testfn2, "/home/shagun/Brown/trial/libshared"), Uint8, (Uint32, Uint32), 5, 2)
println(l)
