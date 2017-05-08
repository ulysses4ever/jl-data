import JulTest: @jt, runtests

@jt begin "One plus one equals two"
  @assert (1 + 2) == 2
end

@jt begin "verify x and y end up the same"
  x = 20
  y = 20
  @assert x == y
end

runtests()
