module RW

export update, update!, norm2, to_plot_str

import Base.zero, Base.zeros, Base.abs, Base.abs2, Base.norm
import Base.Random.rand, Base.Random.rand!

abstract Point{T<:Real}

include("point1d.jl")
include("point2d.jl")
include("point3d.jl")

function zeros{P<:Point}(::Type{P},dims::Dims)
  ar = Array(P,dims)
  for i in 1:length(ar)
    ar[i] = zero(P)
  end
  return ar
end
zeros{P<:Point}(::Type{P},dims::Int...) = zeros(P,dims)

function rand!{P<:Point}(ar::Array{P})
  for i in 1:length(ar)
    ar[i] = rand(P)
  end
  return ar
end

rand{P<:Point}(::Type{P}, dims::Dims) = rand!(Array(P,dims))
rand{P<:Point}(::Type{P}, dims::Int...) = rand(P,dims)

update{P<:Point}(p::P) = update!(deepcopy(p))
update{P<:Point}(ps::Array{P}) = map(update,ps)
update!{P<:Point}(ps::Array{P}) = map!(update!,ps)

to_plot_str(x) = "$x"

end # module RW
