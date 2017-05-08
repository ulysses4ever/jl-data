module tokenizer

import Base: start, next, done

export
  # Token types
  WORD, NUM, SPEC_SP, SPEC_PUNCT, UNKNOWN,
  Token, tokens

const UNKNOWN = 0
const WORD = 1
const NUM  = 2
const SPEC_SP = 3
const SPEC_PUNCT = 4

immutable Tokens
  s::String
end

immutable Token
  typ::Int
  token::String
end

function tokens(s::String)
  Tokens(s)
end

function start(tokens::Tokens)
  start(tokens.s)
end

function next(tokens::Tokens, start::Int)
  if done(tokens.s, start)
    throw(BoundsError())
  end

  _end = start
  c, _cur = next(tokens.s, start)
  typ = _type(c)
  while !done(tokens.s, _cur)
    c, _next = next(tokens.s, _cur)
    if typ != _type(c)
      break
    end
    _end, _cur = _cur, _next
  end
  item = Token(typ, SubString(tokens.s, start, _end))
  (item, _cur)
end

function done(tokens::Tokens, pos::Int)
  done(tokens.s, pos)
end

function _type(c::Char)
  if isalpha(c)
    return WORD
  elseif isdigit(c)
    return NUM
  elseif isspace(c)
    return SPEC_SP
  elseif ispunct(c)
    return SPEC_PUNCT
  else
    return UNKNOWN
  end
end

end # module
