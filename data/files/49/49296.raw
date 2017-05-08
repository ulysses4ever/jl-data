module CountMin

import Base: read!, write

export getprimesabove,
       getprimesbelow,
       CountMinSketch,
       add!,
       retrieve,
       collisionrate,
       write,
       read!

const CMSMAGIC = b"cms\x00jl\x09\x01"
const SIZES = [Uint8, Uint16, None, Uint32, None, None, None, Uint64]

function getprimesabove{T}(from::T, number)
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

function getprimesbelow{T}(until::T, number)
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

type CountMinSketch{T <: Unsigned}
    sketch::Matrix{T}
    tables::Uint64
    tablesize::Uint64
    moduli::Vector{Uint64}
    function CountMinSketch(tables, tablesize)
        if tables < 2
            error("Must have more than 1 table in a CountMinSketch")
        end
        tables = convert(Uint64, tables)
        tablesize = convert(Uint64, tablesize)
        sketch = zeros(T, tables, tablesize)
        moduli = getprimesbelow(tablesize, tables)
        return new(sketch, tables, tablesize, moduli)
    end
    function CountMinSketch()
        return new(zeros(T,0,0), 0, 0, zeros(Uint64, 0))
    end
end

function insert!(cms::CountMinSketch, item)
    item = uint64(item)
    for i in 1:cms.tables
        offset = item % cms.moduli[i] + 1
        cms.sketch[i, offset] += 1
    end
end

function retrieve(cms::CountMinSketch, item)
    item = uint64(item)
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
    write(stream, uint8(1))
    # Size of the elements
    write(stream, uint8(sizeof(eltype(cms.sketch))))
    # padding to 16b, for future compatibility
    write(stream, "\0" ^ 2)
    # Number of tables, little endian u32
    write(stream, htol(uint32(cms.tables)))
    # Size of the sketch matrix
    write(stream, htol(uint64(cms.tablesize)))
    # Write each table
    for tab in 1:cms.tables
        write(stream, htol(uint64(cms.moduli)))
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
    version = read(stream, Uint8, 1)[1]
    if version != 1
        error("Unsuported CountMinSketch.jl file format version")
    end
    elsize = read(stream, Uint8, 1)[1]
    if !(elsize in [1, 2, 4, 8])
        error("Invalid element size `", elsize, "'. Must be 1,2,4 or 8")
    end
    # skip past padding
    skip(stream, 2)
    # Number of tables, little endian u32
    cms.tables = ltoh(read(stream, Uint32, 1)[1])
    # Sketch matrix size
    cms.tablesize = ltoh(read(stream, Uint64, 1)[1])
    # Write each table
    for tab in 1:cms.tables
        cms.moduli = read(stream, Uint64, cms.tables)
    end
    cms.sketch = zeros(SIZES[elsize], cms.tables, cms.tablesize)
    read!(stream, cms.sketch)
    return position(stream)
end

end # module CountMinSketch
