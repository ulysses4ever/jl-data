using Base.Meta

export @commutative

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