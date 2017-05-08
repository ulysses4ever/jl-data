module MyPoint

export Point, Point1D, Point2D, update, update!
import Base.zero, Base.zeros, Base.Random.rand, Base.Random.rand!

abstract Point{T<:Real}

*(a::Real, p::Point) = p*a
\(a::Real, p::Point) = p/a

function zeros{P<:Point}(::Type{P},dims::Dims)
  arr = Array(P,dims)
  for i in 1:length(arr)
    arr[i] = zero(P)
  end
  return arr
end
zeros{P<:Point}(::Type{P},dims::Integer...) = zeros(P,dims)

rand!{P<:Point}(arr::Array{P}) = map!(x->rand(P), arr)
rand{P<:Point}(:Type{P}, dims::Dims) = rand!(Array(P,dims))
rand{P<:Point}(:Type{P}, dims::Integer...) = rand!(Array(P,dims))

norm(p::Point) = norm2(p)

update(p::Point) = update!(deepcopy(p))
update{P<:Point}(ps::Array{P}) = map(update,ps)
update!{P<:Point}(ps::Array{P}) = map!(update,ps)

plotstr(x) = "$x"

include("mypoint1d.jl")
include("mypoint2d.jl")

end
