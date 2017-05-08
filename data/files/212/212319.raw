using Clang
using Clang.cindex
using Clang.wrap_cpp

t = ccall( (:clock, "libc"), Int32, ())
println(t)

a = @scall((:main, "/home/shagun/Brown/learning_julia/libshared"), Uint8, ())
println("main was executed successfully")

k = ccall((:testfn, "/home/shagun/Brown/learning_julia/libshared"), Uint8, (Uint32,), 128)
println(k)

l = ccall((:testfn2, "/home/shagun/Brown/learning_julia/libshared"), Uint8, (Uint32, Uint32), 5, 2)
println(l)

a = ccall((:main2, "/home/shagun/Brown/learning_julia/libshared"), Uint8, ())
println("main2 was executed successfully")

