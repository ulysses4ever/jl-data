include(joinpath("..","src","juliaspec.jl"))

function checkAssertionError(e, reason)
  if isa(e, AssertionError)
    if e.reason != reason
      throw(Failure(string("Error message wrong, got [", e.reason,"]")))
    end   
  else
    throw(e)
  end
end

include("describe_test.jl")
include("equality_test.jl")
