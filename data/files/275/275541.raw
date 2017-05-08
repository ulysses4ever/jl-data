module crypto101

export chi2score, pop, hammingdistance

expectedFreq = [
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

# POP: given char or unsigned int, it returns the population count, ie number of bits that are set to one
function pop(x::UInt32) # from "Hacker's Delight"
  x::UInt32 = x - ((x >> 1) & 0x55555555)
  x = (x & 0x33333333) + ((x >> 2) & 0x33333333)
  x = (x + (x >> 4)) & 0x0F0F0F0F
  x = x + (x >> 8)
  x = x + (x >> 16)
  return Int64(x & 0x0000003F)
end

function pop{T<:Unsigned}(x::T)
  n = 0
  while x != zero(T)
    n += 1
    x = x&(x-one(T))
  end
  n
end

pop(x::Char) = pop(UInt32(x))
pop(x) = count( c->(c=='1'), bits(x))

# HAMMINGDISTANCE: number of bits that are different between x and y
hammingdistance{T<:Unsigned}(x::T,y::T) = pop(x$y)
hammingdistance{T<:Char}(x::T,y::T) = pop(x $ y)

function hammingdistance{T<:String}(xs::T,ys::T)
  length(xs) == length(ys) || error("strings must be equal length to compute hamming distance")
  sum([hammingdistance(x,y) for (x,y) in zip(xs,ys)])
end


end # module


# NOTES

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

