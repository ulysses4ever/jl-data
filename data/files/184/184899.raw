using Base.Test

macro jt(ex)
  description = ex.args[2]
  println(ex.args[2])
  println(ex.args[4])
end

@jt begin "One plus one equals two"
  (1 + 1) == 2
end
