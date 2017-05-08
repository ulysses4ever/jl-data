module Points

import Base.zero, Base.zeros, Base.rand
import Base.+, Base.-, Base.*, Base./, Base.\
import Base.abs, Base.abs2

export Point, update, plot_str

abstract Point

zero(x :: Point) = zero(typeof(x))
zeros{P<:Point}(::Type{P}, n::Int) = [zero(P) for i in 1:n]
rand(x :: Point) = rand(typeof(x))

*(p :: Point, a :: Real) = a*p
\(a :: Real, p :: Point) = p/a

abs(p :: Point) = sqrt(abs2(p))

update(p :: Point) = p + rand(p)

include("Point1d.jl")
include("Point2d.jl")

end ## of module Points
