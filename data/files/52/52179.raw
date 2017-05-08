module tokenizer

include("c.jl")
using .c

import Base: start, next, done

export
  # Token types
  WORD, WORD_F, NUM, SPEC, SPEC_SP, SPEC_PUNCT, URL, OTHER,
  Tokens, tokens

immutable Tokens
  s::String
end

function tokens(s::String)
  Tokens(bytestring(s))
end

function start(tokens::Tokens)
  pscanner = Scanner[Scanner(C_NULL, 0, C_NULL)]
  Scanner_init(pscanner, tokens.s, length(tokens.s))
  pscanner[1]
end

function next(tokens::Tokens, st::Scanner)
  pscanner = Scanner[st]
  ptoken = Token[Token(0, C_NULL, 0)]
  c = Scanner_next(pscanner, ptoken)
  item = (ptoken[1].typ, bytestring(ptoken[1].start, ptoken[1].length))
  (item, pscanner[1])
end

function done(tokens::Tokens, st::Scanner)
  st.length <= st.pos-st.s
end

end # module
