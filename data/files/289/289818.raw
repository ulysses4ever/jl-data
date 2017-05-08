abstract Excr3C

type numC <: Excr3C
  n::Number
end

type boolC <: Excr3C
  b::Bool
end

type idC <: Excr3C
  name
end

type ifC <: Excr3C
  ts::Excr3C
  th::Excr3C
  el::Excr3C
end

type opC <: Excr3C
  op::String
  l::Excr3C
  r::Excr3C
end

abstract Value

type numV <: Value
  n::Number
end

type boolV <: Value
  b::Bool
end

type cloV <: Value
  n::Number
end

function validOp (binop)
  if binop == "+" || binop == "-" || binop == "/" || binop == "*" || binop == "<=" || binop == "eq?"
    return true
  end
  return false
end

function interp (program::Excr3C)
  if typeof(program) == numC
    return numV(program.n)
  elseif typeof(program) == boolC
    return boolV(program.b)
  elseif typeof(program) == ifC
    if (interp(program.ts)).b == true
      return interp(program.th)
    else
      return interp(program.el)
    end
  end
end

function my_serialize (v::Value)
  if typeof(v) == cloV
    return "#<procedure>"
  elseif typeof(v) == boolV
    return string(v.b)
  elseif typeof(v) == numV
    return string(v.n)
  end
end

function runTests ()
  #test valid binops
  @assert(validOp("+") == true)
  @assert(validOp("-") == true)
  @assert(validOp("*") == true)
  @assert(validOp("/") == true)
  @assert(validOp("eq?") == true)
  @assert(validOp("<=") == true)

  #test some false binops
  @assert(validOp("bad") == false)
  @assert(validOp(5) == false)
  @assert(validOp(true) == false)

  #interp tests
  @assert(interp(numC (5)).n == (numV (5)).n)
  @assert(interp(boolC (true)).b == (boolV (true)).b)
  @assert(interp(ifC(boolC (true), numC (5), numC (6))).n == (numV (5)).n)



  #serialize tests
  @assert(my_serialize(numV (5)) == "5")
  @assert(my_serialize(boolV (true)) == "true")
  @assert(my_serialize(boolV (false)) == "false")
  @assert(my_serialize(cloV (5)) == "#<procedure>")

  #test change for git
 #another test
end

runTests()
