module Kwesi
#need to define new method of * to handle single element arrays of Real
function *(x::Array{Real}, y::Array{Real})
  x2 = (x[1])::Real
  y2 = (y[1])::Real
  x2 * y2
end
#base type of node
abstract BaseNode
#VarNode defines variables that simply return their state value
type VarNode <: BaseNode
  name::String
  state::Array{Real, 1}
  function VarNode(name="VarNode", state=[0])
    this = new()
    this.name = name
    this.state = state
    this
  end
end
#OpsNodes return the result from their operation (a defined function)
type OpsNode <: BaseNode
  operation::Function
  state::Array{Real, 1}
  inputs::Array{BaseNode}
  function OpsNode{T<:BaseNode}(operation, state, inputs::Array{T, 1})
    this = new()
    this.operation = operation
    this.state = state
    this.inputs = inputs
    this
  end
end


function runNode(node::VarNode)
  return node.state
end

function runNode(node::OpsNode)
  inputs = [runNode(input) for input in node.inputs]
  state::Array{Real, 1}
  state = Real[]
  result = apply(node.operation, inputs)
  if (typeof(result) <: Array)
    state = result
  elseif (typeof(result) <: Real)
    push!(state, result)
  end
  node.state = state
end
end