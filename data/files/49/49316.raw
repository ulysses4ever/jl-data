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

    # Number of bins per table
    tablesize::Unsigned

    # Num tables (to save getting this from shape(sketch)
    tables::Unsigned

    # We store the sketch as a Matrix
    sketch::Matrix{T}


end

"""
The constructor for `CountMinSketch`es

Arguments
---------

* `tables::Integer`: The number of tables to create
* `tablesize::Integer`: The size of each table
"""
function CountMinSketch(tables::Integer, tablesize::Integer)
    if !(1 <= tables <= 20)
        error("Must have between 1 and 20 tables")
    end
    tablesize > 1 || error("Table size must be greater than 1")
    sketch = zeros(T, tablesize, tables)
    return new(tablesize, tables, sketch)
end

"""
A trivial constructor for `CountMinSketch`es.

WARNING: This trivial constructor instantiates a tiny `CountMinSketch`, which
         will be useless for anything but a simple test. Storing more than 10
         items  is not recommended.
"""
function CountMinSketch()
    return CountMinSketch(4, 1000)
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
function add!(cms::CountMinSketch, item, count::Integer)
    for i in 1:cms.tables
        offset = hash(item, hash(i)) % cms.tablesize + 1
        try
            cms.sketch[offset, i] += count
        catch InexactError
            # clamp overflow to typemin/typemax(eltype(sketch))
            newval = count > 0 ? typemax(eltype(cms)) : typemin(eltype(cms))
            cms.sketch[offset, i] = newval
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
    minval = Inf
    for i in 1:cms.tables
        offset = hash(item, hash(i)) % cms.tablesize + 1
        val = cms.sketch[offset, i]
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
    cms = 0
    h5open(filename, "r") do h5f
        sketch = h5f["sketch"]
        # Sketch is stored column major
        ts, nt = size(sketch)
        cms = CountMinSketch{eltype(sketch)}(nt, ts)
        cms.sketch = read(sketch)
        cms.tables = nt
        cms.tablesize = ts
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

end # module CountMin
