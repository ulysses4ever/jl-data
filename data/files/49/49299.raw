module CountMin

export CountMinSketch,
        getprimesabove,
        getprimesbelow,
        push!,
        pop!,
        add!,
        haskey,
        getindex,
        collisionrate,
        write,
        read!,
        append!,
        unappend!,
        eltype,
        size


import Base: read!, write, push!, pop!, getindex, eltype, size

# File IO constants
const CMSMAGIC = b"cms\x00jl" # Magic string
# unsigned type list by bytes occupied
const SIZES = [UInt8, UInt16, UInt32, UInt32, UInt64, UInt64, UInt64, UInt64]

# Helper functions to get primes above or below a number, which is how we get
# our table sizes.
function getprimesabove{T<:Integer}(from::T, number)
    have = 0
    prime = Array(T, number)
    at = from
    if iseven(at)
        at += 1
    end
    while have < number
        if isprime(at)
            have += 1
            prime[have] = at
        end
        at += 2
    end
    return prime
end

function getprimesbelow{T<:Integer}(until::T, number)
    have = 0
    prime = Array(T, number)
    at = until
    if iseven(at)
        at -= 1
    end
    while have < number
        if isprime(at)
            have += 1
            prime[have] = at
        end
        at -= 2
    end
    return prime
end

# Our CountMinSketch implementation
type CountMinSketch{T<:Unsigned}
    # Num tables (to save geting this from shape(sketch)
    tables::Unsigned
    # we store bins in a Matrix
    sketch::Matrix{T}
    # The prime moduli of the sketch tables
    moduli::Vector{UInt64}
    function CountMinSketch(tables::Integer, tablesize::Integer)
        tables > 1 || error("Must have more than 1 table")
        tablesize > 1 || error("Table size must be greater than 1")
        sketch = zeros(T, tables, tablesize)
        moduli = getprimesbelow(tablesize, tables)
        return new(unsigned(tables), sketch, moduli)
    end
    function CountMinSketch()
        return new(unsigned(0), zeros(T,0,0), zeros(UInt64, 0))
    end
end

function add!(cms::CountMinSketch, item::Integer, number)
    item = UInt64(item)
    for i in 1:cms.tables
        offset = item % cms.moduli[i] + 1
        cms.sketch[i, offset] += number
    end
end

function getindex(cms::CountMinSketch, item::Integer)
    item = UInt64(item)
    min = 0
    for i in 1:cms.tables
        offset = item % cms.moduli[i] + 1
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
    rate = prod(float(occupancy) ./ float(cms.moduli))
    return rate
end

function write(stream::IO, cms::CountMinSketch)
    if isreadonly(stream)
        error("stream must be writable")
    end
    seekstart(stream)
    # Magic
    write(stream, CMSMAGIC)
    # version
    write(stream, UInt8(1))
    # Size of the elements
    write(stream, UInt8(sizeof(eltype(cms.sketch))))
    # padding to 16b, for future compatibility
    write(stream, "\0" ^ 2)
    # Number of tables, little endian u32
    write(stream, htol(UInt32(cms.tables)))
    # Size of the sketch matrix
    write(stream, htol(UInt64(cms.tablesize)))
    # Write each table
    for tab in 1:cms.tables
        write(stream, htol(UInt64(cms.moduli)))
    end
    write(stream, cms.sketch)
    return position(stream)
end

function read!(stream::IO, cms::CountMinSketch)
    seekstart(stream)
    # Check magic num & version
    file_magic = readbytes(stream, sizeof(CMSMAGIC))
    if file_magic != CMSMAGIC
        println("File magic is ", escape_string(file_magic))
        error("File doesn't contain CountMinSketch.jl magic")
    end
    version = read(stream, UInt8, 1)[1]
    if version != 1
        error("Unsuported CountMinSketch.jl file format version")
    end
    elsize = read(stream, UInt8, 1)[1]
    if !(elsize in [1, 2, 4, 8])
        error("Invalid element size `", elsize, "'. Must be 1,2,4 or 8")
    end
    # skip past padding
    skip(stream, 2)
    # Number of tables, little endian u32
    cms.tables = ltoh(read(stream, UInt32, 1)[1])
    # Sketch matrix size
    cms.tablesize = ltoh(read(stream, UInt64, 1)[1])
    # Write each table
    for tab in 1:cms.tables
        cms.moduli = read(stream, UInt64, cms.tables)
    end
    cms.sketch = zeros(SIZES[elsize], cms.tables, cms.tablesize)
    read!(stream, cms.sketch)
    return position(stream)
end

function append!(a::CountMinSketch, b::CountMinSketch)
    if a.tables != b.tables || a.tablesize != b.tablesize || a.moduli != b.moduli
        error("CountMinSketches must be of the exact same sketch dimensions")
    end
    a.sketch += b.sketch
end

function unappend!(a::CountMinSketch, b::CountMinSketch)
    if a.tables != b.tables || a.tablesize != b.tablesize || a.moduli != b.moduli
        error("CountMinSketches must be of the exact same sketch dimensions")
    end
    a.sketch -= b.sketch
end

end # module CountMinSketch
