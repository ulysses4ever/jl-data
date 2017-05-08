using tokenizer
using Base.Test

function test_tokenize()
  @assert "1[aa] 259[ ] 1[bb]" == toks("aa bb")
end

function test_iter()
  toks = tokens("aa bb")
  st = start(toks)
  @assert !done(toks, st)

  (it, st) = next(toks, st)
  @assert (WORD, "aa") == it
  @assert !done(toks, st)

  (it, st) = next(toks, st)
  @assert (SPEC_SP, " ") == it
  @assert !done(toks, st)

  (it, st) = next(toks, st)
  @assert (WORD, "bb") == it
  @assert done(toks, st)
end

function toks(s::String)
  str(it) = "$(it[1])[$(it[2])]"
  join(map(str, tokens(s)), " ")
end

test_tokenize()
test_iter()
