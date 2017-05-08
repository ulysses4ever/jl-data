module RW

export update, update!, norm2, to_plot_str

import Base.zero, Base.zeros, Base.abs, Base.abs2, Base.norm
import Base.Random.rand, Base.Random.rand!

abstract Point{T<:FloatingPoint}

include("point1d.jl")
include("point2d.jl")
include("point3d.jl")

zero(p::Point) = zero(typeof(p))

function zeros{P<:Point}(::Type{P},dims::Dims)
  arr = Array(P,dims)
  for i in 1:length(arr)
    arr[i] = zero(P)
  end
  return arr
end
zeros{P<:Point}(::Type{P},dims::Int...) = zeros(P,dims)

function rand!{P<:Point}(arr::Array{P})
  for i in 1:length(arr)
    arr[i] = rand(P)
  end
  return arr
end

rand{P<:Point}(::Type{P}, dims::Dims) = rand!(Array(P,dims))
rand{P<:Point}(::Type{P}, dims::Int...) = rand(P,dims)

abs(p::Point) = sqrt(abs2(p))
norm(p::Point) = sqrt(abs2(p))
norm2(p::Point) = abs2(p)

update(p::Point) = update!(deepcopy(p))
update{P<:Point}(ps::Array{P}) = map(update,ps)
update!{P<:Point}(ps::Array{P}) = map!(update!,ps)

to_plot_str(x) = "$x"

end # module RW
