module strict

Base.getindex(x::Number) = throw(MethodError(Base.getindex,(Number,)))
Base.getindex(x::Number, i::Integer) = throw(MethodError(Base.getindex,(Number,Integer)))
Base.getindex(x::Number, I::Integer...) = throw(MethodError(Base.getindex(x::Number, I::Integer...)))
Base.getindex(x::Number, I::Real...) = throw(MethodError(Base.getindex(x::Number, I::Real...)))

end
