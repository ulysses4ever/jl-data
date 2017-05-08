using GutFlora
using Base.Test

@test md5("") == 0xd41d8cd98f00b204e9800998ecf8427e
@test md5("abc") == 0x900150983cd24fb0d6963f7d28e17f72
@test md5("message digest") == 0xf96b697d7cb7938d525a2f31aaf161d0
@test md5("abcdefghijklmnopqrstuvwxyz") == 0xc3fcd3d76192e4007dfb496cca67e13b
@test md5("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") == 0xd174ab98d277d9f5a5611c2c9f419d9f
@test md5("12345678901234567890123456789012345678901234567890123456789012345678901234567890") == 0x57edf4a22be3c955ac49da2e2107b67a
@assert md5("12345678"^8) == 0x6456d36652220045192fb2b53da70d63
@assert md5("12345678"^7) == 0xa61ecba06aaba225d2f6d36057c4b67c

for i = 1:1_000_000
  v = rand(UInt64)
  k = rand(UInt128)
  @test TEA.decrypt(TEA.encrypt(v, k), k) == v
end
