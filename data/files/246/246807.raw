const md5 = "1234567812345678"
seed = reinterpret(Uint64,md5.data)

const text = "The quick brown fox jumps over the lazy dog"

function md5string(text::Array{Uint8,1})
  l = uint64(sum([length(bits(i)) for i in text]))
  p = vcat(text,fill(uint8(128),1))
  lp = length(p)
  la = 0 == (lpp = (lp + 8) % 64) ? 0 : 64 - lpp
  if 0 < lpp
    p = vcat(p,fill(uint8(0),64-lpp))
  end # if
  pp = reshape(p,4,ifloor(length(p)/4))
  h = reinterpret(Uint32,vec([[reverse(pp[:,i]) for i=1:size(pp)[2]]...]))
  # h = reinterpret(Uint32,p)  # THIS IS Little-Endian: The 32-bit has the 8-bit elements in reverse order?
  h = vcat(h,[uint32(ifloor(l / 2^32)),uint32(l % 2^32)])
  return h
end # function

function md5rotate(A::Uint32,B::Uint32,C::Uint32,D::Uint32,F::Uint32,K::Uint32,M::Uint32,s::Uint32)
  # T::Uint32 = D
  # D = C
  # C = B
  # B = uint32(B + md5leftrotate(uint32(A + F + K + M), s))
  # A = T
  # return (A, B, C, D)
  return (D, uint32(B + md5leftrotate(uint32(A + F + K + M), s)), B, C)
end # function

# readall(`cd)

function md5_512(a::Uint32,b::Uint32,c::Uint32,d::Uint32,K::Array{Uint32,1},s::Array{Uint32,1},M::Array{Uint32,1})
  A = a; B = b; C = c; D = d
  for i=1:16
    F = uint32(D $ (B & (C $ D)))
    (A, B, C, D) = md5rotate(A, B, C, D, F, K[i], M[i], s[i])
  end # for
  for i=17:32
    F = uint32(C $ (D & (B $ C)))
    (A, B, C, D) = md5rotate(A, B, C, D, F, K[i], M[1 + (1 + 5*(i-1))%16], s[i])
  end # for
  for i=33:48
    F = uint32(B $ C $ D)
    (A, B, C, D) = md5rotate(A, B, C, D, F, K[i], M[1 + (5 + 3*(i-1))%16], s[i])
  end # for
  for i=49:64
    F = uint32(C $ (B | (~D)))
    (A, B, C, D) = md5rotate(A, B, C, D, F, K[i], M[1 + (0 + 7*(i-1))%16], s[i])
  end # for
  return (uint32(a+A), uint32(b+B), uint32(c+C), uint32(d+D))
end # function

function md5leftrotate(x::Uint32, s::Uint32)
  return uint32((x << s) | (x >>> (32-s)))
end # function

function md5hash(text::String)
  const s = let ss = [7 12 17 22
                      5  9 14 20
                      4 11 16 23
                      6 10 15 21]
    uint32(vec([[ss' for i=1:4]...]))
  end
  const K = [uint32(ifloor(abs(sin(i)) * 2^32)) for i=1:64]
  const a0 = uint32(0x67452301)
  const b0 = uint32(0xefcdab89)
  const c0 = uint32(0x89badcfe)
  const d0 = uint32(0x10325476)
  h = md5string(text.data)
  a = a0; b = b0; c = c0; d = d0
  while 0 < length(h)
    M = uint32([h[i] for i=1:16])
    (a, b, c, d) = md5_512(a, b, c, d, K, s, M)
    h = (16 == length(h)) ? Array(Uint32,0) : h[17,end]
  end # while
  return [uint64((a*2^32)+b),uint64((c*2^32)+d)]
end # function

function xorshift128p(s::Array{Uint64,1})
#=
  This function implements Sebastiano Vigna's xorshift 128+ algorithm
  a s	Seed (vector of length 2 of unsigned 64-bit integers)
  r 1	Seed, new seed value
  r 2	Draw, uniform random draw = s[1] + s[2] / 2^64
  d		Note that s[1] + s[2] may wrap around, creating the necessary nonlinearity
=#
  s2::Uint64 = s[1]
  s1::Uint64 = s[2]
  s2 $= s2 << 23								# xorshift a
  s2 = s2 $ s1 $ (s2 >>> 17) $ (s1 >>> 26)	# xorshift b,c
  return ([s1, s2], (s1 + s2) / 2.0^64)
end

function xorshift128p_v(s::Array{Uint64,1}, n::Int64)
#=This function wraps Sebastiano Vigna's xorshift 128+ algorithm
  a s	Seed (vector of length 2 of unsigned 64-bit integers)
  a n	Number (number of random draws requested
  r 1	Seed, new seed value
  r 2	Draw, vector of length n of random draws
  d		Wrapper around xorshift128p which produces many at once
  d		If n <= 0, returns an empty array
=#
  d = Array(Float64,0)
  while n > 0
    s,out = xorshift128p(s)
    push!(d, out)						# can I/how do I convert this to a comprehension?
    n -= 1
  end
  return (s, d)
end

# Additional requirements:
# 1.  How to split a Uint128 (or 128 bit string?) into two Uint64's
# 2.  How to access the c-code for md5 or a native one in Julia
# 2.1.  Keith built a md5hash function in c for use in k.
# 2.2.  Crypto has an "MD5" type/digest. How do I load a package?
#          using Crypto
#          Crypto.init()
#          Crypto.digest("MD5", "test")
# 3.
