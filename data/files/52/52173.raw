module c

include("../deps/deps.jl")

export
  # Token types
  WORD, WORD_F, NUM, SPEC, SPEC_SP, SPEC_PUNCT, URL, OTHER,

  # Types
  Scanner, Token,

  # Methods
  Scanner_init, Scanner_next

# Token types
const WORD   = convert(Cint, 0x0001)
const WORD_F = convert(Cint, 0x0101)
const NUM    = convert(Cint, 0x0002)
const SPEC       = convert(Cint, 0x0003)
const SPEC_SP    = convert(Cint, 0x0103)
const SPEC_PUNCT = convert(Cint, 0x0203)
const URL    = convert(Cint, 0x0004)
const OTHER  = convert(Cint, 0x0005)

typealias CString Ptr{Uint8}

immutable Scanner
  s::CString
  length::Csize_t
  pos::CString
end

immutable Token
  typ::Cint
  start::CString
  length::Csize_t
end

# Initialize Scanner object
function Scanner_init(scanner, string, length)
  ccall((:Scanner_init, libtokenizer), Void, (Ptr{Scanner}, CString, Csize_t),
    scanner, string, length)
end

# Move to the next token
function Scanner_next(scanner, token)
  ccall((:next, libtokenizer), Cint, (Ptr{Scanner}, Ptr{Token}),
    scanner, token)
end

end # module
