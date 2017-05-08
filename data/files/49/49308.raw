module CountMin

export CountMinSketch,
       push!,
       pop!,
       add!,
       haskey,
       getindex,
       collisionrate,
       readcms,
       readcms!,
       writecms,
       append!,
       unappend!,
       eltype,
       size


import Base: read!,
             write,
             push!,
             pop!,
             getindex,
             eltype,
             size
import HDF5: h5open


# Our CountMinSketch implementation
type CountMinSketch{T<:Unsigned}
    # tables and tablesize are purely for convenience, and are just
    # shape(sketch)

    # Num tables (to save geting this from shape(sketch)
    tables::Unsigned
    # Number of bins per table
    tablesize::Unsigned

    # We store the sketch as a Matrix
    sketch::Matrix{T}

    function CountMinSketch(tables::Integer, tablesize::Integer)
        if !(1 <= tables <= 20)
            error("Must have between 1 and 20 tables")
        end
        tablesize > 1 || error("Table size must be greater than 1")
        sketch = zeros(T, tables, tablesize)
        return new(tables, tablesize, sketch)
    end

    function CountMinSketch()
        return new(0, 0, zeros(T,0,0))
    end
end

function add!(cms::CountMinSketch, item, count)
    for i in 1:cms.tables
        offset = hash(item, hash(i)) % cms.tablesize + 1
        try
            cms.sketch[i, offset] += count
        catch InexactError
            # clamp overflow to typemin/typemax(eltype(sketch))
            newval = count > 0 ? typemax(eltype(cms)) : typemin(eltype(cms))
            cms.sketch[i, offset] = newval
        end
    end
end

function getindex(cms::CountMinSketch, item)
    min = Inf
    for i in 1:cms.tables
        offset = hash(item, hash(i)) % cms.tablesize + 1
        val = cms.sketch[i, offset]
        if val < min
            min = val
        end
    end
    return min
end

function push!(cms::CountMinSketch, item)
    add!(cms, item, 1)
end

function pop!(cms::CountMinSketch, item)
    add!(cms, item, -1)
end

function haskey(cms::CountMinSketch, item)
    return cms[item] > 0
end

function eltype(cms::CountMinSketch)
    return eltype(cms.sketch)
end

function size(cms::CountMinSketch)
    return size(cms.sketch)
end

function collisionrate(cms::CountMinSketch)
    # Expectected collision rate, modified from Khmer
    occupancy = sum(cms.sketch .> 0, 2)
    # The total FPR is the product of all rates, as we assume each is truly
    # independent
    rate = prod(float(occupancy) / float(cms.tablesize))
    return rate
end

function writecms(filename::AbstractString, cms::CountMinSketch)
    h5open(filename, "w") do h5f
        chunksize = (1, min(2^20, cms.tablesize))
        h5f["sketch", "blosc", 9, "chunk", chunksize] = cms.sketch
    end
end

function readcms!(filename::AbstractString, cms::CountMinSketch)
end

function readcms(filename::AbstractString)
    cms = 0
    h5open(filename, "r") do h5f
        sketch = h5f["sketch"]
        nt, ts = size(sketch)
        cms = CountMinSketch{eltype(sketch)}(nt, ts)
        cms.sketch = read(sketch)
        cms.tables, cms.tablesize = nt, ts
    end
    return cms
end

function append!(a::CountMinSketch, b::CountMinSketch)
    if shape(a) != shape(b)
        error("CountMinSketches must be of the exact same sketch dimensions")
    end
    a.sketch += b.sketch
end

function unappend!(a::CountMinSketch, b::CountMinSketch)
    if shape(a) != shape(b)
        error("CountMinSketches must be of the exact same sketch dimensions")
    end
    a.sketch -= b.sketch
end

end # module CountMinSketch
