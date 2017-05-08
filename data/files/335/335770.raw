module Crypto101

using Base.Collections, Base.Order

export str2bytes, chi2score, collectNBestXor, encryptxor, populationcount, hammingdistance, randompass, countsameblocks
export pad, unpad, Padder1Bit, PadderPKCS7
export heappeek, heappushpop!, heapreplace!

heappeek(xs::AbstractArray) = xs[1]

# Binary min-heap pushpop (faster than push followed by pop, as only one percolate).
function heappushpop!(xs::AbstractArray, x, o::Ordering=Forward)
    if !isempty(xs) && lt(o, xs[1], x)
        xs[1], x = x, xs[1]
        Base.Collections.percolate_down!(xs, 1, o)
    end
    x
end

# Binary min-heap replace (faster than pop followed by push, as only one percolate).
function heapreplace!(xs::AbstractArray, x, o::Ordering=Forward)
    xs[1] = x
    Base.Collections.percolate_down!(xs, 1, x, o)
    xs
end


str2bytes(s::String) = [UInt8(c) for c in s]

const expectedFreq = [
8.167    #a
1.492    #b
2.782    #c
4.253    #d
12.702    #e
2.228    #f
2.015    #g
6.094    #h
6.966    #i
0.153    #j
0.772    #k
4.025    #l
2.406    #m
6.749    #n
7.507    #o
1.929    #p
0.095    #q
5.987    #r
6.327    #s
9.056    #t
2.758    #u
0.978    #v
2.360    #w
0.150    #x
1.974    #y
0.074    #z
  15.0   # space
  8.0    # punctuation
  2.0   # all others
]

# CHI2SCORE: given a string, computes how far away it is to ordinary English, by character frequency.
# The smaller (closer to 0) the result, the more the text resembles English.
function chi2score(s)
  actualFreq = zeros(Int64,29)
  ln = length(s)
  for c in s
    normalizedC = uppercase(Char(c))
    if 'A' <= normalizedC <= 'Z'
      i = Int(normalizedC) - Int('A') + 1
    elseif normalizedC == ' '
      i = 27
    elseif normalizedC in ".,;:!?"
      i = 28
    else
      i = 29
    end
    actualFreq[i] += 1
  end
  disc = 0
  for i = 1:29
    disc += (actualFreq[i]/ln - expectedFreq[i]/125.0)^2 / (expectedFreq[i]/125.0)
  end
  disc
end

const charsbyfrequency = UInt8[0x20,0x65,0x74,0x61,0x6f,0x69,0x6e,0x73,0x68,0x72,0x64,0x6c,0x66,0x63,0x6d,0x75,
                              0x67,0x79,0x70,0x77,0x62,0x76,0x6b,0x6a,0x78,0x71,0x7a,0x53,0x41,0x43,0x4d,0x50,
                              0x52,0x54,0x42,0x46,0x47,0x44,0x4c,0x48,0x49,0x45,0x4e,0x4f,0x57,0x55,0x56,0x4a,
                              0x4b,0x51,0x59,0x5a,0x58,0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x09,
                              0x0a,0x2c,0x2e,0x21,0x3f,0x2f,0x40,0x23,0x24,0x25,0x5e,0x26,0x2a,0x28,0x29,0x5f,
                              0x2b,0x5b,0x5d,0x3b,0x3a,0x27,0x22,0x2d,0x3c,0x3d,0x3e,0x5c,0x60,0x7b,0x7c,0x7d,
                              0x7e,0x7f,0x80,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x0b,0x0c,0x0d,0x0e,
                              0x0f,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,
                              0x1f,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,
                              0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9a,0x9b,0x9c,0x9d,0x9e,0x9f,
                              0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,
                              0xb0,0xb1,0xb2,0xb3,0xb4,0xb5,0xb6,0xb7,0xb8,0xb9,0xba,0xbb,0xbc,0xbd,0xbe,0xbf,
                              0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,
                              0xd0,0xd1,0xd2,0xd3,0xd4,0xd5,0xd6,0xd7,0xd8,0xd9,0xda,0xdb,0xdc,0xdd,0xde,0xdf,
                              0xe0,0xe1,0xe2,0xe3,0xe4,0xe5,0xe6,0xe7,0xe8,0xe9,0xea,0xeb,0xec,0xed,0xee,0xef,
                              0xf0,0xf1,0xf2,0xf3,0xf4,0xf5,0xf6,0xf7,0xf8,0xf9,0xfa,0xfb,0xfc,0xfd,0xfe,0xff]


# collectNBestXor: given an array of unsigneds and N, will XOR with all b in 0:255,
# score them for similarity to English using chi2score,
# and return the N best matches as tuples (-score, b, plaintext_bytes)
function collectNBestXor{T<:Unsigned}(ciphertext_bytes::Array{T,1}, N = 1)
  candidate_heap = fill((Inf,zero(T),T[]), N)
  for b::T = 0:255
    plaintext_bytes = ciphertext_bytes $ b
    s   = chi2score(plaintext_bytes)
    heappushpop!(candidate_heap, (s,b,plaintext_bytes), Reverse)
  end
  candidate_heap
end

# ENCRYPT_XOR: given a plaintext array and a key array,
# returns an array of the plaintext xor-ed with the (infinitely repeating) key sequence
function encryptxor(pt_b, key_b)
  res = copy(pt_b)
  for i = 1:length(pt_b)
    res[i] = pt_b[i] $ key_b[mod1(i,length(key_b))]
  end
  res
end


# POPULATIONCOUNT: given char or unsigned int, it returns the population count, ie number of bits that are set to one
function populationcount(x::UInt32) # from "Hacker's Delight"
  x::UInt32 = x - ((x >> 1) & 0x55555555)
  x = (x & 0x33333333) + ((x >> 2) & 0x33333333)
  x = (x + (x >> 4)) & 0x0F0F0F0F
  x = x + (x >> 8)
  x = x + (x >> 16)
  return Int64(x & 0x0000003F)
end

function populationcount{T<:Unsigned}(x::T)
  n = 0
  while x != zero(T)
    n += 1
    x = x&(x-one(T))
  end
  n
end

populationcount(x::Char) = populationcount(UInt32(x))
populationcount(x) = count( c->(c=='1'), bits(x))

# PAR computes the parity of x, that is 1 if the number of set bits in x is odd, and 0 if it's even
function par(x::UInt8)
    y = x $ (x>>1)
    y = y $ (y>>2)
    y = y $ (y>>4)
    y & one(x)
end

par(x) = populationcount(x) & one(x)

# HAMMINGDISTANCE: number of bits that are different between x and y
hammingdistance{T<:Unsigned}(x::T,y::T) = populationcount(x $ y)
hammingdistance{T<:Char}(x::T,y::T) = populationcount(x $ y)

function hammingdistance{T<:String}(xs::T,ys::T)
  length(xs) == length(ys) || error("strings must be equal length to compute hamming distance")
  sum([hammingdistance(x,y) for (x,y) in zip(xs,ys)])
end


# RANDOMPASS: a trivial utility function to get a "random" password of given length.
# Note: no guarantees for crypto strength
randompass(len::Int) = rand(UInt8, len)

# COUNTSAMEBLOCKS: counts how often two different blocks of length block_size (starting at 1, 1+block_size, 1+2*block_size, ...)
# are the same in the given string ct_b
function countsameblocks(ct_b, block_size = 16) # n^2 algo
    c = 0
    r = 2
    while r*block_size <= length(ct_b)
        l = 1
        while l < r
            if ct_b[((r-1)*block_size+1):(r*block_size)] == ct_b[((l-1)*block_size+1):(l*block_size)]
                c += 1
            end
            l += 1
        end
        r += 1
    end
    c
end

# PADDER: a type to pad the length of a text to a multiple of some integer, reversibly
abstract Padder
# support pad!(p::Padder, sequence), unpad!(p,s)

# default implementations
pad(p::Padder, seq) = pad!(p, copy(seq))
unpad(p::Padder, seq) = unpad!(p, copy(seq))

immutable PadderPKCS7 <: Padder
    numBytes::Int
    function PadderPKCS7(n::Integer)
        n < 256 || error("PKCS7 can only pad to multiples smaller 256")
        n > 0 || error("PKCS7 multiple must be positive")
        new(n)
    end
end

function pad!(p::PadderPKCS7, seq::AbstractArray{UInt8,1})
    r = p.numBytes - mod(length(seq), p.numBytes) # r is in 1..p.numBytes
    padding = fill(UInt8(r) ,r)
    append!(seq, padding)
end

function unpad!(p::PadderPKCS7, seq::AbstractArray{UInt8,1})
    L = length(seq)
    mod(L, p.numBytes) == 0 || error("padded sequence length should be multiple of $(p.numBytes), is $L.")
    lastByte = seq[L]
    lastByte <= L || error("incorrect padding")
    for k = (L-lastByte+1):L
        seq[L] == lastByte || error("incorrect padding")
    end
    resize!(seq, L-lastByte)
end

immutable Padder1Bit <: Padder
    numBytes::Int
    function Padder1Bit(n::Integer)
        n > 0 || error("Padder1Bit multiple must be positive")
        new(n)
    end
end

function pad!(p::Padder1Bit, seq::AbstractArray{UInt8,1})
    r = p.numBytes - mod(length(seq),p.numBytes)  # r is in 1..p.numBytes
    padding = fill(UInt8(0), r)
    padding[1] = 0x80
    append!(seq,padding)
end

function unpad!(p::Padder1Bit, seq::AbstractArray{UInt8,1})
    L = length(seq)
    mod(L, p.numBytes) == 0 || error("padded sequence length should be multiple of $(p.numBytes), is $L.")
    while seq[L] == 0x00
        L -= 1
        L == 0 && error("incorrect padding")
    end
    seq[L] == 0x80 || error("incorrect padding")
    resize!(seq, L-1)
end


end # module


# NOTES

# b"YELLOW" == [0x59, 0x45, 0x4c, 0x4c, 0x4f, 0x57]
# hex2bytes("1234ab")
# bytes2hex(bin_arr::Array{UInt8, 1})
# num2hex(f) Get a hexadecimal string of the binary representation of a floating point number
# hex2num(str)
# bswap(n)
# bits(n)
# hex(n[, pad]) Convert an integer to a hexadecimal string, optionally specifying a number of digits to pad to.
# dec(n[, pad]) Convert an integer to a decimal string, optionally specifying a number of digits to pad to.
# oct(n[, pad]) Convert an integer to an octal string, optionally specifying a number of digits to pad to.
# base(base, n[, pad])

# Base64EncodePipe(ostream)
# Returns a new write-only I/O stream, which converts any bytes written to it into base64-encoded ASCII bytes written to ostream. Calling close on the Base64Pipe stream is necessary to complete the encoding (but does not close ostream).
# Base64DecodePipe(istream)
# Returns a new read-only I/O stream, which decodes base64-encoded data read from istream.
# base64encode(writefunc, args...)
# base64encode(args...)
# Given a write-like function writefunc, which takes an I/O stream as its first argument, base64(writefunc, args...) calls writefunc to write args... to a base64-encoded string, and returns the string. base64(args...) is equivalent to base64(write, args...): it converts its arguments into bytes using the standard write functions and returns the base64-encoded string.
# base64decode(string)
# Decodes the base64-encoded string and returns the obtained bytes.

