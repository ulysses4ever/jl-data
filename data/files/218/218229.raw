module Rewrite

using DataStructures


export xsub, xmatch, XMatch, rewrite, flatten, distribute_over, distribute_over2

import Base: (==)

# package code goes here
function xsub(e::Expr, subs::Dict)
  es = get(subs, e, nothing)
  if es != nothing
    return es
  end
  nh =  xsub(e.head, subs)
  nargs = [xsub(arg, subs) for arg=e.args]
  re = Expr(nh)
  re.args = nargs
  re
end

function xsub(e, subs::Dict)
  get(subs, e, e)
end

type Wildcard
  symbol::Symbol
#   minlength::Int64
#   maxlength::Int64
#   Wildcard(s) = new(symbol(s), 1, 1)
#   Wildcard(s,j,k) = new(symbol(s), int(j), int(k))
end


function matchrange(w::Wildcard)
  Int64[w.minlength, w.maxlength]
end

function matchrange(v::Vector)
  rng = zeros(Int, 2)
  for vj=v
    rng += matchrange(vj)
  end
  rng
end

function matchrange(x)
  Int64[1, 1]
end

type XMatch
  success::Bool
  subs::Dict{Symbol,Any}
  path::Vector{Int64}
  XMatch(success, subs, path) = new(success, subs, path)
  XMatch() = new(false, Dict{Symbol,Any}(),Int64[])
  XMatch(success::Bool) = new(success, Dict{Symbol,Any}(),Int64[])
  XMatch(success::Bool, path::Vector{Int64}) = new(success, Dict{Symbol,Any}(), path)
  XMatch(subs::Dict) = new(true, convert(Dict{Symbol,Any}, subs),Int64[])
  XMatch(subs::Dict, path::Vector{Int64}) = new(true, convert(Dict{Symbol,Any}, subs),path)
end

(==)(x1::XMatch, x2::XMatch) = (x1.success==x2.success) && (x1.subs == x2.subs)

function xmatch(p, e)
  XMatch(p==e)
end


function xmatch(p::Expr, e::Expr)
  mh = xmatch(p.head, e.head)
  if !mh.success
    return mh
  end
  p = xsub(p, mh.subs)
  ma = xmatch_args(p.args, e.args)
  if ma.success
    merge!(ma.subs, mh.subs)
    return ma
  else
    return XMatch()
  end
end

function xmatch(p::Symbol, e)
  ps = string(p)
  if endswith(ps, "_")
    if length(ps) == 1
      return XMatch(true)
    end
    return XMatch([p=>e])
  end
  return XMatch(p==e)
end

# AnyDict = Union(Dict{Any, Any}, OrderedDict{Any, Any})
# SymbolDict = Union(Dict{Symbol, AnyDict}, OrderedDict{Symbol, AnyDict})
# type Rules
#   atomic::AnyDict
#   ByHead::SymbolDict
#   CallByHead::SymbolDict
#   PartialCallByHead::SymbolDict
#   Rules() = new(OrderedDict{Any,AnyDict}(),OrderedDict{Symbol,AnyDict}(),OrderedDict{Symbol,AnyDict}(),OrderedDict{Symbol,AnyDict}())
# end

function xmatch_args(pargs::AbstractVector, eargs::AbstractVector)
  lp = length(pargs)
  le = length(eargs)
  if lp != le
    return XMatch(false)
  end
  m = XMatch(true)
  for k=1:lp
    mk = xmatch(xsub(pargs[k], m.subs), eargs[k])
    if !mk.success
      return mk
    end
    merge!(m.subs, mk.subs)
  end
  return m
end

# function xmatch_partial(callhead::Symbol, rules::Rules, eargs::AbstractVector)
#   prules = rules.PartialCallByHead[callhead]
#   lhs = keys(prules)
#   rhs = values(prules)

# end



# function rewrite(rules::Union(Dict, OrderedDict), e, recursive=true)
#   from = keys(rules)
#   to = values(rules)
#   success = true
#   while success
#     success = false
#     for (fk,tk) = zip(from, to)
#       xm = xmatch(fk, e)
#       if xm.success
#         if isa(tk, Function)
#           e = tk(;xm.subs...)
#         else
#           e = xsub(tk, xm.subs)
#         end
#         success = true
# #         println(e)
#       end
#     end
#   end
#   return e
# end






function rewrite_top(rules, e)
  from = keys(rules)
  to = values(rules)
  for (fk,tk) = zip(from, to)
    xm = xmatch(fk, e)
    if xm.success
      if isa(tk, Function)
        return XRewrite(true, tk(;xm.subs...))
      else
        return XRewrite(true, xsub(tk, xm.subs))
      end
    end
  end
  XRewrite(false, e)
end

type XRewrite
  success::Bool
  result
end

function rewrite_step(rules, e, recursive=true)
  rewrite_top(rules, e)
end

function rewrite_step(rules, e::Expr, recursive=true)
  success = false
  if recursive
    rh = rewrite_step(rules, e.head)
    success = rh.success
    nargs = {}
    for arg in e.args
      rarg = rewrite_step(rules, arg, recursive)
      success = success || rarg.success
      push!(nargs, rarg.result)
    end
    e = Expr(rh.result)
    e.args = nargs
  end
  rt = rewrite_top(rules, e)
  return XRewrite(rt.success || success, rt.result)
end


function xrewrite(rules, e, recursive=true)
#   print(e, " [ ")
  success = true
  anysuccess = false
  while success
    er = rewrite_step(rules, e, recursive)
    success = er.success
    anysuccess = anysuccess || success
    e = er.result
  end
#   println(" ] -> ", e)
  XRewrite(anysuccess, e)
end

function rewrite(rules, e, recursive=true)
  xres = xrewrite(rules, e, recursive)
  xres.result
end





function rewrite_partial(rules, e::Expr, recursive=true)

end





function flatten(e, args...)
  e
end

function operands(op, e::Expr)
  if e.head === :call && first(e.args) === op
    e.args[2:end]
  else
    Any[e]
  end
end

function operands(op, e)
  Any[e]
end


function flatten(e::Expr, flat_ops=[:+,:*], recursive::Bool=true)
  if isa(flat_ops, Symbol)
    flat_ops = [flat_ops]
  end
  fargs = e.args
  if recursive
    fargs = [flatten(arg, flat_ops, recursive) for arg in e.args]
  end
  nargs = {}
  if e.head === :call
    op = first(fargs)
    push!(nargs, op)
    for a in fargs[2:end]
      append!(nargs, operands(op, a))
    end
  else
    nargs = fargs
  end
  re = Expr(e.head)
  re.args = nargs
  re
end


function distribute_over(ex::Expr, operations, over::Symbol=:(+), recursive=true, flatten_expr=true)
  if recursive
      args = [distribute_over(ea, operations, over, recursive, flatten_expr) for ea=ex.args]
  else
      args = copy(ex.args)
  end

  if flatten_expr
    ex = flatten(Expr(ex.head, args...), [operations, over], recursive)
    args = ex.args
  end

  if ex.head === :call && (args[1] in operations)
    factor_args = {}
    dims = Int64[]
    for kk=2:length(args)
      arg = args[kk]
      if (isa(arg, Expr) && arg.head === :call && arg.args[1] === over)
        push!(factor_args, arg.args[2:end])
        push!(dims, length(arg.args)-1)
      else
        push!(factor_args, [arg])
        push!(dims, 1)
      end
    end
    ret = Expr(:call, over)
    for idxs in cartesianiter(dims...)
      part = Expr(:call, args[1])
      for (k, idx) = enumerate(idxs)
        current = factor_args[k][idx]

        if flatten_expr && isa(current, Expr) && current.head === :call && current.args[1] === args[1]

          append!(part.args, current.args[2:end])
        else
          push!(part.args, current)
        end
      end

      push!(ret.args, part)
    end
    ret
  else
    re = Expr(ex.head)
    re.args = args
    re
  end
end

function distribute_over(ex, operations, over::Symbol=:(+), recursive=true, flatten=true)
    ex
end


function cartesianiter(dims)
    @task cartesianmap(((x...)->produce(x)), dims)
end

function cartesianiter(dims::Int...)
    cartesianiter(dims)
end



end # module
