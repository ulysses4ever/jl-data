macro c(ret_type, func, arg_types, lib)
  local args_in = Any[ symbol(string('a',x)) for x in 1:length(arg_types.args) ]
  quote
    $(esc(func))($(args_in...)) = ccall( ($(string(func)), $(Expr(:quote, lib)) ), $ret_type, $arg_types, $(args_in...) )
  end
end

macro ctypedef(fake_t,real_t)
  quote
    typealias $fake_t $real_t
  end
end

type aes_key_st
  rd_key::Void
  rounds::Int32
end
@ctypedef AES_KEY aes_key_st
type rand_meth_st
  seed::Ptr{Void}
  bytes::Ptr{Void}
  cleanup::Ptr{Void}
  add::Ptr{Void}
  pseudorand::Ptr{Void}
  status::Ptr{Void}
end
