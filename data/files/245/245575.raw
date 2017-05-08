module RoundingIndexArrays

import Base: size, linearindexing, getindex, setindex!, show, writemime

export RoundingIndexArray

type RoundingIndexArray{T,N,A<:AbstractArray} <: AbstractArray{T,N}
    data::A
end
RoundingIndexArray{T,N}(data::AbstractArray{T,N}) = RoundingIndexArray{T,N,typeof(data)}(data)
size(ra::RoundingIndexArray) = size(ra.data)
Base.linearindexing(::RoundingIndexArray) = Base.LinearFast()
getindex{T<:Real}(ra::RoundingIndexArray,ix::T) = ra.data[Int64(round(ix))]
getindex(ra::RoundingIndexArray,ix) = [ra[i]::typeof(ra[1]) for i in ix]
setindex!{T<:Real}(ra::RoundingIndexArray, v, ix::T) = (ra.data[Int64(round(ix))] = v)

#=...............
Display Functions
...............=#
show(io::Base.IO, ra::RoundingIndexArray) = show(io::Base.IO, ra.data)
writemime(io::Base.IO, ::MIME"text/plain", ra::RoundingIndexArray) = show(io, ra.data)

end
