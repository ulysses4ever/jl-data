# TODO: add check to ensure minimum seg value is 1
inorder(x, y) = (min(x, y), max(x, y))
interleave(x, y) = map((x, y) -> (x, y), x, y)

function collapse{T}(x::Array{T, 3})
    # Collapse a 3 dimensional array to a 2 dimensional array of vectors
    nrows, ncols, depth = size(x)
    result = [T[] for i=1:nrows, j=1:ncols]
    for k = 1:depth
        for j = 1:ncols
            for i = 1:nrows
                push!(result[i, j], x[i, j, k])
            end
        end
    end

    result
end

function neighborpairs{T}(spmap::Matrix{T})
    neighbordict = Dict{Int,Set{Int}}()
    for j = 1:size(spmap, 2)
        for i = 1:size(spmap, 1)
            if j < size(spmap, 2)
                left = spmap[i,j]
                right = spmap[i,j+1]
                if left != right
                    minind = min(left, right)
                    maxind = max(left, right)

                    if !haskey(neighbordict, minind)
                        neighbordict[minind] = Set{Int}()
                    end

                    push!(neighbordict[minind], maxind)
                end
            end
            if i < size(spmap, 1)
                top = spmap[i,j]
                bottom = spmap[i+1,j]
                if top != bottom
                    minind = min(top, bottom)
                    maxind = max(top, bottom)

                    if !haskey(neighbordict, minind)
                        neighbordict[minind] = Set{Int}()
                    end

                    push!(neighbordict[minind], maxind)
                end
            end
        end
    end

    rval = NTuple{2,Int}[]
    for key in sort(collect(keys(neighbordict)))
        for val in sort(collect(neighbordict[key]))
            push!(rval, (key, val))
        end
    end
    rval
end
    
function spdist{T<:Integer}(segmap::Matrix{T}, sp1indices::Vector{Int}, sp2indices::Vector{Int})
    # Return the distance between the pixels in sp1indices and sp2indices, as defined by segmap.
    sp1seg = segmap[sp1indices]
    sp2seg = segmap[sp2indices]

    maxsegval = maximum([maximum(sp1seg), maximum(sp2seg)])

    _, sp1segfreq = hist(sp1seg, 0:maxsegval)
    _, sp2segfreq = hist(sp2seg, 0:maxsegval)

    acc = 0
    for x in unique(sp1seg)
        acc += sp1segfreq[x] * sp2segfreq[x]
    end

    return 1 - (acc / (length(sp1indices) * length(sp2indices)))
end

function spdist{T<:Integer}(spmap::Matrix{T}, segmap::Matrix{T})
    spindices = Dict{Int, Vector{Int}}()
    for (index, val) in enumerate(spmap)
        if !haskey(spindices, val)
            spindices[val] = [index]
        else
            push!(spindices[val], index)
        end
    end

    ((T, T) => Float64)[(i, j) => spdist(segmap, spindices[i], spindices[j]) for (i, j) in neighborpairs(spmap)]
end

function seg2boundary{T<:Integer}(seg::Matrix{T}; format=:imagesize)
    # Ported by Jake Snell <jsnell@cs.toronto.edu> from MATLAB code due to Pablo Arbelaez <arbelaez@eecs.berkeley.edu>
    (tx, ty) = size(seg)

    boundary = convert(BitArray, zeros(2*tx+1, 2*ty+1))
    hedges = hcat(!(seg[:, 1:end-1] .== seg[:, 2:end]), zeros(Bool, (tx,1)))
    vedges = vcat(!(seg[1:end-1, :] .== seg[2:end, :]), zeros(Bool, (1,ty)))

    boundary[3:2:end, 2:2:end] = vedges
    boundary[2:2:end, 3:2:end] = hedges
    boundary[3:2:end-1, 3:2:end-1] = hedges[1:end-1, 1:end-1] | hedges[2:end, 1:end-1] | 
                                     vedges[1:end-1, 1:end-1] | vedges[1:end-1, 2:end]

    boundary[1, :] = boundary[2, :]
    boundary[:, 1] = boundary[:, 2]
    boundary[end, :] = boundary[end-1, :]
    boundary[:, end] = boundary[:, end-1]

    if format == :imagesize
        boundary = boundary[3:2:end, 3:2:end]
    end
    boundary
end

function seg2boundaryindex{T<:Integer}(seg::Matrix{T})
    (tx, ty) = size(seg)

    hedges = hcat(interleave(seg[:, 1:end-1], seg[:, 2:end]), fill((0,0), (tx, 1)))
    vedges = vcat(interleave(seg[1:end-1, :], seg[2:end, :]), fill((0,0), (1, ty)))

    ul = collapse(cat(3, hedges[1:end-1, 1:end-1], hedges[2:end, 1:end-1],
    vedges[1:end-1, 1:end-1], vedges[1:end-1, 2:end]))
    ur = collapse(reshape(vedges[1:end-1, end], (tx-1, 1, 1)))
    bl = collapse(reshape(hedges[end, 1:end-1], (1, ty-1, 1)))
    br = collapse(cat(3, hedges[end, end], vedges[end, end]))

    unfiltered = [ul ur; bl br]

    Vector{(Int, Int)}[unique(map(ys -> inorder(ys[1], ys[2]), filter(zs -> zs[1] != zs[2], unfiltered[i, j]))) for i = 1:tx, j = 1:ty]
end
