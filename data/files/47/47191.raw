module Cav

export donothing, ref

donothing() = nothing

type Ref{T}
  value::T
end

ref(x) = Ref(x)
deref{T}(x::Ref{T}) = x.value
set!{T}(x::Ref{T}, v::T) = (x.value = v; x)
swap!{T}(x::Ref{T}, f::Function) = (x.value = f(x.value); x)

include("functional.jl")

end
