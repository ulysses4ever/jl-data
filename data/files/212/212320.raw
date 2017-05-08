using Clang
using Clang.cindex

macro scall(ret_type, func, arg_types, sym, lib)
  local _args_in = Any[ symbol(string('a',x)) for x in 1:length(arg_types.args) ]
  hdl = dlopen(string(lib))
  fptr = dlsym_e(hdl, sym)
  if (fptr==C_NULL) return end
  quote
    function $(esc(func))($(_args_in...))
      ccall( $(esc(fptr)), $(esc(ret_type)), $(esc(arg_types)), $(_args_in...) )
    end
  end
end


t = ccall( (:clock, "libc"), Int32, ())
println(t)

a = @scall(Uint8, trial, (), main, "/home/shagun/Brown/brown_sample_codes/learning_julia/libshared") 
println("main was executed successfully")


b = @scall(Uint8, trial, (), main2, "/home/shagun/Brown/brown_sample_codes/learning_julia/libshared")
println("main2 was executed successfully")

k = ccall((:testfn, "/home/shagun/Brown/learning_julia/libshared"), Uint8, (Uint32,), 128)
println(k)

l = ccall((:testfn2, "/home/shagun/Brown/learning_julia/libshared"), Uint8, (Uint32, Uint32), 5, 2)
println(l)

