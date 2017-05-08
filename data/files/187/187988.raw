module IDXParser

# package code goes here

using Base.Docs

export parseIDX

@doc """
Parse IDX-formatted file and return an array of values:
  1ˢᵗ byte: 0x00
  2ⁿᵈ byte: 0x00
  3ʳᵈ byte: Array Datatype: 0x08 -> UInt8, 0x09 -> Int8, 0x0B -> Int16, 0x0C -> Int32, 0x0D -> Float32, 0x0E -> Float64
  4ᵗʰ byte: # dimensions: 0x01 for vector, 0x02 for 2D matrix, etc.
  5ᵗʰ byte: length of first dimension
  ⋮
  (5 + #dimensions - 1)ᵗʰ byte: length of final dimension
  (5 + #dimensions)ᵗʰ byte: start of data 
""" ->
function parseIDX(file_name)
    fs = open(file_name, "r")
    magic_number = read(fs, UInt8, 4)

    if magic_number[1] != 0x00 && magic_number[2] != 0x00
        throw(DomainError())
    end

    if magic_number[3] == 0x08
        idx_type = UInt8
    elseif magic_number[3] == 0x09
        idx_type = Int8
    elseif magic_number[3] == 0x0B
        idx_type = Int16
    elseif magic_number[3] == 0x0C
        idx_type = Int32
    elseif magic_number[3] == 0x0D
        idx_type = Float32
    elseif magic_number[3] == 0x0E
        idx_type = Float64
    else
        throw(DomainError())
    end

    dims = Array{Int64}(map(ntoh, read(fs, Int32, magic_number[4])))

    contents = read(fs, idx_type, prod(dims))

    if idx_type != UInt8 && idx_type != Int8
        contents = map(ntoh, contents)
    end
    
    out = reshape(contents, tuple(dims...))
    return out 
end

end # module
