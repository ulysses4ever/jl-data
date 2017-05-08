module Rewrite

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

type XMatch
  success::Bool
  subs::Dict{Symbol,Any}
  path::Vector{Int64}
  XMatch(success, subs, path) = new(success, subs,path)
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

# function xmatch_partial(p::Expr, e::Expr)
#   mh = xmatch(p.head, e.head)
#   if !mh.success
#     return mh
#   end
#   p = xsub(p, mh.subs)
#   mh = xmatch(p.args[1], e.args[1])
#   if !mh.success
#     return mh
#   end
#   p = xsub(p, mh.subs)

#   le = length(e.args)-1
#   lp = length(p.args)-1
#   if le < lp
#     return XMatch()
#   end
#   pargs = p.args[2:end]
#   for k=2:(2+lp-le)
#     ma = xmatch_args(pargs, sub(e.args, k:k+lp-1))
#     if ma.success
#       merge!(ma.subs, mh.subs)
#       push!(ma.path, k)
#       return ma
#     end
#   end
#   return XMatch()
# end


function xmatch(p::Symbol, e)
  ps = string(p)
  if endswith(ps, "_")
    if length(ps) == 1
      return XMatch(true)
    end
    return XMatch(true, [p=>e])
  end
  return XMatch(p==e)
end




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


function rewrite(rules, e, recursive=true)
  from = keys(rules)
  to = values(rules)
  for (fk,tk) = zip(from, to)
    xm = xmatch(fk, e)
    if xm.success
      if isa(tk, Function)
        return tk(;xm.subs...)
      end
      return xsub(tk, xm.subs)
    end
  end
  return e
end

function rewrite(rules, e::Expr, recursive=true)
  er = invoke(rewrite, (Any, Any, Any), rules, e, recursive)
  if er != e
    return er
  end
  if recursive
    rh = rewrite(rules, e.head)
    rargs = [rewrite(rules, arg, recursive=recursive) for  arg=e.args]
    re = Expr(rh)
    re.args = rargs
    return re
  end
  return e
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
