using Base.Test

macro jt(ex)
  description = ex.args[2]
  try
    $ex
  catch error
    println(error)
  end
end

@jt begin "One plus one equals two"
  (1 + 1) == 2
end
