#################################################################
# Boolean datatype declaration
immutable _Boolean
  _Boolean(_::Dict{Symbol,Any})= begin
    b::String=haskey(_,:finalBrief) ?  _[:finalBrief] : haskey(_,:Brief) ? _[:Brief] : "Boolean Value"
    d::Bool=haskey(_,:finalDefault) ?  _[:finalDefault] : haskey(_,:Default) ? bool(_[:Default]) : false
    new(b,d)
  end
  brief::String
  default::Bool
end
#################################################################
# Integer datatype declaration
immutable _Integer
  _Integer(_::Dict{Symbol,Any}) = begin
    b::String=haskey(_,:finalBrief) ?  _[:finalBrief] : haskey(_,:Brief) ? _[:Brief] : "Integer Number"
    d::Int=haskey(_,:finalDefault) ?  _[:finalDefault] : haskey(_,:Default) ? integer(_[:Default]) : 0
    l::Int=haskey(_,:finalLower) ?  _[:finalLower] : haskey(_,:Lower) ? integer(_[:Lower]) : typemin(Int)
    u::Int=haskey(_,:finalUpper) ?  _[:finalUpper] : haskey(_,:Upper) ? integer(_[:Upper]) : typemax(Int)
    new(b,d,l,u)
  end
  brief::String
  default::Int
  lower::Int
  upper::Int
end
#################################################################
# Switcher datatype declaration
immutable _Switcher
  _Switcher(_::Dict{Symbol,Any}) = begin
    if !haskey(_,:finalValid) && !haskey(_,:Valid)
      return nothing,"in Switcher: valid values not found"
    end
    if !haskey(_,:finalDefault) && !haskey(_,:Default)
      return nothing,"in Switcher: default value not found"
    end
    b::String=haskey(_,:finalBrief) ?  _[:finalBrief] : (haskey(_,:Brief) ? _[:Brief] : "Switcher")
    d=haskey(_,:finalDefault) ?  _[:finalDefault] : _[:Default]
    e::Set=haskey(_,:finalValid) ?  Set(_[:finalValid]...) : (haskey(_,:Valid) ? Set(_[:Valid]...) : Set())
    if !isa(e,Set)
      return nothing #"in Switcher: invalid values, must be a set"
    end
    if !in(d,e)
      return nothing #"in Switcher: invalid default value"
    end
    new(b,d,e)
  end
  brief::String
  default::Any
  valid::Set
end
#################################################################
# Real datatype declaration
immutable _Real
  _Real(_::Dict{Symbol,Any}) = begin
    b::String=haskey(_,:finalBrief) ?  _[:finalBrief] : haskey(_,:Brief) ? _[:Brief] : "Real Number"
    d::Float64=haskey(_,:finalDefault) ?  _[:finalDefault] : haskey(_,:Default) ? float(_[:Default]) : 0.0
    l::Float64=haskey(_,:finalLower) ?  _[:finalLower] : haskey(_,:Lower) ? float(_[:Lower]) : typemin(Float64)
    u::Float64=haskey(_,:finalUpper) ?  _[:finalUpper] : haskey(_,:Upper) ? float(_[:Upper]) : typemax(Float64)
    un::String=haskey(_,:finalUnit) ?  _[:finalUnit] : haskey(_,:Unit) ? _[:Unit] : ""
    new(b,d,l,u,un)
  end
  brief::String
  default::Float64
  lower::Float64
  upper::Float64
  unit::String
end
#################################################################
# Plugin datatype declaration
immutable DanaPlugin
  DanaPlugin(_::Dict{Symbol,Any}) = begin
    b::String=haskey(_,:finalBrief) ?  _[:finalBrief] : haskey(_,:Brief) ? _[:Brief] : "Plugin"
    new(b)
  end
  brief::String
end

