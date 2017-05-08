# this file is a part of Dana Virtula Laboratury project
# author:Reza Afzalan
# email:RAfzalan@Gmail.com
# 
#################################################################
# this module declares builtin types for Dana virtual laboratory
# this types must comply requiremnts of EML data model 
#################################################################


#################################################################
#         here is list of EML builtin data types
#
# Boolean Type for logical parameters or variables, with attributes:
# Brief textual brief description
# Default default value for parameters and initial guess for variables
#
#
# Integer Type for int variables or parameters, with attributes:
# Brief: textual brief description
# Default: default value for parameters and initial guess for variables
# Lower: lower limit
# Upper: upper limit
#
#
# Plugin Object for loading third party pieces of software providing special calculation
# services, see chapter 5.
#
# Real Type for continuous variables or parameters, with attributes:
# Brief: textual brief description
# Default: default value for parameters and initial guess for variables
# Lower: lower limit
# Upper: upper limit
# Unit: textual unit of measurement
#
#
# Switcher Type for textual parameters, with attributes:
# Brief textual brief description
# Valid the valid values for the switcher
# Default default value for the switcher
#
#################################################################
module DanaTypes
  include ("immutables.jl")
  include ("danabase.jl")
  export get,getbracket,getdefault
  export setfield!,setEquationFlow
  export isunknown,isequal
  export drive!
  export outers

  setEquationFlow(danamodel::DanaModel)=return nothing #Base method must overloaded  
  

######################### Get ##########################
  get(x::Float64)=x
  function get(x::Dana)
    # unset equals unknown, set to unknown equals a constant default value
    return x.unset ? NaN : (isunknown(x.value) ?  x.immute.default : x.value)
  end
  function get(x::DanaSwitcher)
    return x.unset ? x.immute.default : x.value
  end
  function getbracket(danamodel::DanaModel,fieldname::String)
    danavar = getfield(danamodel,symbol(fieldname))
    return [danavar.immute.lower,danavar.immute.upper]
  end
  function getdefault(danamodel::DanaModel,fieldname::String)
    danavar = getfield(danamodel,symbol(fieldname))
    return danavar.immute.default
  end
######################## Set ###########################
  function set(x::Dana)
    x.unset=false
  end
  function set(x::DanaBoolean,y::Bool)
      x.value=y
      x.unset=false
  end
  function set(x::DanaSwitcher,y::Any)
    if !in(y,x.immute.valid)
      return (nothing,"in set: invalid Switcher value " * string(y))
    else
      x.value=y
      x.unset=false
      return y
    end
  end
  function set(x::DanaRealParametric,y::Float64)
    isconstant(x) && return (nothing,"cant reset constant") 
    if isunknown(y)
      x.unset=true #unset equals unknown
    else
      if !(y>=x.immute.lower && y<=x.immute.upper)
        return (nothing,"real value is out of bounds")
      else
        x.value=y
        x.unset=false
      end
    end
  end
  function set(x::DanaIntegerParametric,y::Int)
    if !(y>=x.immute.lower && y<=x.immute.upper)
      return (nothing,"integer value is out of bounds")
    else
      x.value=y
      x.unset=false
    end
  end
  function setfield!(danamodel::DanaModel,sy::Symbol,value)
    isa(danamodel.(sy),Dana) ? set(danamodel.(sy),value) : danamodel.(sy)=value
  end

######################## Check #########
  function isequal(x::DanaSwitcherParametric,y::Any)
    return x.unset ? (nothing,"value is unset, use immute.default") : x.value==y
  end
  isunknown(var::Float64)=isnan(var)
  isunknown(var::DanaRealParametric)=isnan(var.value)
  isconstant(var::DanaRealParametric)=(isnan(var.value)&&(!var.unset))

######################## Drive childs from Dana datatypes
  function drive!(base::Dict{Symbol,Any},child::Dict{Symbol,Any})
    f(k,v)=!(haskey(base,k) && beginswith(string(k),"final"))
    merge!(base,filter(f,child))
  end
######################## TODO ##############################
  module outers
    PP=0
    NComp=0
  end

end

include ("types.jl")
