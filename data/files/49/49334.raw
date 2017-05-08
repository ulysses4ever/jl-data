module CountMin

export CountMinSketch,
       push!,
       pop!,
       add!,
       haskey,
       getindex,
       collisionrate,
       readcms,
       writecms,
       eltype,
       size,
       show

import Base: read!,
             write,
             push!,
             pop!,
             getindex,
             eltype,
             size,
             show

import HDF5: h5open


"""
A Count-min Sketch

### Implementation Notes

Sketches are stored such that each table is contiguous, which in Julia means
that tables need to be columns. To ease transition between those using this
datastructure in Python or C, we preseve the (number of tables, table size)
way of referring to the sketch's size, and just reverse this internally.
"""
type CountMinSketch{T<:Unsigned}
    # tables and tablesize are purely for convenience, and are just
    # shape(sketch)

    # Num tables (to save getting this from shape(sketch)
    tables::UInt

    # Number of bins per table
    tablesize::UInt

    # We store the sketch as a Matrix
    sketch::Matrix{T}

    # Type min and max precomuted to avoid allocs
    tpmax::Int
    tpmin::Int

    seeds::Vector{UInt}

    """
    The constructor for `CountMinSketch`es

    Arguments
    ---------

    * `tables::Int`: The number of tables to create
    * `tablesize::Int`: The size of each table
    """
    function CountMinSketch(tables::Int, tablesize::Int)
        if !(1 <= tables <= 20)
            error("Must have between 1 and 20 tables")
        end
        tablesize > 1 || error("Table size must be greater than 1")
        sketch = zeros(T, tablesize, tables)
        seeds = map(hash, 1:tables)
        return new(tables, tablesize, sketch, typemax(T), typemin(T), seeds)
    end
end


"""
A trivial constructor for `CountMinSketch`es.

Creates a sketch with 4 tables of 1000 UInt8-typed bins.

WARNING: This trivial constructor instantiates a tiny `CountMinSketch`, which
         will be useless for anything but a simple test. Storing more than 10
         items  is not recommended.
"""
CountMinSketch() = CountMinSketch{UInt8}(4, 1000)


function show{T}(io::IO, cms::CountMinSketch{T})
    nt = cms.tables
    ts = cms.tablesize
    print("CountMinSketch with $nt tables of $ts `$T`s")
end


"""
Adds `count` `item`s to a CountMinSketch

This function will never allow the counts for an item to overflow or underflow.

Arguments
---------
* `cms`: A count-min sketch
* `item`: any hashable item
* `count::Integer`: a (potentially negative) number of `item`s to add.
"""
function add!(cms::CountMinSketch, item, count::Int)
    i::UInt = 0
    while (i+=1) <= cms.tables
        offset = (hash(item, cms.seeds[i]) % cms.tablesize) + 1
        try
            @inbounds cms.sketch[offset, i] += count
        catch
            # clamp overflow to typemin/typemax(eltype(sketch))
            @inbounds cms.sketch[offset, i] = count > 0 ? cms.tpmax : cms.tpmin
        end
    end
end


"""
Determine count of an item in a CountMinSketch.

NB: This function returns an estimate of the true count. This estimate is never
    lower than the true count, but has a very low probablity of being higher.

Arguments
---------
* `cms`: A count-min sketch
* `item`: any hashable item
"""
function getindex(cms::CountMinSketch, item)
    minval = cms.tpmax
    i::UInt = 0
    while (i+=1) <= cms.tables
        offset = (hash(item, cms.seeds[i]) % cms.tablesize) + 1
        @inbounds val = cms.sketch[offset, i]
        if val < minval
            minval = val
        end
    end
    return minval
end


"""
Add one `item` from a CountMinSketch

This function will never allow the counts for an item to overflow.

Arguments
---------
* `cms`: A count-min sketch
* `item`: any hashable item
"""
function push!(cms::CountMinSketch, item)
    add!(cms, item, 1)
end


"""
Remove one `item` from a CountMinSketch

This function will never allow the counts for an item to underflow.

Arguments
---------
* `cms`: A count-min sketch
* `item`: any hashable item
"""
function pop!(cms::CountMinSketch, item)
    add!(cms, item, -1)
end

"""
Test for presence of an item in a CountMinSketch.

NB: This function never returns a false negative, but has a very low probablity
    of returning a false positive due to collision.
"""
function haskey(cms::CountMinSketch, item)
    return cms[item] > 0
end


"""
Element type of a CountMinSketch
"""
function eltype(cms::CountMinSketch)
    return eltype(cms.sketch)
end


"""
Shape of a CountMinSketch, i.e. (number of tables, tablesize).
"""
function size(cms::CountMinSketch)
    # It's the reverse as we store the sketch in table-major order (which in
    # Julia means transposed (tables are columns), as Julia is Column major).
    return reverse(size(cms.sketch))
end


"""
Estimates the collision or aliasing rate of a `CountMinSketch`.

The collision rate is the probability that a random key will be added in such a
way that it is indistinguishable to another random key. This is equivalent to
the product of the probablities of colliding in each table independently, which
is simply the occupancy rate of each table.

Generally avoid using a `CountMinSketch` with a collision rate above about 0.05
- 0.10.
"""
function collisionrate(cms::CountMinSketch)
    # Expectected collision rate, modified from Khmer
    occupancy = sum(cms.sketch .> 0, 1)
    # The total FPR is the product of all rates, as we assume each is truly
    # independent
    rate = prod(float(occupancy) / float(cms.tablesize))
    return rate
end


function writecms(filename::AbstractString, cms::CountMinSketch)
    h5open(filename, "w") do h5f
        # Chunks of up to 1MB by one table
        chunksize = (min(2^20, cms.tablesize), 1)
        h5f["sketch", "blosc", 9, "chunk", chunksize] = cms.sketch
    end
end


function readcms(filename::AbstractString)
    h5open(filename, "r") do h5f
        sketch = h5f["sketch"]
        # Sketch is stored column major
        ts, nt = size(sketch)
        cms = CountMinSketch{eltype(sketch)}(nt, ts)
        cms.sketch = read(sketch)
        cms.tables = nt
        cms.tablesize = ts
        return cms
    end
end


end # module CountMin
