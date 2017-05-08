module CountMin

export CountMinSketch,
        push!,
        pop!,
        add!,
        haskey,
        getindex,
        setindex!,
        collisionrate,
        write,
        read!,
        append!,
        unappend!,
        eltype,
        size


import Base: read!, write, push!, pop!, getindex, setindex!, eltype, size
import HDF5: h5open


# Our CountMinSketch implementation
type CountMinSketch{T<:Unsigned}
    # Num tables (to save geting this from shape(sketch)
    tables::Unsigned
    # Number of bins per table
    tablesize::Unsigned
    # we store bins in a Matrix
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
        cms.sketch[i, offset] += count
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

function setindex!(cms::CountMinSketch, item, value::Integer)
    min = 0
    for i in 1:cms.tables
        offset = item % cms.tablesize + 1
        val = cms.sketch[i, offset]
        if val > min
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

function write(filename::AbstractString, cms::CountMinSketch)
    h5open(filename, 'w') do h5f
        h5f["sketch", "blosc", 9] = cms.sketch
    end
end

function read!(filename::AbstractString, cms::CountMinSketch)
    h5open(filename, 'r') do h5f
        cms.sketch = h5f["sketch"]
        cms.tables, cms.tablesize = shape(cms.sketch)
    end
end

function read(filename)
    cms = CountMinSketch()
    read!(filename, cms)
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
