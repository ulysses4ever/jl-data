export MCExpr
export var, @var, show
export +, -, *
export mcvx_begin, mcvx_end, minimize, maximize
export @mcvx
export resolve, @resolve
export solver_coorddesc
export init_zero, init_randn

#########################################################
# type definitions
#########################################################

abstract MCExpr
abstract MCFun

immutable EVar <: MCExpr
  idx  :: Int64
  name :: String
end

immutable EConst <: MCExpr
  val  :: Float64
end

immutable EPlus <: MCExpr
  x    :: MCExpr
  y    :: MCExpr
end

immutable ENeg <: MCExpr
  x    :: MCExpr
end

immutable ETimes <: MCExpr
  x    :: MCExpr
  y    :: MCExpr
end

immutable EApp <: MCExpr
  f    :: MCFun
  x    :: MCExpr
end

#########################################################
# global module state
#########################################################

problem_size = nothing
problem_var = nothing
problem_obj = nothing
problem_init = nothing
problem_solver = nothing

#########################################################
# variable declaration
#########################################################

function var(name :: String)
  global problem_size
  if (problem_size == nothing)
    error("mcvx tried to create var outside mcvx block")
  end
  problem_size += 1
  rv = EVar(problem_size, name)
  return rv
end

var(name :: String, dim1 :: Int64) = MCExpr[ var("$name[$i1]") for i1 = 1:dim1 ]
var(name :: String, dim1 :: Int64, dim2 :: Int64) = MCExpr[ var("$name[$i1,$i2]") for i1 = 1:dim1, i2 = 1:dim2 ]

function var()
  return var("problem_var[$(problem_size+1)]")
end

var(dim1 :: Int64) = MCExpr[ var() for i1 = 1:dim1 ]
var(dim1 :: Int64, dim2 :: Int64) = MCExpr[ var() for i1 = 1:dim1, i2 = 1:dim2 ]


macro var(sym :: Symbol, dims...)
  name = string(sym)
  if (length(dims) == 0)
    return esc(:( $sym = var($name) ))
  elseif (length(dims) == 1)
    dim1 = dims[1]
    return esc(:( $sym = var($name, $dim1) ))
  elseif (length(dims) == 2)
    dim1 = dims[1]
    dim1 = dims[2]
    return esc(:( $sym = var($name, $dim1, $dim2) ))
  else
    error("more than two-dimensional variables not supported yet!")
  end
end

#########################################################
# overloading show for MCExpr
#########################################################

import Base.show

function show(io :: IO, e :: MCExpr)
  error("show not implemented for MCExpr!")
end

function show(io :: IO, e :: EVar)
  print(io, e.name)
end

function show(io :: IO, e :: EConst)
  print(io, e.val)
end

function show(io :: IO, e :: EPlus)
  sx = string(e.x)
  sy = string(e.y)
  print(io, "($sx + $sy)")
end

function show(io :: IO, e :: ENeg)
  sx = string(e.x)
  print(io, "(-$sx)")
end

function show(io :: IO, e :: ETimes)
  sx = string(e.x)
  sy = string(e.y)
  print(io, "($sx * $sy)")
end

#########################################################
# overloading number ops
#########################################################

function +(x :: MCExpr, y :: MCExpr)
  return EPlus(x, y)
end

function -(x :: MCExpr)
  return ENeg(x)
end

function *(x :: MCExpr, y :: MCExpr)
  return ETimes(x, y)
end

#########################################################
# constant folding
#########################################################

function +(x :: EConst, y :: EConst)
  return EConst(x.val + y.val)
end

function -(x :: EConst)
  return EConst(-x.val)
end

function *(x :: EConst, y :: EConst)
  return EConst(x.val * y.val)
end

function +(x :: EConst, y :: MCExpr)
  if (x.val == 0.0)
    return y
  else
    return EPlus(y, x)
  end
end

function +(x :: MCExpr, y :: EConst)
  if (y.val == 0.0)
    return x
  else
    return EPlus(x, y)
  end
end

function *(x :: EConst, y :: MCExpr)
  if (x.val == 0.0)
    return x
  elseif (x.val == 1.0)
    return y
  elseif (x.val == -1.0)
    return -y
  else
    return ETimes(x, y)
  end
end

function *(x :: MCExpr, y :: EConst)
  if (y.val == 0.0)
    return y
  elseif (y.val == 1.0)
    return x
  elseif (y.val == -1.0)
    return -x
  else
    return ETimes(y, x)
  end
end

#########################################################
# lifting constants to MCExpr types
#########################################################

typealias IntOrFloat Union(Float64, Int64)

function reify(x :: Int64)
  return EConst(float64(x))
end

function reify(x :: Float64)
  return EConst(x)
end

function +(x :: IntOrFloat, y :: MCExpr)
  return reify(x) + y
end

function +(x :: MCExpr, y :: IntOrFloat)
  return x + reify(y)
end

function -(x :: IntOrFloat, y :: MCExpr)
  return x + (-y)
end

function -(x :: MCExpr, y :: IntOrFloat)
  return x + (-y)
end

function *(x :: IntOrFloat, y :: MCExpr)
  return reify(x) * y
end

function *(x :: MCExpr, y :: IntOrFloat)
  return x * reify(y)
end

#########################################################
# derivatives
#########################################################

function deriv(e :: MCExpr, v :: EVar)
  error("deriv not implemented for MCExpr")
end

function deriv(e :: EVar, v :: EVar)
  if(e.idx == v.idx)
    return reify(1.0)
  else
    return reify(0.0)
  end
end

function deriv(e :: EConst, v :: EVar)
  return reify(0.0)
end

function deriv(e :: EPlus, v :: EVar)
  return deriv(e.x, v) + deriv(e.y, v)
end

function deriv(e :: ENeg, v :: EVar)
  return -deriv(e.x, v)
end

function deriv(e :: ETimes, v :: EVar)
  return deriv(e.x, v) * e.y + e.x * deriv(e.y, v)
end

#########################################################
# evaluating a MCExpr
#########################################################

function mceval(e :: MCExpr, problem_var :: Array{Float64,1})
  error("mceval not implemented for MCExpr")
end

function mceval(e :: EVar, problem_var :: Array{Float64,1})
  return problem_var[e.idx]
end

function mceval(e :: EConst, problem_var :: Array{Float64,1})
  return e.val
end

function mceval(e :: EPlus, problem_var :: Array{Float64,1})
  return mceval(e.x, problem_var) + mceval(e.y, problem_var)
end

function mceval(e :: ENeg, problem_var :: Array{Float64,1})
  return -mceval(e.x, problem_var)
end

function mceval(e :: ETimes, problem_var :: Array{Float64,1})
  return mceval(e.x, problem_var) * mceval(e.y, problem_var)
end

#########################################################
# modeling a problem
#########################################################

function mcvx_begin()
  global problem_size
  global problem_var
  global problem_obj
  global problem_init
  global problem_solver
  problem_size = 0
  problem_var = nothing
  problem_obj = nothing
  problem_init = nothing
  problem_solver = nothing
end

function mcvx_end()
  if (problem_obj == nothing)
    error("mcvx specified no objectives")
  end
  if (problem_init == nothing)
    # default initialization
    init_randn()
  end
  if (problem_solver == nothing)
    # default solver
    solver_coorddesc(1000, 0.01)
  end
  # initialize the problem variable
  problem_init()
  # solve the problem
  problem_solver()
end

function minimize(e :: MCExpr)
  global problem_obj
  if (problem_obj == nothing)
    problem_obj = e
  else
    error("mcvx specified two objectives")
  end
  nothing
end

function maximize(e :: MCExpr)
  minimize(-e)
  nothing
end

function mcvx_init_zero()
  global problem_var
  problem_var = zeros(problem_size)
end

function init_zero()
  global problem_init
  if (problem_init == nothing)
    problem_init = mcvx_init_zero
  else
    error("mcvx specified multiple initializations")
  end
end

function mcvx_init_randn()
  global problem_var
  problem_var = randn(problem_size)
end

function init_randn()
  global problem_init
  if (problem_init == nothing)
    problem_init = mcvx_init_randn
  else
    error("mcvx specified multiple initializations")
  end
end

function mcvx_solver_coorddesc(niters :: Int64, step_size :: Float64)
  # differentiate with respect to all the variables
  obj_derivs = [deriv(problem_obj, EVar(i, "")) for i = 1:problem_size]
  # initialize the state
  for iter = 1:niters
    for iv = 1:problem_size
      problem_var[iv] -= step_size * mceval(obj_derivs[iv], problem_var)
    end
  end
end

function solver_coorddesc(niters :: Int64, step_size :: Float64)
  function m_solver_coorddesc()
    mcvx_solver_coorddesc(niters, step_size)
  end
  global problem_solver
  if (problem_solver == nothing)
    problem_solver = m_solver_coorddesc
  else
    error("mcvx specified multiple solvers")
  end
end

function mcvx_solver_newton(objective :: MCExpr, niters :: Int64, alpha :: Float64)
  # differentiate with respect to all the variables
  obj_derivs = [deriv(objective, EVar(i, "")) for i = 1:problem_size]
  obj_2nddiffs = [deriv(obj_derivs[i], EVar(i, "")) for i = 1:problem_size]
  # initialize the state
  for iter = 1:niters
    for iv = 1:problem_size
      d1iv = mceval(obj_derivs[iv], problem_var)
      d2iv = mceval(obj_2nddiffs[iv], problem_var)
      problem_var[iv] -= alpha * d1iv / d2iv
    end
  end
end

function solver_newton(niters :: Int64, alpha :: Float64)
  function m_solver_newton()
    mcvx_solver_newton(niters, alpha)
  end
  global problem_solver
  if (problem_solver == nothing)
    problem_solver = m_solver_newton
  else
    error("mcvx specified multiple solvers")
  end
end

function solver_newton(niters :: Int64)
  solver_newton(niters, 0.5)
end

#########################################################
# resolving variables
#########################################################

function resolve(e)
  error("should not be called!")
end

function resolve(e :: MCExpr)
  return mceval(e, problem_var)
end

function resolve(e :: AbstractArray{MCExpr})
  return map(resolve, e)
end

macro resolve(sym :: Symbol)
  sym = esc(sym)
  return quote
    if ((typeof($sym) <: MCExpr)||(typeof($sym) <: AbstractArray{MCExpr}))
      $sym = resolve($sym)
    end
  end
end

#########################################################
# single macro for whole thing
#########################################################

function extract_assignments(b)
  return Symbol[]
end

function extract_assignments(b :: Expr)
  acc = Symbol[]
  if (b.head == :(=))
    if (typeof(b.args[1]) == Symbol)
      push!(acc, b.args[1])
    end
  end
  for a = b.args
    append!(acc, extract_assignments(a))
  end
  return unique(acc)
end

macro mcvx(block)
  asyms = extract_assignments(block)
  resolve_stmts = Any[]
  for s = asyms
    r = esc(s)
    push!(resolve_stmts, :(@resolve($r)))
  end
  block = esc(block)
  resolve_block = Expr(:block, resolve_stmts...)
  return quote
    mcvx_begin()
    $block
    mcvx_end()
    $resolve_block
    nothing
  end
end
