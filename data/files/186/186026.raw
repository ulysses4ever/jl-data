export md5, md5file

const K = floor(UInt32, abs(sin(1:64))*2^32)

const s = vcat(map(a->repmat(a, 4), (Int32[7, 12, 17, 22],
                                     Int32[5,  9, 14, 20],
                                     Int32[4, 11, 16, 23],
                                     Int32[6, 10, 15, 21]))...)

# Uint64 -> 8 bytes
split(b::Uint64) = [uint8(b >> 8i) for i = 0:7]

# Read 64 bytes (512 bits) out of the stream
function chunk!(ch::Array{Uint8}, io::IO)
  forced = position(io) > 0 && eof(io)
  l = length(ch) # 64
  n = readbytes!(io, ch)
  if n < length(ch)
    ch[n+1] = forced ? 0x00 : 0x80 # append 100000... 
    for i = n+2:l
      ch[i] = 0x00
    end
    l-n < 3 && # We need 3 bytes for 0x80 bit + Uint64 size
      return false # Force another chunk
    ch[l-7:l] = position(io)*8 |> Uint64 |> split
  end
  return done = n < l || eof(io)
end

# Four bytes -> 1 UInt32 word, little endian
word(b1::Uint8, b2::Uint8, b3::Uint8, b4::Uint8) =
  (uint32(b4) << 8*3) |
  (uint32(b3) << 8*2) |
  (uint32(b2) << 8*1) |
  (uint32(b1) << 8*0)

# Grab UInt32 words from byte chunk
function word!(M::Array{UInt32}, ch::Array{Uint8})
  for i = 1:length(M)
    j = 4(i-1)
    M[i] = word(ch[j+1], ch[j+2], ch[j+3], ch[j+4])
  end
  return M
end

# Four UInt32 words -> 1 md5 hash
function md5(bs::UInt32...)
  place = 16
  n = uint128(0)
  for b in bs
    for _ = 1:4
      place -= 1
      n |= uint128(b & 0xff) << 8*place
      b >>>= 8
    end
  end
  return n
end

@inline leftrotate(x::Uint32, c::Int32) = (x << c) | (x >> (int32(32)-c))

function md5(io::IO)
  a, b, c, d = 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476
  ch = Array(Uint8, 64)
  M = Array(UInt32, 16)
  done = false
  while !done
    done = chunk!(ch, io); word!(M, ch)
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
  return md5(a, b, c, d)
end

md5(s::String) = md5(IOBuffer(s))
md5(s::Array{UInt8}) = md5(IOBuffer(s))

md5file(f) = open(md5, f)
