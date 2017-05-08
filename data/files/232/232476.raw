#################################################################
# container for immute data + value
# Q is value datatype and must be as immute default datatype
# R non builtIn datatype
export DanaBoolean,DanaInteger,DanaReal,DanaSwitcher,DanaPlugin,DanaError,AbsBulitIns
export DanaBooleanParametric,DanaIntegerParametric,DanaRealParametric,DanaSwitcherParametric
export DanaModel
type Dana{T,Q,R}
  function Dana()
    contains(string(R.name),"_constant") ? (unset=false) : (unset=true)
    _immute=is(R,AbsBulitIns) ? T(Dict{Symbol,Any}()) : T(R(Dict{Symbol,Any}()).value)
    typeof(_immute)==T ? new(_immute,_immute.default,unset) : _immute
  end
  function Dana(_::Dict{Symbol,Any})
    contains(string(R.name),"_constant") ? (unset=false) : (unset=true)
    _immute=is(R,AbsBulitIns) ? T(_) : T(R(_).value)
    typeof(_immute)==T ? new(_immute,_immute.default,unset) : _immute
  end
  immute::T
  value::Q
  unset::Bool
end
abstract DanaModel #abstract type for all models
abstract AbsBulitIns
typealias DanaError Tuple{Void,AbstractString}
typealias DanaBooleanParametric{R} Dana{_Boolean,Bool,R}
typealias DanaBoolean Dana{_Boolean,Bool,AbsBulitIns}
typealias DanaIntegerParametric{R} Dana{_Integer,Int,R}
typealias DanaInteger Dana{_Integer,Int,AbsBulitIns}
typealias DanaSwitcherParametric{R} Dana{_Switcher,Any,R}
typealias DanaSwitcher Dana{_Switcher,Any,AbsBulitIns}
typealias DanaRealParametric{R} Dana{_Real,Float64,R}
typealias DanaReal Dana{_Real,Float64,AbsBulitIns}
