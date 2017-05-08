# reversable padding functions for use in block cypher encryption
module Padding

include("Rand.jl")

# all use of these functions outside of this file are via:
function pad!(padding, block_size, data :: Array{Uint8})
    n = block_size - (length(data) % block_size)
    append!(data, make_padding(padding, n == 0 ? block_size : n))
end
function pad!(padding, block_size, data :: Array{Uint8}, length)
    n = block_size - (length % block_size)
    data[length+1:end] = make_padding(padding, n == 0 ? block_size : n)
end

function padded_size(block_size, data)
    len = length(data)
    n = block_size - (len % block_size)
    len + n
end

function unpad!(padding, data :: Array{Uint8})
    resize!(data, length(data) - padding_length(padding, data))
end

# which as you can see, requires everying padding sceme to implement both
# make_padding and padding_length

immutable NoPadding
end

function make_padding(::Type{NoPadding}, len)
    []
end

function padding_length(::Type{NoPadding}, data :: Array{Uint8})
    0
end


immutable BytePadding
end

function make_padding(::Type{BytePadding}, len)
    out = zeros(Uint8, len)
    out[1] = 1
    out
end

function padding_length(::Type{BytePadding}, data :: Array{Uint8})
    len = length(data)
    ct = 0
    while data[len - ct] == 0
        ct += 1
    end

    @assert data[len - ct] == 1
    ct + 1
end


immutable AnsiX923
end

function make_padding(::Type{AnsiX923}, len)
    out = zeros(Uint8, len)
    out[end] = len
    out
end

function padding_length(::Type{AnsiX923}, data :: Array{Uint8})
    data[end]
end


immutable Iso10126
end

function make_padding(::Type{Iso10126}, len)
    out = Rand.cryptographic_rand(len)
    out[end] = len
    out
end

function padding_length(::Type{Iso10126}, data :: Array{Uint8})
    data[end]
end


immutable Pkcs7
end

function make_padding(::Type{Pkcs7}, len)
    [len for i=1:len]
end

function padding_length(::Type{Pkcs7}, data :: Array{Uint8})
    data[end]
end


immutable IsoIec7816_4
end

function make_padding(::Type{IsoIec7816_4}, len)
    out = zeros(Uint8, len)
    out[1] = 0x08
    out
end

function padding_length(::Type{IsoIec7816_4}, data :: Array{Uint8})
    len = length(data)
    ct = 0
    while data[len - ct] == 0
        ct += 1
    end

    @assert data[len - ct] == 0x08
    ct + 1
end


export pad!, unpad!, padded_size, NoPadding, BytePadding, AnsiX923, Iso10126, Pkcs7, IsoIec7816_4

end # module Padding