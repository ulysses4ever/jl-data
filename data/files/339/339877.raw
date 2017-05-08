export abs

import Base.abs

immutable EAppAbs <: EApp
  x    :: MCExpr
end

immutable EAppSgn <: EApp
  x    :: MCExpr
end

function abs(e :: MCExpr)
  return EAppAbs(e)
end

function show(io :: IO, e :: EAppAbs)
  sx = string(e.x)
  sy = string(e.y)
  print(io, "abs($sx)")
end

function show(io :: IO, e :: EAppSgn)
  sx = string(e.x)
  sy = string(e.y)
  print(io, "sgn($sx)")
end

function deriv(e :: EAppAbs, v :: EVar)
  return EAppSgn(e.x) * deriv(e.x, v)
end

function deriv(e :: EAppSgn, v :: EVar)
  error("differentiating the sgn function not supported")
end

function mceval(e :: EAppAbs, problem_var :: Array{Float64,1})
  return abs(mceval(e.x, problem_var))
end

function mceval(e :: EAppSgn, problem_var :: Array{Float64,1})
  return sign(mceval(e.x, problem_var))
end

