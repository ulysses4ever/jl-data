include("../src/tokenizer.jl")
using Base.Test
using tokenizer

function test_tokenize()
  @assert "1[aa] 3[ ] 1[bb]" == toks("aa bb")
end

function test_iter()
  toks = tokens("aa bb")
  st = start(toks)
  @assert !done(toks, st)

  (it, st) = next(toks, st)
  @assert WORD == it.typ
  @assert "aa" == it.token
  @assert !done(toks, st)

  (it, st) = next(toks, st)
  @assert SPEC_SP == it.typ
  @assert " " == it.token
  @assert !done(toks, st)

  (it, st) = next(toks, st)
  @assert WORD == it.typ
  @assert "bb" == it.token
  @assert done(toks, st)
end

function toks(s::String)
  str(it) = "$(it.typ)[$(it.token)]"
  join(map(str, tokens(s)), " ")
end

test_tokenize()
test_iter()
