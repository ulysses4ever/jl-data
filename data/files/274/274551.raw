# Pure Julia implementation of decompression of zlib and gzip
# compressed data, as specified by RFC 1950-1952.
# Author: Gunnar Farneback
# See https://groups.google.com/forum/#!searchin/julia-users/decompress/julia-users/HbyFaJjfSs0/IhI1oqYbAtEJs
#
# A small change by NJWalker to take into account concatenated gzips
#

# Huffman codes are internally represented by Vector{Vector{Int}},
# where code[k] are a vector of the values with code words of length
# k. Codes are assigned in order from shorter to longer codes and in
# the order listed. E.g.
# [[], [2, 7], [1, 3, 5], [6, 4]]
# would be the code
# 00    - 2
# 01    - 7
# 100   - 1
# 101   - 3
# 110   - 5
# 1110  - 6
# 1111  - 4

const fixed_literal_or_length_table = (Vector{Int})[Int[],
                                                    Int[],
                                                    Int[],
                                                    Int[],
                                                    Int[],
                                                    Int[],
				                    Int[256:279],
				                    Int[0:143, 280:287],
				                    Int[144:255]]

const fixed_distance_table = (Vector{Int})[Int[],
                                           Int[],
                                           Int[],
                                           Int[],
                                           Int[0:31]]

type InflateData
    bytes::Vector{Uint8}
    current_byte::Int
    bytepos::Int
    bitpos::Int
    literal_or_length_code::Vector{Vector{Int}}
    distance_code::Vector{Vector{Int}}
end

function InflateData(source::Vector{Uint8})
    InflateData(source, 0, 1, 0, fixed_literal_or_length_table, fixed_distance_table)
end

function getbit(in::InflateData)
    if in.bitpos == 0
        in.current_byte = int(in.bytes[in.bytepos])
    end
    b = in.current_byte & 1
    in.bitpos += 1
    if in.bitpos == 8
        in.bitpos = 0
        in.bytepos += 1
    else
        in.current_byte >>= 1
    end
    b
end

function getbits(in::InflateData, n::Int)
    b = 0
    for i = 0:(n-1)
        b |= getbit(in) << i
    end
    b
end

function skip_bits_to_byte_boundary(in::InflateData)
    if in.bitpos > 0
        in.bytepos += 1
        in.bitpos = 0
    end
    nothing
end

# It is the responsibility of the caller to make sure that bitpos is
# at zero, e.g. by calling skip_bits_to_byte_boundary.
function get_aligned_byte(in::InflateData)
    byte = in.bytes[in.bytepos]
    in.bytepos += 1
    byte
end

function get_value_from_code(in::InflateData, code::Vector{Vector{Int}})
    v = 0
    for i = 1:length(code)
        v = (v << 1) | getbit(in)
        if v < length(code[i])
            return code[i][1 + v]
        end
        v -= length(code[i])
    end
    throw("incomplete code table")
end

get_literal_or_length(in) = get_value_from_code(in, in.literal_or_length_code)

const base_length = [11, 13, 15, 17, 19, 23, 27, 31, 35, 43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227]
const extra_length_bits = [1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5]

function getlength(in::InflateData, v::Int)
    if v <= 264
        return v - 254
    elseif v <= 284
        return base_length[v - 264] + getbits(in, extra_length_bits[v - 264])
    else
        return 258
    end
end

function getdist(in::InflateData)
    b = get_value_from_code(in, in.distance_code)
    if b <= 3
        return b + 1
    else
        extra_bits = fld(b - 2, 2)
        return 1 + ((2 + b % 2) << extra_bits) + getbits(in, extra_bits)
    end
end

function transform_code_lengths_to_code(code_lengths::Vector{Int})
    code = Vector{Int}[]
    for i = 1:length(code_lengths)
        n = code_lengths[i]
        if n > 0
            while n > length(code)
                push!(code, Int[])
            end
            push!(code[n], i - 1)
        end
    end
    return code
end

const order = [16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15]

function read_code_tables(in::InflateData)
    hlit = getbits(in, 5) + 257
    hdist = getbits(in, 5) + 1
    hclen = getbits(in, 4) + 4
    code_length_code_lengths = zeros(Int, 19)
    for i = 1:hclen
        code_length_code_lengths[1 + order[i]] = getbits(in, 3)
    end
    code_length_code = transform_code_lengths_to_code(code_length_code_lengths)
    code_lengths = zeros(Int, hlit + hdist)
    i = 1
    while i <= hlit + hdist
        c = get_value_from_code(in, code_length_code)
        n = 1
        l = 0
        if c < 16
            l = c
        elseif c == 16
            n = 3 + getbits(in, 2)
            l = code_lengths[i-1]
        elseif c == 17
            n = 3 + getbits(in, 3)
        elseif c == 18
            n = 11 + getbits(in, 7)
        else
            throw("invalid code length code")
        end
        code_lengths[i:(i+n-1)] = l
        i += n
    end
    in.literal_or_length_code = transform_code_lengths_to_code(code_lengths[1:hlit])
    in.distance_code = transform_code_lengths_to_code(code_lengths[(hlit+1):end])
end
# Decompress data given in deflate format, as specified by RFC 1951.
function inflate(in::InflateData)
    dest = Uint8[]
    final = false
    while !final
        final = getbits(in, 1) == 1
        compression_mode = getbits(in, 2)
        if compression_mode == 0
            skip_bits_to_byte_boundary(in)
            len = getbits(in, 16)
            nlen = getbits(in, 16)
            if len $ nlen != 0xffff
                throw("corrupted data")
            end
            for i = 1:len
                push!(dest, get_aligned_byte(in))
            end
            continue
        elseif compression_mode == 1
            in.literal_or_length_code = fixed_literal_or_length_table
            in.distance_code = fixed_distance_table
        elseif compression_mode == 2
	    read_code_tables(in)
        else
            throw("invalid block compression mode 3")
        end

        while true
            v = get_literal_or_length(in)
            if v < 256
                push!(dest, uint8(v))
            elseif v == 256
                break
            else
                length = getlength(in, v)
                distance = getdist(in)
                for i = 1:length
                    push!(dest, dest[end - distance + 1])
                end
            end
        end
    end

    return dest
end

function compute_adler_checksum(x::Vector{Uint8})
    s1 = 1
    s2 = 0
    for b in x
        s1 += b
        if s1 >= 65521
            s1 -= 65521
        end
        s2 += s1
        if s2 >= 65521
            s2 -= 65521
        end
    end
    return (s2 << 16) | s1
end

const crc_table = zeros(Uint32, 256)

function make_crc_table()
    for n = 1:256
        c = uint32(n - 1)
        for k = 1:8
            if bool(c & 0x00000001)
                c = 0xedb88320 $ (c >> 1)
            else
                c >>= 1
            end
        end
        crc_table[n] = c
    end
end

function crc(x::Vector{Uint8})
    if crc_table[1] == 0
        make_crc_table()
    end
    c = 0xffffffff
    for b in x
        c = crc_table[1 + ((c $ b) & 0xff)] $ (c >> 8)
    end
    c $ 0xffffffff
end

function read_zero_terminated_data(in)
    s = Uint8[]
    while true
        c = get_aligned_byte(in)
        push!(s, c)
        if c == 0
            break
        end
    end
end

# Decompress Zlib compressed data, as specified by RFC 1950.
function decompress(source::Vector{Uint8})
    in = InflateData(source)

    CMF = get_aligned_byte(in)
    FLG = get_aligned_byte(in)
    CM = CMF & 0x0f
    CINFO = CM >> 4
    FLEVEL = FLG >> 6
    FDICT = (FLG >> 5) & 0x01
    if CM != 8
        throw("unsupported compression method")
    end
    if CINFO > 7
        throw("invalid LZ77 window size")
    end
    if FDICT != 0
        throw("preset dictionary not supported")
    end
    if mod((uint(CMF) << 8) | FLG, 31) != 0
        throw("header checksum error")
    end

    dest = inflate(in)

    skip_bits_to_byte_boundary(in)
    ADLER = 0
    for i = [24, 16, 8, 0]
        ADLER |= int(get_aligned_byte(in)) << i
    end
    if compute_adler_checksum(dest) != ADLER
        throw("corrupted data")
    end

    dest
end

# Decompress GZIP compressed data, as specified by RFC 1952.

function check_gunzip_block_header( in::InflateData )
    ID1 = get_aligned_byte(in)
    ID2 = get_aligned_byte(in)
    if ID1 != 0x1f || ID2 != 0x8b
        throw("not gzipped data")
    end
    CM = get_aligned_byte(in)
    if CM != 8
        throw("unsupported compression method")
    end
    FLG = get_aligned_byte(in)
    MTIME = getbits(in, 32)
    XFL = get_aligned_byte(in)
    OS = get_aligned_byte(in)

    if bool(FLG & 0x04)
        # FLG.FEXTRA
        xlen = getbits(in, 16)
        in.bytepos += xlen
    end

    if bool(FLG & 0x08)
        # FLG.FNAME
        name = read_zero_terminated_data(in)
    end

    if bool(FLG & 0x10)
        # FLG.FCOMMENT
        comment = read_zero_terminated_data(in)
    end

    if bool(FLG & 0x02)
        # FLG.FHCRC
        crc16 = getbits(in, 16)
        if check_crc && crc16 != (crc(in.bytes[1:(in.bytepos-3)]) & 0xffff)
            throw("corrupted data, header crc check failed")
        end
    end
end

function check_gunzip_block_tail(in::InflateData,dest::Vector{Uint8}; check_crc::Bool = true)
    skip_bits_to_byte_boundary(in)
    crc32 = getbits(in, 32)
    if check_crc && crc32 != crc(dest)
        throw("corrupted data, crc check failed")
    end
    isize = getbits(in, 32)
    if isize != length(dest)
        throw("corrupted data, length check failed")
    end
end

function gunzip( source::Vector{Uint8}; check_crc::Bool = true)
    in = InflateData(source)
    destall = Uint8[]
    while in.bytepos < length(source)
        check_gunzip_block_header(in)
        dest=inflate(in)
        append!(destall,dest)
        check_gunzip_block_tail(in,dest,check_crc=check_crc)
    end
    return destall
end

function gunzip_old(source::Vector{Uint8}; check_crc::Bool = true)
    in = InflateData(source)

    ID1 = get_aligned_byte(in)
    ID2 = get_aligned_byte(in)
    if ID1 != 0x1f || ID2 != 0x8b
        throw("not gzipped data")
    end
    CM = get_aligned_byte(in)
    if CM != 8
        throw("unsupported compression method")
    end
    FLG = get_aligned_byte(in)
    MTIME = getbits(in, 32)
    XFL = get_aligned_byte(in)
    OS = get_aligned_byte(in)

    if bool(FLG & 0x04)
        # FLG.FEXTRA
        xlen = getbits(in, 16)
        in.bytepos += xlen
    end

    if bool(FLG & 0x08)
        # FLG.FNAME
        name = read_zero_terminated_data(in)
    end

    if bool(FLG & 0x10)
        # FLG.FCOMMENT
        comment = read_zero_terminated_data(in)
    end

    if bool(FLG & 0x02)
        # FLG.FHCRC
        crc16 = getbits(in, 16)
        if check_crc && crc16 != (crc(in.bytes[1:(in.bytepos-3)]) & 0xffff)
            throw("corrupted data, header crc check failed")
        end
    end

    dest = inflate(in)

    skip_bits_to_byte_boundary(in)
    crc32 = getbits(in, 32)
    if check_crc && crc32 != crc(dest)
        throw("corrupted data, crc check failed")
    end
    isize = getbits(in, 32)
    if isize != length(dest)
        throw("corrupted data, length check failed")
    end

    dest
end
