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
  scores = [score_englishness(xor(bytes, key)) for key = 0:255]
  key = indmax(scores)-1
  return convert(Uint8, key)
end

data = hex2bytes("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736")
println(ASCIIString(xor(data, guess_xor_byte_key(data))))


# Challenge 4
# Detect single-character XOR
# One of the 60-character strings in this file has been encrypted by single-character XOR.
# Find it.

f = open("/home/timos/Work/cpals/4.txt")
lines = readlines(f)
bytes = map(x->hex2bytes(chomp(x)), lines)
keys = map(guess_xor_byte_key, bytes)
decrypts = map(i->xor(bytes[i], keys[i]), 1:length(keys))
scores = map(score_englishness, decrypts)
println(ASCIIString(decrypts[indmax(scores)]))

# Challenge 5
# Implement repeating-key XOR
# Here is the opening stanza of an important work of the English language:
# Burning 'em, if you ain't quick and nimble
# I go crazy when I hear a cymbal
# Encrypt it, under the key "ICE", using repeating-key XOR.
# In repeating-key XOR, you'll sequentially apply each byte of the key; the
# first byte of plaintext will be XOR'd against I, the next C, the next E, then
# I again for the 4th byte, and so on.
# It should come out to:
# 0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272
# a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f

data_str = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal"
key_str = "ICE"
goal_str = "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f"
res = xor(data_str, key_str)
@test res == hex2bytes(goal_str)

# Challenge 6
# There's a file here. It's been base64'd after being encrypted with repeating-key XOR.
# Decrypt it.

function split_into_blocks(bytes, blocksize)
  numblocks = ifloor(length(bytes)/blocksize)
  reshape(bytes[1:blocksize*numblocks], blocksize, numblocks)'
end

function hamming_distance(bytes1, bytes2)
  bytes = xor(bytes1, bytes2)
  # this could be optimized, i.e., make use of popcnt inst
  bitstr = join(map(bits, bytes))
  length(matchall(r"1", bitstr))
end

@test hamming_distance("this is a test", "wokka wokka!!!") == 37

function avg_hamming_distance(bytes, blocksize)
  blocks = split_into_blocks(bytes, blocksize)
  nblocks = min(length(blocks), 30)
  dists = [hamming_distance(blocks[i], blocks[j]) for i=1:nblocks, j=1:nblocks]
  sum = reduce(+, dists) / (nblocks^2-nblocks)
end

function detect_xor_keylen(bytes)
  hamming_sums = map(x->avg_hamming_distance(bytes, x), [1:40])
  keylen = indmin(hamming_sums)
end

function guess_xor_key(bytes)
  keylen = detect_xor_keylen(bytes)
  blocks = split_into_blocks(bytes, keylen)'
  key = mapslices(guess_xor_byte_key, split_into_blocks(bytes ,keylen)', 2)
  return vec(key)
end

f = open("/home/timos/Work/cpals/6.txt")
s = map(chomp, readlines(f))
b64str = join(s)
bytes = base642bytes(b64str)
key = guess_xor_key(bytes)
plain = xor(bytes, key)
println(ASCIIString(key))
println(ASCIIString(plain))

# Challenge 7:
# AES in ECB mode
# The Base64-encoded content in this file has been encrypted via AES-128 in ECB
# mode under the key "YELLOW SUBMARINE".
# Decrypt it. You know the key, after all.

using AES  #Pkg.clone("https://github.com/faf0/AES.jl.git")
f = open("/home/timos/Work/cpals/7.txt")
s = map(chomp, readlines(f))
b64str = join(s)
bytes = base642bytes(b64str)
key = convert(Array{Uint8,1}, "YELLOW SUBMARINE")
plain = AESECB(bytes, key, false)
println("Challenge 7")
println(ASCIIString(plain))

# Challenge 8:
# Detect AES in ECB mode
# In this file are a bunch of hex-encoded ciphertexts.
# One of them has been encrypted with ECB.
# Detect it.
# Remember that the problem with ECB is that it is stateless and deterministic;
# the same 16 byte plaintext block will always produce the same 16 byte ciphertext.

f = open("/home/timos/Work/cpals/8.txt")
lines = map(chomp, readlines(f))
bytes = map(hex2bytes, lines)
# find successive identical blocks of length blocksize
