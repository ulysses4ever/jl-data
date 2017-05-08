module MD5

import Base: start, next, done

using ..GutFlora

export md5, md5file

const K = floor(UInt32, abs(sin(1:64))*2^32)

const s = vcat(map(a->repmat(a, 4), (Int32[7, 12, 17, 22],
                                     Int32[5,  9, 14, 20],
                                     Int32[4, 11, 16, 23],
                                     Int32[6, 10, 15, 21]))...)

# UInt8 bytes to UInt32 words, little endian
function word!(M::Array{UInt32}, ch::Array{Uint8})
  for i = 1:length(M)
    j = 4(i-1)
    M[i] = bitcat(ch[j+4], ch[j+3], ch[j+2], ch[j+1])
  end
  return M
end

type MD5Chunks{T<:IO}
  io::T
  bytes::Vector{UInt8}  # length 64
  words::Vector{UInt32} # length 16
  marked::Bool # Appended the 1 bit
  done::Bool   # Appended the length
end

MD5Chunks(io) = MD5Chunks(io, Array(UInt8, 64), Array(UInt32, 16), false, false)
chunks(io) = MD5Chunks(io)

start(cs::MD5Chunks) = nothing
done(cs::MD5Chunks, _) = cs.done

@inline function next(cs::MD5Chunks, _)
  n = readbytes!(cs.io, cs.bytes)
  if n < 64
    cs.bytes[n+1] = cs.marked ? 0x00 : 0x80 # Append the 1 bit
    cs.marked = true
    for i = n+2:64
      cs.bytes[i] = 0x00
    end
    if 64-n >= 9 # space for 0x80 + 64bit size
      cs.bytes[64-7:64] = position(cs.io)*8 |> UInt64 |> reverse |> split8 |> collect
      cs.done = true
    end
  end
  word!(cs.words, cs.bytes)
  return cs.words, nothing
end

@inline leftrotate(x::Uint32, c::Int32) = (x << c) | (x >> (int32(32)-c))

function md5(io::IO)
  a, b, c, d = 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476

  for M in chunks(io)
    A, B, C, D = a, b, c, d

    for i = 0:63
      F = uint32(0)
      g = 0
      if 0 ≤ i ≤ 15
        F = (B & C) | (~B & D)
        g = i
      elseif 16 ≤ i ≤ 31
        F = (D & B) | (~D & C)
        g = mod(5i + 1, 16)
      elseif 32 ≤ i ≤ 47
        F = B $ C $ D
        g = mod(3i + 5, 16)
      elseif 48 ≤ i ≤ 63
        F = C $ (B | ~D)
        g = mod(7i, 16)
      end

      @inbounds rot = leftrotate(A + F + K[i+1] + M[g+1], s[i+1])
      A, B, C, D = D, B + rot, B, C
    end
    a += A; b += B; c += C; d += D
  end
  return bitcat(reverse(a), reverse(b), reverse(c), reverse(d))
end

md5(s::String) = md5(IOBuffer(s))
md5(s::Array{UInt8}) = md5(IOBuffer(s))

md5file(f) = open(md5, f)

end
