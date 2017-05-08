include("../src/Padding.jl")
include("testing.jl")

importall Padding

for padder = [BytePadding, AnsiX923, Iso10126, Pkcs7, IsoIec7816_4]
    print("Testing ", padder, " ")
    for block_size = 1:10
        for test_value = map(x -> convert(Array{Uint8}, x), ["foo", "foobar", "baz", "this is a test", ""])
            padded = pad!(padder, block_size, copy(test_value))
            @assert_not_equal(test_value, padded)
            @assert_equal(0, length(padded) % block_size)

            unpadded = unpad!(padder, padded)
            @assert_equal(test_value, unpadded)
        end
    end
    println()
end

println()