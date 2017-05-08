module strict


# This file is a part of Julia. License is MIT: http://julialang.org/license

## generic operations on numbers ##

Base.size(x::Number,d) = convert(Int,d)<1 ? throw(BoundsError()) : 0
Base.eltype(x::Number) = throw(MethodError(Base.eltype,(Number,)))
Base.length(x::Number) = 0
Base.endof(x::Number) = throw(MethodError(Base.endof,(Number,)))
Base.getindex(x::Number) = throw(MethodError(Base.getindex,(Number,)))
Base.getindex(x::Number, i::Integer) = throw(MethodError(Base.getindex,(Number,Integer)))
Base.getindex(x::Number, I::Integer...) = throw(MethodError(Base.getindex,(Number, Integer...)))
Base.getindex(x::Number, I::Real...) = throw(MethodError(Base.getindex,(Number, Real...)))
Base.unsafe_getindex(x::Real, i::Real) = throw(MethodError(Base.unsafe_getindex,(Real, Real)))
Base.first(x::Number) = throw(MethodError(Base.first,(Number,)))
Base.last(x::Number) = throw(MethodError(Base.last,(Number,)))

Base.conj(x::Real) = throw(MethodError(Base.conj,(Real,)))
Base.transpose(x::Number) = throw(MethodError(Base.transpose,(Number,)))
Base.ctranspose(x::Number) = throw(MethodError(Base.ctranspose,(Number,)))

Base.start(x::Number) = throw(MethodError(Base.start,(Number,)))
Base.next(x::Number, state) = throw(MethodError(Base.next,(Number,ANY)))
Base.done(x::Number, state) = throw(MethodError(Base.done,(Number,ANY)))
Base.in(x::Number, y::Number) = throw(MethodError(Base.in,(Number,Number)))

Base.map(f, x::Number, ys::Number...) = throw(MethodError(Base.map,(ANY,Number,Number...)))

end
