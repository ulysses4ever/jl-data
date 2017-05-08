module tokenizer

include("c.jl")
using .c

import Base: start, next, done

export
  Tokens, tokens

immutable Tokens
  s::String
end

function tokens(s::String)
  Tokens(bytestring(s))
end

function start(tokens::Tokens)
  pscanner = Scanner[1]
  Scanner_init(pscanner, tokens.s, length(tokens.s))
  pscanner[1]
end

function next(tokens::Tokens, st::Scanner)
  pscanner = Scanner[1]{st}
  ptoken = Token[1]
  c = c.next(pscanner, ptoken)
  item = (ptoken[1].type, bytestring(ptoken[1].start, ptoken[1].length)
  (item, pscanner[1])
end

function done(tokens::Tokens, st::Scanner)
  st.length <= st.pos-st.s
end

end # module
