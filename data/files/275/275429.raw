module AES

import Crypto101

export encipher, decipher, blocklength_bytes

# input 16 bytes         state 4 x 4 bytes             output 16 bytes
# in01 in05 in09 in13    s[1,1] s[1,2] s[1,3] s[1,4]   out01 out05 out09 out13
# in02 in06 in10 in14    s[2,1] s[2,2] s[2,3] s[2,4]   out02 out06 out10 out14
# in03 in07 in11 in15    s[3,1] s[3,2] s[3,3] s[3,4]   out03 out07 out11 out15
# in04 in08 in12 in16    s[4,1] s[4,2] s[4,3] s[4,4]   out04 out08 out12 out16

# questions:
# how to deal with endianness?
# how to encapsulate params for AES block cipher (generate with key)

# ref: fips-197.pdf

# conceptually:
# blockcipher contains key and params; turns fixed size block of plaintext bytes into ciphertext bytes
# cipher contains blockcipher, padding, block mode.
# Block mode contains type, and possibly initialization vector IV, counter, segment_size
# padding contains func to pad and depad

# AGENDA
# switch state to bitstype?? file:///Users/frl/Downloads/julia-release-0.3/index.html#bits-types

abstract Blockcipher
# supports: blocklength_bytes(bc), instantiation somehow,
# encode(bc, plaintext), decode(bc, ciphertext), with plaintext and ciphertext of length blocklength

abstract Blockmode

type Cipher
# supports: instantiation somehow, encode, decode, with arbitrary length texts
# contains: block cipher, block mode, padder
    blockcipher :: Blockcipher
    blockmode :: Blockmode
    padder :: Crypto101.Padder
end

# examples:

# encryptblock(cipherblock, keyblock)
# encrypt(cipherObj, plaintext)
# decrypt(cipherObj, plaintext)
# pad(plaintext, multiple)
# depad(paddedtext)


# FIXFIXFIX: make immutable?
type AESBlock <: Blockcipher
    Nb::Int    # Nb = 4          # number of (32-bit) columns in state. AES specifies 4, thus 128 bits of state
    Nk::Int    # Nk = 4,6,8      # number of (32-bit) words in key. AES specifies 4 (128 bit), 6 (192 bit), 8 (256 bit)
    Nr::Int    # Nr = 10,12,14   # number of rounds. 10, 12, 14
    key::Array{UInt8,1}          # key, as sequence of bytes (16, 24, or 32)

    function AESBlock(key::AbstractArray{UInt8,1})
        length(key) == 4*4 && return new(4, 4, 10, key)
        length(key) == 4*6 && return new(4, 6, 12, key)
        length(key) == 4*8 && return new(4, 8, 14, key)
        error("AESBlock key length should be 16, 24, or 32; is $(length(key))")
    end
end

blocklength_bytes(aes::AESBlock) = 16

# AES_Cipher(password, mode)

# """Create a new AES cipher

#     :Parameters:
#       key : byte string
#         The secret key to use in the symmetric cipher.
#         It must be 16 (*AES-128*), 24 (*AES-192*), or 32 (*AES-256*) bytes long.
#     :Keywords:
#       mode : a *MODE_** constant
#         The chaining mode to use for encryption or decryption.
#         Default is `MODE_ECB`.
#       IV : byte string
#         The initialization vector to use for encryption or decryption.

#         It is ignored for `MODE_ECB` and `MODE_CTR`.

#         For `MODE_OPENPGP`, IV must be `block_size` bytes long for encryption
#         and `block_size` +2 bytes for decryption (in the latter case, it is
#         actually the *encrypted* IV which was prefixed to the ciphertext).
#         It is mandatory.

#         For all other modes, it must be `block_size` bytes longs. It is optional and
#         when not present it will be given a default value of all zeroes.
#       counter : callable
#         (*Only* `MODE_CTR`). A stateful function that returns the next
#         *counter block*, which is a byte string of `block_size` bytes.
#         For better performance, use `Crypto.Util.Counter`.
#       segment_size : integer
#         (*Only* `MODE_CFB`).The number of bits the plaintext and ciphertext
#         are segmented in.
#         It must be a multiple of 8. If 0 or not specified, it will be assumed to be 8.

#     :Return: an `AESCipher` object
#     """


# xtimes in fips-197
function xtimes(b::UInt8)
    if b & 0x80 == 0x80
        ( b << 1 ) $ 0x1b
    else
        b << 1
    end
end

# finite field multiplication, ∙ (\vysmblkcircle) in fips-197
# note: this naive implementation is faster when the first factor is smaller
# note: big crypto no-no, of course, to have the runtime of this dependent on the number...
# remember, this is a toy-implementation
function (∙)(a::UInt8, b::UInt8)
    r = 0x00
    while a != 0x00
        if a & 0x01 == 0x01
            r $= b
        end
        a >>= 1
        b = xtimes(b)
    end
    r
end

# Multiplication of two polynomials (each with degree < 4) modulo x^4 + 1, ⊗ (\otimes) in fips-197
function (⊗)(a::AbstractArray{UInt8,1}, b::AbstractArray{UInt8,1})
    length(a) == 4 || error("first argument of polynomial multplication (⊗) must have 4 bytes")
    length(b) == 4 || error("first argument of polynomial multplication (⊗) must have 4 bytes")
    d = Array(UInt8,4)
    d[1] = (a[1]∙b[1]) $ (a[4]∙b[2]) $ (a[3]∙b[3]) $ (a[2]∙b[4])
    d[2] = (a[2]∙b[1]) $ (a[1]∙b[2]) $ (a[4]∙b[3]) $ (a[3]∙b[4])
    d[3] = (a[3]∙b[1]) $ (a[2]∙b[2]) $ (a[1]∙b[3]) $ (a[4]∙b[4])
    d[4] = (a[4]∙b[1]) $ (a[3]∙b[2]) $ (a[2]∙b[3]) $ (a[1]∙b[4])
    d
end

function create_multiplication_table()
    mult_table = Array(UInt8,256,256)
    inv_table = zeros(UInt8,256)
    print("[0")
    for a = 0x00:0xff
        for b = 0x00:0xff
            mult_table[a+1,b+1] = a∙b
            if mult_table[a+1,b+1] == 0x01 # a∙b = 1, so b = a^(-1)
                inv_table[a+1] = b
                print(",",repr(b))
            end
        end
    end
    println("]")
    mult_table, inv_table
end

const inv_table = [0x00,0x01,0x8d,0xf6,0xcb,0x52,0x7b,0xd1,0xe8,0x4f,0x29,0xc0,0xb0,0xe1,0xe5,0xc7,
                   0x74,0xb4,0xaa,0x4b,0x99,0x2b,0x60,0x5f,0x58,0x3f,0xfd,0xcc,0xff,0x40,0xee,0xb2,
                   0x3a,0x6e,0x5a,0xf1,0x55,0x4d,0xa8,0xc9,0xc1,0x0a,0x98,0x15,0x30,0x44,0xa2,0xc2,
                   0x2c,0x45,0x92,0x6c,0xf3,0x39,0x66,0x42,0xf2,0x35,0x20,0x6f,0x77,0xbb,0x59,0x19,
                   0x1d,0xfe,0x37,0x67,0x2d,0x31,0xf5,0x69,0xa7,0x64,0xab,0x13,0x54,0x25,0xe9,0x09,
                   0xed,0x5c,0x05,0xca,0x4c,0x24,0x87,0xbf,0x18,0x3e,0x22,0xf0,0x51,0xec,0x61,0x17,
                   0x16,0x5e,0xaf,0xd3,0x49,0xa6,0x36,0x43,0xf4,0x47,0x91,0xdf,0x33,0x93,0x21,0x3b,
                   0x79,0xb7,0x97,0x85,0x10,0xb5,0xba,0x3c,0xb6,0x70,0xd0,0x06,0xa1,0xfa,0x81,0x82,
                   0x83,0x7e,0x7f,0x80,0x96,0x73,0xbe,0x56,0x9b,0x9e,0x95,0xd9,0xf7,0x02,0xb9,0xa4,
                   0xde,0x6a,0x32,0x6d,0xd8,0x8a,0x84,0x72,0x2a,0x14,0x9f,0x88,0xf9,0xdc,0x89,0x9a,
                   0xfb,0x7c,0x2e,0xc3,0x8f,0xb8,0x65,0x48,0x26,0xc8,0x12,0x4a,0xce,0xe7,0xd2,0x62,
                   0x0c,0xe0,0x1f,0xef,0x11,0x75,0x78,0x71,0xa5,0x8e,0x76,0x3d,0xbd,0xbc,0x86,0x57,
                   0x0b,0x28,0x2f,0xa3,0xda,0xd4,0xe4,0x0f,0xa9,0x27,0x53,0x04,0x1b,0xfc,0xac,0xe6,
                   0x7a,0x07,0xae,0x63,0xc5,0xdb,0xe2,0xea,0x94,0x8b,0xc4,0xd5,0x9d,0xf8,0x90,0x6b,
                   0xb1,0x0d,0xd6,0xeb,0xc6,0x0e,0xcf,0xad,0x08,0x4e,0xd7,0xe3,0x5d,0x50,0x1e,0xb3,
                   0x5b,0x23,0x38,0x34,0x68,0x46,0x03,0x8c,0xdd,0x9c,0x7d,0xa0,0xcd,0x1a,0x41,0x1c]

const Sbox_table = [0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76,
                    0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0,
                    0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15,
                    0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75,
                    0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84,
                    0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf,
                    0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8,
                    0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2,
                    0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73,
                    0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb,
                    0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79,
                    0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08,
                    0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a,
                    0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e,
                    0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf,
                    0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16]

const invSbox_table =
                    [0x52,0x09,0x6a,0xd5,0x30,0x36,0xa5,0x38,0xbf,0x40,0xa3,0x9e,0x81,0xf3,0xd7,0xfb,
                     0x7c,0xe3,0x39,0x82,0x9b,0x2f,0xff,0x87,0x34,0x8e,0x43,0x44,0xc4,0xde,0xe9,0xcb,
                     0x54,0x7b,0x94,0x32,0xa6,0xc2,0x23,0x3d,0xee,0x4c,0x95,0x0b,0x42,0xfa,0xc3,0x4e,
                     0x08,0x2e,0xa1,0x66,0x28,0xd9,0x24,0xb2,0x76,0x5b,0xa2,0x49,0x6d,0x8b,0xd1,0x25,
                     0x72,0xf8,0xf6,0x64,0x86,0x68,0x98,0x16,0xd4,0xa4,0x5c,0xcc,0x5d,0x65,0xb6,0x92,
                     0x6c,0x70,0x48,0x50,0xfd,0xed,0xb9,0xda,0x5e,0x15,0x46,0x57,0xa7,0x8d,0x9d,0x84,
                     0x90,0xd8,0xab,0x00,0x8c,0xbc,0xd3,0x0a,0xf7,0xe4,0x58,0x05,0xb8,0xb3,0x45,0x06,
                     0xd0,0x2c,0x1e,0x8f,0xca,0x3f,0x0f,0x02,0xc1,0xaf,0xbd,0x03,0x01,0x13,0x8a,0x6b,
                     0x3a,0x91,0x11,0x41,0x4f,0x67,0xdc,0xea,0x97,0xf2,0xcf,0xce,0xf0,0xb4,0xe6,0x73,
                     0x96,0xac,0x74,0x22,0xe7,0xad,0x35,0x85,0xe2,0xf9,0x37,0xe8,0x1c,0x75,0xdf,0x6e,
                     0x47,0xf1,0x1a,0x71,0x1d,0x29,0xc5,0x89,0x6f,0xb7,0x62,0x0e,0xaa,0x18,0xbe,0x1b,
                     0xfc,0x56,0x3e,0x4b,0xc6,0xd2,0x79,0x20,0x9a,0xdb,0xc0,0xfe,0x78,0xcd,0x5a,0xf4,
                     0x1f,0xdd,0xa8,0x33,0x88,0x07,0xc7,0x31,0xb1,0x12,0x10,0x59,0x27,0x80,0xec,0x5f,
                     0x60,0x51,0x7f,0xa9,0x19,0xb5,0x4a,0x0d,0x2d,0xe5,0x7a,0x9f,0x93,0xc9,0x9c,0xef,
                     0xa0,0xe0,0x3b,0x4d,0xae,0x2a,0xf5,0xb0,0xc8,0xeb,0xbb,0x3c,0x83,0x53,0x99,0x61,
                     0x17,0x2b,0x04,0x7e,0xba,0x77,0xd6,0x26,0xe1,0x69,0x14,0x63,0x55,0x21,0x0c,0x7d]

const Rcon = UInt32[0x01000000,0x02000000,0x04000000,0x08000000,0x10000000,0x20000000,0x40000000,0x80000000,
                    0x1b000000,0x36000000,0x6c000000,0xd8000000,0xab000000,0x4d000000,0x9a000000,0x2f000000]

const Rcon_b = UInt8[0x01,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x08,0x00,0x00,0x00,
                     0x10,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x80,0x00,0x00,0x00,
                     0x1b,0x00,0x00,0x00,0x36,0x00,0x00,0x00]



rotr1(x::UInt8) = (x>>1)|(x<<7)
rotr(x::UInt8,n) = (x>>n)|(x<<(8-n))
rotl1(x::UInt8) = (x<<1)|(x>>7)
rotl(x::UInt8,n) = (x<<n)|(x>>(8-n))

rotr1(x::UInt32) = (x>>1)|(x<<31)
rotr(x::UInt32,n) = (x>>n)|(x<<(32-n))
rotl1(x::UInt32) = (x<<1)|(x>>31)
rotl(x::UInt32,n) = (x<<n)|(x>>(32-n))

if ENDIAN_BOM == 0x04030201
    rotlittle = rotr
    word(b1::UInt8, b2::UInt8, b3::UInt8, b4::UInt8) = reinterpret(UInt32,[b4,b3,b2,b1])[1]
elseif ENDIAN_BOM == 0x01020304
    rotlittle = rotl
    word(b1::UInt8, b2::UInt8, b3::UInt8, b4::UInt8) = reinterpret(UInt32,[b1,b2,b3,b4])[1]
else
    error("what ENDIANness?")
end

function Sbox_slow(b::UInt8)
    b = inv_table[b+1]
    b_prime = 0x00
    mask = 0xf1
    c = 0x63
    for i = 0:7
        b_prime |= ((par(b & mask) $ (c & 0x01)) << i)
        mask = rotl1(mask)
        c = c>>1
    end
    b_prime
end

create_Sbox_table() = [Sbox_slow(b) for b in 0x00:0xff]

Sbox(b::UInt8) = Sbox_table[b+1]
invSbox(b::UInt8) = invSbox_table[b+1]

function subbytes!(state::AbstractArray{UInt8,1})
    for i in eachindex(state)
        @inbounds state[i] = Sbox(state[i])
    end
end

function invsubbytes!(state::AbstractArray{UInt8,1})
    for i in eachindex(state)
        @inbounds state[i] = invSbox(state[i])
    end
end

function subword!(wb::AbstractArray{UInt8,1})
    length(wb) == 4 || error("word must be 4 bytes")
    for i = 1:4
        wb[i] = Sbox(wb[i])
    end
end

function subword(w::UInt32)
    # this is ENDIAN independent... right?
    wb = reinterpret(UInt8,[w])
    subword!(wb)
    reinterpret(UInt32,wb)[1]
end

function shiftrows_old!(aes::AESBlock, state::AbstractArray{UInt8,1})
    length(state) == 4*aes.Nb || error("state must be 16 bytes")
    state32 = reinterpret(UInt32,state)
    @inbounds state32[2] = rotlittle(state32[2],8)
    @inbounds state32[3] = rotlittle(state32[3],16)
    @inbounds state32[4] = rotlittle(state32[4],24)
end

function shiftrows!(state::AbstractArray{UInt8,1})
    state[:] = state[[1,6,11,16,5,10,15,4,9,14,3,8,13,2,7,12]]
    # from
    #      1  5  9 13
    #      2  6 10 14
    #      3  7 11 15
    #      4  8 12 16
    # to
    #      1  5  9 13
    #      6 10 14  2
    #     11 15  3  7
    #     16  4  8 12
end

function invshiftrows!(state::AbstractArray{UInt8,1})
    state[:] = state[[1,14,11,8,5,2,15,12,9,6,3,16,13,10,7,4]]
    # from
    #      1  5  9 13
    #      2  6 10 14
    #      3  7 11 15
    #      4  8 12 16
    # to
    #      1  5  9 13
    #     14  2  6 10
    #     11 15  3  7
    #      8 12 16  4
end

function mixcolumn_slow!(col::AbstractArray{UInt8,1})
    length(col) == 4 || error("col must be 4 bytes")
    const a = [0x02, 0x01, 0x01, 0x03]
    col[:] = a ⊗ col
end

function invmixcolumn_slow!(col::AbstractArray{UInt8,1})
    length(col) == 4 || error("col must be 4 bytes")
    const ainv = [0x0e, 0x09, 0x0d, 0x0b]
    col[:] = ainv ⊗ col
end

function mixcolumn!(col::AbstractArray{UInt8,1})
    length(col) == 4 || error("col must be 4 bytes")
    c = copy(col)
    col[1] = xtimes(c[1]) $ (xtimes(c[2]) $ c[2]) $ c[3] $ c[4]
    col[2] = c[1] $ xtimes(c[2]) $ (xtimes(c[3]) $ c[3]) $ c[4]
    col[3] = c[1] $ c[2] $ xtimes(c[3]) $ (xtimes(c[4]) $ c[4])
    col[4] = (xtimes(c[1]) $ c[1]) $ c[2] $ c[3] $ xtimes(c[4])
end

# 1: b -> b (unchanged)
# 2: b -> bx (xtimes(b))
# 3: b -> b+bx (b $ xtimes(b))

function mixcolumns!(state::AbstractArray{UInt8,1})
    mixcolumn!(slice(state,1:4))
    mixcolumn!(slice(state,5:8))
    mixcolumn!(slice(state,9:12))
    mixcolumn!(slice(state,13:16))
end

function invmixcolumns!(state::AbstractArray{UInt8,1})
    invmixcolumn_slow!(slice(state,1:4))
    invmixcolumn_slow!(slice(state,5:8))
    invmixcolumn_slow!(slice(state,9:12))
    invmixcolumn_slow!(slice(state,13:16))
end

# AGENDA
# addroundkey(state, w)

rotword(w::UInt32) = rotl(w,8)
rotword(wb::AbstractArray{UInt8,1}) = wb[[2,3,4,1]]


# FIXFIXFIX: de-word (to circumvent endianness problems)
function create_rcon_word()
    m = 10 # the max Nb*(Nr+1)/Nk, Nk = 4: 4*11/4 = 11, Nk = 6: 4*13/6 = 9, 4*15/8
    rcon = Array(UInt32, m)
    power_of_x = 0x01
    for i = 1:m
        rcon[i] = word(power_of_x, 0x00, 0x00, 0x00)
        power_of_x = xtimes(power_of_x)
    end
    rcon
end

function create_rcon()
    m = 10 # the max Nb*(Nr+1)/Nk, Nk = 4: 4*11/4 = 11, Nk = 6: 4*13/6 = 9, 4*15/8
    rcon_b = zeros(UInt8, 4*m) # using bytes instead of 32 bit words
    power_of_x = 0x01
    for i = 1:m
        rcon_b[4i-3] = power_of_x
        power_of_x = xtimes(power_of_x)
    end
    rcon_b
end

function keyexpansion_word(aes::AESBlock) # result: ws::Array{UInt32,1} of length Nb*(Nr+1)
    const debug = false
    # key must be length Nk*4
    # ws must be length Nb*(Nr+1)

    w = Array(UInt32, aes.Nb*(aes.Nr+1))
    for ip = 1:aes.Nk
        w[ip] = word(aes.key[(4ip-3):(4ip)]...)
    end

    for i = (aes.Nk):(aes.Nb*(aes.Nr+1)-1)
        temp = w[i]
        debug && print("$i $(repr(temp)) ")
        if mod(i, aes.Nk) == 0
            temp = rotword(temp)
            debug && print("$(repr(temp)) ")
            temp = subword(temp)
            debug && print("$(repr(temp)) ")
            temp $= Rcon[div(i,aes.Nk)]
            debug && print("$(repr(Rcon[div(i,aes.Nk)])) ")
            debug && print("$(repr(temp)) ")
        elseif (aes.Nk > 6 && mod(i,aes.Nk) == 4)
            temp = subword(temp)
            debug && print("0x         ")
            debug && print("$(repr(temp)) ")
            debug && print("0x         ")
            debug && print("0x         ")
        else
            debug && print("0x         ")
            debug && print("0x         ")
            debug && print("0x         ")
            debug && print("0x         ")
        end
        debug && print("$(repr(w[i+1-aes.Nk])) ")
        w[i+1] = w[i+1-aes.Nk] $ temp
        debug && print("$(repr(w[i+1])) ")
        debug && println()
    end
    return w
end

function keyexpansion(aes::AESBlock) # result: ws::Array{UInt8,1} of length 4*Nb*(Nr+1)
    const debug = false
    # key must be length Nk*4
    # ws must be length Nb*(Nr+1)

    wb = Array(UInt8, 4*aes.Nb*(aes.Nr+1))
    wb[1:(4*aes.Nk)] = aes.key[1:(4*aes.Nk)]

    # w[i] = wb[4i-3 : 4i]
    for i = (aes.Nk):(aes.Nb*(aes.Nr+1)-1)
        temp = wb[(4i-3):4i]
        debug && print("$i $(repr(temp)) ")
        if mod(i, aes.Nk) == 0
            temp = rotword(temp)
            debug && print("$(repr(temp)) ")
            subword!(temp)
            debug && print("$(repr(temp)) ")
            temp $= Rcon_b[(4*div(i,aes.Nk)-3):(4*div(i,aes.Nk))] # note: 4*i/4, might remove
            debug && print("$(repr(Rcon_b[(4*div(i,aes.Nk)-3):(4*div(i,aes.Nk))])) ")
            debug && print("$(repr(temp)) ")
        elseif (aes.Nk > 6 && mod(i,aes.Nk) == 4)
            subword!(temp)
            debug && print("0x         ")
            debug && print("$(repr(temp)) ")
            debug && print("0x         ")
            debug && print("0x         ")
        else
            debug && print("0x         ")
            debug && print("0x         ")
            debug && print("0x         ")
            debug && print("0x         ")
        end
        debug && print("$(repr(wb[(4(i-aes.Nk)+1):(4(i-aes.Nk)+4)])) ")
        wb[(4i+1):(4(i+1))] = wb[(4(i-aes.Nk)+1):(4(i-aes.Nk)+4)] $ temp
        debug && print("$(repr(wb[(4i+1):(4(i+1))])) ")
        debug && println()
    end
    return wb
end


addroundkey!(state, roundkey) = state[:] $= roundkey

function encipher_block!(aes::AESBlock, plaintext::AbstractArray{UInt8,1})
    const debug = false
    length(plaintext) == blocklength_bytes(aes) || error("plaintext wrong length $(length(plaintext)), should be $(blocklength_bytes(aes)).")
    state = plaintext # FIXFIXFIX
    debug && println("fresh state:   $(repr(state))")
    wb = keyexpansion(aes)
    addroundkey!(state, wb[1:(4*aes.Nb)])
    debug && println("    round key: $(repr(wb[1:(4*aes.Nb)]))")
    debug && println("add round key: $(repr(state))")
    for k = 1:(aes.Nr-1)
        subbytes!(state)
        debug && println("r $k subbytes:  $(repr(state))")
        shiftrows!(state)
        debug && println("r $k shiftrows: $(repr(state))")
        mixcolumns!(state)
        debug && println("r $k mixcolums: $(repr(state))")
        #       addroundkey!(state,  w[ (aes.Nb*k + 1) :(  aes.Nb*(k+1)) ] )
        addroundkey!(state, wb[ (4*aes.Nb*k +1):(4*aes.Nb*(k+1)) ] )
        debug && println("r $k    rk:     $(repr(wb[ (4*aes.Nb*k +1):(4*aes.Nb*(k+1)) ]))")
        debug && println("r $k addrk:     $(repr(state))")
    end
    subbytes!(state)
    debug && println("finalsubbytes: $(repr(state))")
    shiftrows!(state)
    debug && println("finalshiftrow: $(repr(state))")
    addroundkey!(state, wb[(4*aes.Nb*aes.Nr + 1):(4*aes.Nb*(aes.Nr+1))])
    debug && println("final     rk:  $(repr(wb[(4*aes.Nb*aes.Nr + 1):(4*aes.Nb*(aes.Nr+1))]))")
    debug && println("final add rk:  $(repr(state))")

    state
end

encipher_block(aes, plaintext) = encipher_block!(aes, copy(plaintext))


function decipher_block!(aes::AESBlock, plaintext::AbstractArray{UInt8,1})
   # const debug = false
    length(plaintext) == blocklength_bytes(aes) || error("plaintext wrong length $(length(plaintext)), should be $(blocklength_bytes(aes)).")
    state = plaintext # FIXFIXFIX
   # debug && println("fresh state:   $(repr(state))")
    wb = keyexpansion(aes)
    addroundkey!(state, wb[ (4*aes.Nr*aes.Nb+1):(4*(aes.Nr+1)*aes.Nb) ])
   # debug && println("    round key: $(repr(wb[ (4*aes.Nr*aes.Nb+1):(4*(aes.Nr+1)*aes.Nb) ]))")
   # debug && println("add round key: $(repr(state))")
    for k = (aes.Nr-1):-1:1
        invshiftrows!(state)
#        debug && println("r $k shiftrows: $(repr(state))")
        invsubbytes!(state)
#        debug && println("r $k subbytes:  $(repr(state))")
        addroundkey!(state, wb[ (4*aes.Nb*k +1):(4*aes.Nb*(k+1)) ] )
#         debug && println("r $k    rk:     $(repr(wb[ (4*aes.Nb*k +1):(4*aes.Nb*(k+1)) ]))")
#         debug && println("r $k addrk:     $(repr(state))")
        invmixcolumns!(state)
#         debug && println("r $k mixcolums: $(repr(state))")

    end
    invshiftrows!(state)
    #        debug && println("finalshiftrows: $(repr(state))")
    invsubbytes!(state)

    #        debug && println("finalsubbytes:  $(repr(state))")
    addroundkey!(state, wb[1:(4*aes.Nb)])
    # debug && println("final     rk:  $(repr(wb[ 1 :(4*aes.Nb) ]))")
    # debug && println("final add rk:  $(repr(state))")

    state
end

decipher_block(aes, ciphertext) = decipher_block!(aes, copy(ciphertext))

#########################
# Blockmodes
#########################

type Blockmode_ECB <: Blockmode
end

type Blockmode_CBC <: Blockmode
    IV :: AbstractArray{UInt8,1}
end

# ECB
# C_i = E(K, P_i)
function encipher_blocks!(blocks, bm::Blockmode_ECB, bc::Blockcipher)
    for i = 1:size(blocks, 2)
        encipher_block!(bc, sub(blocks, :, i ) )
    end
    blocks
end

# P_i = D(K, C_i)
function decipher_blocks!(blocks, bm::Blockmode_ECB, bc::Blockcipher)
    for i = 1:size(blocks, 2)
        decipher_block!(bc, sub(blocks, :, i) )
    end
    blocks
end

# CBC
# C_i = E(K, P_i xor C_{i-1}), with C_0 := IV
function encipher_blocks!(blocks, bm::Blockmode_CBC, bc::Blockcipher)
    length(bm.IV) == size(blocks,1) || error("plaintext wrong length")

    C_im1 = bm.IV
    for i = 1:size(blocks, 2)
        block = sub(blocks, :, i)
#         println("initial p ", block)
        block[:] $= C_im1
#         println("after xor ", block)
        encipher_block!(bc, block )
#         println("after enc ", block)
        C_im1 = block
    end
#     println("finally ", blocks)
    blocks
end

# P_i = D(K, C_i) xor C_{i-1}, with C_0 := IV
function decipher_blocks!(blocks, bm::Blockmode_CBC, bc::Blockcipher)
    length(bm.IV) == size(blocks,1) || error("plaintext wrong length")

    for i = size(blocks, 2):-1:1
        block = sub(blocks, :, i)
#         println("initial c ", block)
        decipher_block!(bc, block )
#         println("after dec ", block)
        if i > 1
            C_im1 = blocks[:, i-1]
        else
            C_im1 = bm.IV
        end
        block[:] $= C_im1
#         println("after xor ", block)
    end
    blocks
end

# blocklength_bytes(aes::AESBlock) = 16

function encipher(cipher::Cipher, plaintext)
    # pad
    plaintext_padded = Crypto101.pad(cipher.padder, plaintext)

    # check dimensions
    blocklength = blocklength_bytes(cipher.blockcipher)
    numblocks, extra = divrem(length(plaintext_padded), blocklength)
    extra == 0 || error("padded plaintext wrong length")

    # reshape, encrypt blocks
    blocks = reshape(plaintext_padded, (blocklength, numblocks)) # every column is a block
    encipher_blocks!(blocks, cipher.blockmode, cipher.blockcipher)
    return vec(blocks)
end

function decipher(cipher::Cipher, ciphertext)
    # check dimensions
    blocklength = blocklength_bytes(cipher.blockcipher)
    numblocks, extra = divrem(length(ciphertext), blocklength)
    extra == 0 || error("ciphertext wrong length")

    # reshape, decrypt blocks
    blocks = reshape(ciphertext, (blocklength, numblocks)) # every column is a block
    decipher_blocks!(blocks, cipher.blockmode, cipher.blockcipher)

    # unpad
    plaintext = Crypto101.unpad(cipher.padder, vec(blocks))
end

end
