
# Plain arrays can be treated as images. Other types will have
# metadata associated, make yours a child of one of the following:
abstract AbstractImage{T,N} <: AbstractArray{T,N}         # image with metadata
abstract AbstractImageDirect{T,N} <: AbstractImage{T,N}   # each pixel has own value/color
abstract AbstractImageIndexed{T,N} <: AbstractImage{T,N}  # indexed images (i.e., lookup table)

# Direct image (e.g., grayscale, RGB)
type Image{T,N,A<:AbstractArray} <: AbstractImageDirect{T,N}
    data::A
    properties::Dict{ASCIIString,Any}
end

Image(data::AbstractArray, props::Dict) = Image{eltype(data),ndims(data),typeof(data)}(data,props)
Image(data::AbstractArray; kwargs...) = Image(data, kwargs2dict(kwar

