module Cav

export do_nothing, ref, deref, set!, swap!

do_nothing() = nothing

type Ref{T}
  value::T
end

ref(x) = Ref(x)
deref(x::Ref) = x.value
set!{T}(x::Ref{T}, v::T) = (x.value = v; x)
swap!(x::Ref, f::Function) = (x.value = f(x.value); x)

include("functional.jl")
include("algo.jl")

end
