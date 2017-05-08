t = ccall( (:clock, "libc"), Int32, ())
println(t)

a = ccall((:main, "/home/shagun/Brown/brown_sample_codes/learning_julia/libshared"), Uint8, ())
println(a)

k = ccall((:testfn, "/home/shagun/Brown/brown_sample_codes/learning_julia/libshared"), Uint8, (Uint32,), 128)
println(k)

l = ccall((:testfn2, "/home/shagun/Brown/brown_sample_codes/learning_julia/libshared"), Uint8, (Uint32, Uint32), 5, 2)
println(l)

b = ccall((:main2, "/home/shagun/Brown/brown_sample_codes/learning_julia/libshared"), Uint8, ())
println(b)
