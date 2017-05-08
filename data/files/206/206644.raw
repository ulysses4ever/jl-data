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
@ctypedef DES_cblock Void
@ctypedef const_DES_cblock Void
type DES_ks
  ks::Void
end
@ctypedef DES_key_schedule DES_ks
type MD5state_st
  A::Uint32
  B::Uint32
  C::Uint32
  D::Uint32
  Nl::Uint32
  Nh::Uint32
  data::Void
  num::Uint32
end
@ctypedef MD5_CTX MD5state_st
type MD4state_st
  A::Uint32
  B::Uint32
  C::Uint32
  D::Uint32
  Nl::Uint32
  Nh::Uint32
  data::Void
  num::Uint32
end
@ctypedef MD4_CTX MD4state_st
type mdc2_ctx_st
  num::Uint32
  data::Void
  h::DES_cblock
  hh::DES_cblock
  pad_type::Int32
end
@ctypedef MDC2_CTX mdc2_ctx_st
type SHAstate_st
  h0::Uint32
  h1::Uint32
  h2::Uint32
  h3::Uint32
  h4::Uint32
  Nl::Uint32
  Nh::Uint32
  data::Void
  num::Uint32
end
@ctypedef SHA_CTX SHAstate_st
type SHA256state_st
  h::Void
  Nl::Uint32
  Nh::Uint32
  data::Void
  num::Uint32
  md_len::Uint32
end
@ctypedef SHA256_CTX SHA256state_st
type SHA512state_st
  h::Void
  Nl::Uint64
  Nh::Uint64
  u::
  num::Uint32
  md_len::Uint32
end
@ctypedef SHA512_CTX SHA512state_st
type rand_meth_st
  seed::Ptr{Void}
  bytes::Ptr{Void}
  cleanup::Ptr{Void}
  add::Ptr{Void}
  pseudorand::Ptr{Void}
  status::Ptr{Void}
end
