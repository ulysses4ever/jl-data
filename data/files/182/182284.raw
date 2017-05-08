# Challenge 1:
#
# Convert hex to base64
# The string
# 49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d
# Should produce:
# SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t

# Solution:
# There is already a hex2bytes function in Julia which takes a string with hex
# values and converts it to a array of uint8s. We only need to code a function
# to convert bytes to base64. To make it complete, let us also convert back
# with another function.

function bytes2base64(bytes)
  const b64chars = ['A':'Z';'a':'z';'0':'9';'+';'/']
  const base64_pad = '='
  padlen = length(bytes) % 3
  append!(bytes, [0 for i=1:padlen])
  res = Char[]
  for i in 0:(length(bytes)/3)-1
    tmp = (convert(Uint32, bytes[3i+1]) << 16) |
          (convert(Uint32, bytes[3i+2]) << 8) |
           convert(Uint32, bytes[3i+3])
    push!(res, b64chars[(tmp >> 18) & 0x3f + 1])
    push!(res, b64chars[(tmp >> 12) & 0x3f + 1])
    push!(res, b64chars[(tmp >> 6)  & 0x3f + 1])
    push!(res, b64chars[(tmp >> 0)  & 0x3f + 1])
  end
  append!(res, [base64_pad for i = 1:padlen])
  return join(res)
end

function base642bytes(b64str)
  const b64chars = ['A':'Z';'a':'z';'0':'9';'+';'/']
  const b64dict = [b64chars[i] => i-1 for i = 1:length(b64chars)]
  m = match(r"(=*)$", b64str)
  padlen = length(m.match)
  b64str = b64str[1:end-padlen]
  res = Uint8[]
  for i in 0:length(b64str)/4-1
    tmp = b64dict[b64str[4i+1]] << 18 |
          b64dict[b64str[4i+2]] << 12 |
          b64dict[b64str[4i+3]] <<  6 |
          b64dict[b64str[4i+4]] <<  0
    mask = 0x000000FF
    bytes = [tmp & (mask << 16) >> 16,
             tmp & (mask <<  8) >>  8,
             tmp & (mask <<  0) >>  0]
    append!(res, bytes)
  end
  res = res[1:end-padlen]
end

using Base.Test
hex = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"
goal = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"
@test goal == bytes2base64(hex2bytes(hex))

# Challenge 2
# Fixed XOR
# Write a function that takes two equal-length buffers and produces their XOR combination.
# If your function works properly, then when you feed it the string:
# 1c0111001f010100061a024b53535009181c
# ... after hex decoding, and when XOR'd against:
# 686974207468652062756c6c277320657965
# ... should produce:
# 746865206b696420646f6e277420706c6179

function xor(data, key)
  res = Uint8[]
  for i in 0:(length(data)-1)
    push!(res, data[i+1] $ key[i%length(key)+1])
  end
  return res
end

data_str = "1c0111001f010100061a024b53535009181c"
key_str = "686974207468652062756c6c277320657965"
goal_str = "746865206b696420646f6e277420706c6179"
xor(hex2bytes(data_str), hex2bytes(key_str))
@test xor(hex2bytes(data_str), hex2bytes(key_str)) == hex2bytes(goal_str)

# Challenge 3
# Single-byte XOR cipher
# The hex encoded string:

# 1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736
# ... has been XOR'd against a single character. Find the key, decrypt the message.

function score_englishness(bytes::Array{Uint8,1})
  str = ASCIIString(bytes)
  m = matchall(r"(e|t|a|o|i|n| )"i, str)
  return length(m)/length(bytes)
end

function guess_xor_byte_key(bytes)
  scores = [score_englishness(xor(data, key)) for key = 0:255]
  key = indmax(scores)-1
  return key
end

data = hex2bytes("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736")
println(ASCIIString(xor(data, guess_xor_byte_key(data))))



