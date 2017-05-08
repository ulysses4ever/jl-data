t = ccall( (:clock, "libc"), Int32, ())
println(t)

a = ccall((:main, "/home/shagun/Brown/brown_sample_codes/class_lib/libmyclass"), Uint8, ())
println(a)

c = ccall((:test, "/home/shagun/Brown/brown_sample_codes/class_lib/libmyclass"), Uint8, ())
println(c)

b = ccall((:set_class, "/home/shagun/Brown/brown_sample_codes/class_lib/libmyclass"), Ptr{Void}, (Uint8,), 4)
d = ccall((:set_class, "/home/shagun/Brown/brown_sample_codes/class_lib/libmyclass"), Uint8, (Ptr{Void},), 4)
