
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
# Indexed image (colormap)
type ImageCmap{T<:Color,N,A<:AbstractArray} <: AbstractImageIndexed{T,N}
    data::A
    cmap::Vector{T}
    properties::Dict{ASCIIString,Any}
end
ImageCmap(data::AbstractArray, cmap::AbstractVector, props::Dict) = ImageCmap{eltype(cmap),ndims(data),typeof(data)}(data, cmap, props)
ImageCmap(data::AbstractArray, cmap::AbstractVector; kwargs...) = ImageCmap(data, cmap, kwargs2dict(kwargs))

Image(data::AbstractArray, props::Dict) = Image{eltype(data),ndims(data),typeof(data)}(data,props)
Image(data::AbstractArray; kwargs...) = Image(data, kwargs2dict(kwargs))


Base.eltype{T}(img::AbstractImage{T}) = T

Base.size(img::AbstractImage) = size(img.data)
Base.size(img::AbstractImage, i::Integer) = size(img.data, i)
Base.size(img::AbstractImage, dimname::String) = size(img.data, dimindex(img, dimname))

Base.ndims(img::AbstractImage) = ndims(img.data)

Base.strides(img::AbstractImage) = strides(img.data)

Base.copy(img::Image) = Image(copy(img.data), deepcopy(img.properties))
Base.copy(img::ImageCmap) = ImageCmap(copy(img.data), copy(img.cmap), deepcopy(img.properties))

const emptyset = Set()
function showim(io::IO, img::AbstractImageDirect)
    IT = typeof(img)
    print(io, colorspace(img), " ", IT.name, " with:\n  data: ", summary(img.data), "\n  properties:")
    showdictlines(io, img.properties, get(img, "suppress", emptyset))
end
function showim(io::IO, img::AbstractImageIndexed)
    IT = typeof(img)
    print(io, colorspace(img), " ", IT.name, " with:\n  data: ", summary(img.data), "\n  cmap: ", summary(img.cmap), "\n  properties:")
    showdictlines(io, img.properties, get(img, "suppress", emptyset))
end
Base.show(io::IO, img::AbstractImageDirect) = showim(io, img)
Base.writemime(io::IO, ::MIME"text/plain", img::AbstractImageDirect) = showim(io, img)
Base.show(io::IO, img::AbstractImageIndexed) = showim(io, img)
Base.writemime(io::IO, ::MIME"text/plain", img::AbstractImageIndexed) = showim(io, img)
function showdictlines(io::IO, dict::Dict, suppress::Set)
    for (k, v) in dict
        if k == "suppress"
            continue
        end
        if !in(k, suppress)
            print(io, "\n    ", k, ": ")
            printdictval(io, v)
        else
            print(io, "\n    ", k, ": <suppressed>")
        end
    end
end
macro get(img, k, default)
    quote
        img, k = $(esc(img)), $(esc(k))
        local val
        if !isa(img, AbstractImage)
            val = $(esc(default))
        else
            index = Base.ht_keyindex(img.properties, k)
            val = (index > 0) ? img.properties.vals[index] : $(esc(default))
        end
        val
    end
end


colorspace{C<:Color}(img::AbstractMatrix{C}) = string(C.name.name)
colorspace{C<:Color}(img::AbstractArray{C,3}) = string(C.name.name)
colorspace{C<:Color}(img::AbstractImage{C}) = string(C.name.name)
colorspace{C<:Color,T}(img::AbstractArray{AbstractAlphaColorValue{C,T},2}) = (S = string(C.name.name); S == "Gray" ? "GrayAlpha" : string(S, "A"))
colorspace{C<:Color,T}(img::AbstractImage{AbstractAlphaColorValue{C,T}}) = (S = string(C.name.name); S == "Gray" ? "GrayAlpha" : string(S, "A"))
colorspace(img::AbstractMatrix{Bool}) = "Binary"
colorspace(img::AbstractArray{Bool}) = "Binary"
colorspace(img::AbstractArray{Bool,3}) = "Binary"
colorspace(img::AbstractMatrix{Uint32}) = "RGB24"
colorspace(img::AbstractMatrix) = "Gray"
colorspace{T}(img::AbstractArray{T,3}) = (size(img, defaultarraycolordim) == 3) ? "RGB" : error("Cannot infer colorspace of Array, use an AbstractImage type")
colorspace(img::AbstractImage{Bool}) = "Binary"
colorspace{T,N,A<:AbstractArray}(img::ImageCmap{T,N,A}) = string(T.name.name)
colorspace(img::AbstractImageIndexed) = @get img "colorspace" csinfer(eltype(img.cmap))
colorspace{T}(img::AbstractImageIndexed{T,2}) = @get img "colorspace" csinfer(eltype(img.cmap))
csinfer{C<:Color}(::Type{C}) = string(C)
csinfer(C) = "Unknown"
colorspace(img::AbstractImage) = get(img.properties, "colorspace", "Unknown")


properties(A::AbstractArray) = @compat Dict(
    "colorspace" => colorspace(A),
    "colordim" => colordim(A),
    "timedim" => timedim(A),
    "pixelspacing" => pixelspacing(A),
    "spatialorder" => spatialorder(A))
properties{C<:Color}(A::AbstractArray{C}) = @compat Dict(
    "timedim" => timedim(A),
    "pixelspacing" => pixelspacing(A),
    "spatialorder" => spatialorder(A))
properties(img::AbstractImage) = img.properties

Base.haskey(a::AbstractArray, k::String) = false
Base.haskey(img::AbstractImage, k::String) = haskey(img.properties, k)

Base.get(img::AbstractArray, k::String, default) = default
Base.get(img::AbstractImage, k::String, default) = get(img.properties, k, default)

printdictval(io::IO, v) = print(io, v)
function printdictval(io::IO, v::Vector)
    for i = 1:length(v)
        print(io, " ", v[i])
    end
end