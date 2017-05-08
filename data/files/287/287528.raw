module Segplot

using Seglib
using Color
using PyPlot

function boundaryplot(x::Vector{BitMatrix})
    # Simultaneously plots a vector of boundary matrices
    fig = figure()
    for i = 1:length(x)
        subfig = subplot(1, length(x), i)
        imshow(x[i], cmap="Greys", vmin=0, vmax=1, interpolation="nearest")
        subfig[:axes][:get_xaxis]()[:set_visible](false)
        subfig[:axes][:get_yaxis]()[:set_visible](false)
    end
    fig 
end

boundaryplot(x::BitMatrix) = boundaryplot(typeof(x)[x])

function implot{T<:Real}(x::Union(Vector{Matrix{T}}, Vector{Array{T,3}}))
    # Simultaneously plots a vector of RGB images
    fig = figure()
    for i = 1:length(x)
        subplot(1, length(x), i)
        imsubplot(x[i])
        axis("off")
    end
    fig
end

implot{T<:Real}(x::Union(Matrix{T}, Array{T,3})) = implot(typeof(x)[x])

function imsubplot{T<:Real}(x::Matrix{T})
    imshow(x, vmin=0, vmax=1, interpolation="none")
    gray()
end

imsubplot{T<:Real}(x::Array{T,3}) = imshow(x, vmin=0, vmax=1, interpolation="none")

function segplot{T<:Integer}(segs::Vector{Matrix{T}})
    # Simulataneously plots segmentations with distinguishable colors
    implot(map(applycolor, segs))
end

segplot{T<:Integer}(seg::Matrix{T}) = segplot(typeof(seg)[seg])

function applycolor{T}(x::Matrix{T}, cmap::Vector{Vector{Uint8}})
    (nrows, ncols) = size(x)
    result = Array(Uint8, (nrows, ncols, 3))
    for j = 1:ncols
        for i = 1:nrows
            result[i,j,:] = cmap[x[i,j]]
        end
    end
    result
end

applycolor{T}(x::Matrix{T}) = applycolor(x, distinguishable_cmap(maximum(x)))

function distinguishable_cmap{T<:Integer}(n::T)
    # Returns a vector of n distinguishable RGB values
    map(x->hex2bytes(hex(x)), distinguishable_colors(n))
end

function highlight(img::Array{Float64, 3}, mask::BitMatrix; border::Bool=true)
    @assert size(img)[1:2] == size(mask)

    # yellow
    alphaimg = cat(3, fill(0.5, size(mask)),
                      fill(0.5, size(mask)),
                      zeros(size(mask))) .* mask

    highlightedimg = img .+ alphaimg
    highlightedimg[highlightedimg .> 1.0] = 1.0

    if border
        boundarymask = seg2boundary(convert(Matrix{Int}, mask))
        for j = 1:size(boundarymask, 2)
            for i = 1:size(boundarymask, 1)
                if boundarymask[i, j]
                    highlightedimg[i, j, :] = [1.0, 0.0, 0.0]
                end
            end
        end
    end

    highlightedimg 
end

export
    boundaryplot,
    implot,
    segplot,
    highlight

end # module Segplot
