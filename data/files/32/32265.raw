using Base.Meta

export emit

function emit(arg::ParsedArgument)
  local out::Expr = Expr(:(::), arg.name, arg.typ)
  if arg.varargs
    out = Expr(:(...), out)
  end
  if isdefined(arg, :default)
    out = Expr(:kw, out, arg.default)
  end
  return out
end

emit(args::Vector{ParsedArgument}) = map(emit, args)

function emit_args(func::ParsedFunction)
  if isdefined(func, :kwargs)
    return [Expr(:parameters, emit(func.kwargs)...), emit(func.args)...]
  else
    return emit(func.args)
  end
end

make_quotenode(s::Symbol) = eval(quot(quot(s)))

function emit_name(namespace::Vector{Symbol}, name::Symbol)
  if length(namespace)>0
    return Expr(:(.), emit_name(namespace[1:end-1], namespace[end]), make_quotenode(name))
  else
    return name
  end
end

function emit_name(func::ParsedFunction)
  if !isdefined(func, :name)
    return []
  elseif isdefined(func, :types)
    if isdefined(func, :namespace)
      return [Expr(:curly, emit_name(func.namespace, func.name), func.types...)]
    else
      return [Expr(:curly, func.name, func.types...)]
    end
  elseif isdefined(func, :namespace)
    return [emit_name(func.namespace, func.name)]
  else
    return [func.name]
  end
end

function emit(func::ParsedFunction)
  const head = isdefined(func, :name) ? :call : :tuple # :call for a method else :tuple
  return Expr(:function, Expr(head, emit_name(func)..., emit_args(func)...), func.body)
end

macro commutative(ex::Expr)
  # Parse the function
  pfunc = ParsedFunction(ex)

  if (!isdefined(pfunc, :name) ||
      length(pfunc.args) != 2 ||
      pfunc.args[1].varargs || pfunc.args[2].varargs ||
      isdefined(pfunc.args[1], :default) || isdefined(pfunc.args[2], :default) ||
      (isdefined(pfunc, :kwargs) && length(pfunc.kwargs) != 0))
    error("Expected a method of 2 simple arguments only")
  end

  if pfunc.args[1].typ == pfunc.args[2].typ
    error("Arguments must be of different types")
  end

  # commutative so we can just swap the arguments
  reverse!(pfunc.args)

  if pfunc.args[1].typ == :Any || pfunc.args[2].typ == :Any
    # If one of the arguments is nothing we'll get warning unless we
    # define a method with symetric types first
    pfunc2 = deepcopy(pfunc)
    if pfunc2.args[1].typ == :Any
      pfunc2.args[1].typ = pfunc2.args[2].typ
    else
      pfunc2.args[2].typ = pfunc2.args[1].typ
    end
    # produce three forms of the method
    return esc(quote
      $(emit(pfunc2))
      $ex
      $(emit(pfunc))
    end)
  else
    # produce two forms of the method
    return esc(quote
      $ex
      $(emit(pfunc))
    end)
  end
end