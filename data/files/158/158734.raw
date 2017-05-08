


module RBCmod

import Base.show

export Model, mylog

mylog(x::Float64) = ccall((:log, "libm"), Float64, (Float64,), x)
include("model.jl")

end