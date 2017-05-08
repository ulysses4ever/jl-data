const kDoubleSignificandSize = int32(53)    # Includes the hidden bit.

function FillDigits32FixedLength(n1::Uint32,requested_len::Int,buffer,len::Int32)
    # assumes len is valid index
    len::Int32
    for i = (requested_len-1):-1:0
        buffer[len+i] = 0x30 + n1 % 10
        n1::Uint32 = div(n1,10)
    end
    return int32(len + requested_len)
end

function FillDigits32(n::Uint32,buffer,len::Int32)
    # assumes len is valid index
    n::Uint32; len::Int32
    n_len#=::Int32=# = int32(0)
    while n != 0
        digit#=::Int32=# = int32(n % 10)
        n = div(n,10)
        buffer[len+n_len] = 0x30 + digit
        n_len += 1
    end
    i,j = len, len + n_len - 1
    while i < j
        buffer[i], buffer[j] = buffer[j], buffer[i]
        i += 1
        j -= 1
    end
    return int32(len + n_len)
end

function FillDigits64FixedLength(n2::Uint64,buffer,len::Int32)
    # assumes len is valid index
    len::Int32
    kTen7::Uint32 = 10000000
    part2::Uint32 = n2 % kTen7
    n2 = div(n2,kTen7)
    part0::Uint32, part1::Uint32 = divrem(n2,kTen7)
    len = FillDigits32FixedLength(part0, 3, buffer, len)
    len = FillDigits32FixedLength(part1, 7, buffer, len)
    len = FillDigits32FixedLength(part2, 7, buffer, len)
    return len
end

function FillDigits64(n3::Uint64,buffer,len::Int32)
    # assumes len is valid index
    len::Int32
    kTen7#=::Uint32=# = uint32(10000000)
    part2#=::Uint32=# = uint32(n3 % kTen7)
    n3 = div(n3,kTen7)
    part0#=::Uint32=#, part1#=::Uint32=# = divrem(n3,kTen7)
    if part0 != 0
        len = FillDigits32(uint32(part0), buffer, len)
        len = FillDigits32FixedLength(uint32(part1), 7, buffer, len)
        len = FillDigits32FixedLength(uint32(part2), 7, buffer, len)
    elseif part1 != 0
        len = FillDigits32(uint32(part1), buffer, len)
        len = FillDigits32FixedLength(uint32(part2), 7, buffer, len)
    else
        len = FillDigits32(uint32(part2), buffer, len)
    end
    return len
end

function RoundUp(buffer, len::Int32, decimal_point::Int32)
    # assumes len is valid index
    len::Int32
    if len == 1
        buffer[1] = 0x31
        decimal_point = int32(1)
        len = int32(2) #might be wrong
        return len, decimal_point
    end
    buffer[len - 1] += 1
    for i = (len-1):-1:2
        buffer[i] != 0x30 + 10 && return len, decimal_point
        buffer[i] = 0x30
        buffer[i - 1] += 1
    end
    if buffer[1] == 0x30 + 10
        buffer[1] = 0x31
        decimal_point += 1
    end
    return len, int32(decimal_point)
end

function FillFractionals(fractionals::Uint64, exponent::Int32,
                         fractional_count::Int, buffer,
                         len::Int32, decimal_point::Int32)
    # assumes len is valid index
    len::Int32
    @assert(-128 <= exponent && exponent <= 0)
    if -exponent <= 64
        @assert(fractionals >> 56 == 0)
        point#=::Int32=# = int32(-exponent)
        for i = 1:fractional_count
            fractionals == 0 && break
            fractionals *= 5
            point -= 1
            digit#=::Int32=# = int32(fractionals >> point)
            @assert(digit <= 9)
            buffer[len] = 0x30 + digit
            len += 1
            fractionals::Uint64 -= uint64(digit) << point
        end
        if ((fractionals >> (point - 1)) & 1) == 1
            len, decimal_point = RoundUp(buffer, len, decimal_point)
        end
    else
        @assert(64 < -exponent && -exponent <= 128)
        fract128#=::Uint128=# = uint128(fractionals) << 64 #check
        fract128 = shift(fract128,-exponent - 64)
        point = 128
        for i = 1:fractional_count
            fract128 == 0 && break
            fract128 *= 5
            point -= 1
            digit, fract128 = divrem2(fract128,point)
            @assert(digit <= 9)
            buffer[len] = 0x30 + digit
            len += 1
        end
        if bitat(fract128,point - 1) == 1
            len, decimal_point = RoundUp(buffer, len, decimal_point)
        end
    end
    return len, decimal_point
end

low(x) = uint64(x)
high(x) = uint64(x >> 64)
bitat(x::Uint128,y) = y >= 64 ? (int32(high(x) >> (y-64)) & 1) : (int32(low(x) >> y) & 1)
function divrem2(x,power)
    h = high(x)
    l = low(x)
    if power >= 64
        result = int32(h >> (power - 64))
        h -= uint64(result) << (power - 64)
        return result, (uint128(h) << 64) + l
    else
        part_low::Uint64 = l >> power
        part_high::Uint64 = h << (64 - power)
        result = int32(part_low + part_high)
        return result, uint128(l - (part_low << power))
    end
end
function shift(x::Uint128,amt)
    if amt == 0
      return x
    elseif amt == -64
        return x << 64
    elseif amt == 64
        return x >> 64
    elseif amt <= 0
        h = high(x); l = low(x)
        h <<= -amt
        h += l >> (64 + amt)
        l <<= -amt
        return (uint128(h) << 64) + l
    else
        h = high(x); l = low(x)
        l >>= amt
        l += h << (64 - amt)
        h >>= amt
        return (uint128(h) << 64) + l
    end
end

function TrimZeros(buffer, len::Int32, decimal_point::Int32)
    # assumes len is valid index
    len::Int32
    while len > 1 && buffer[len - 1] == 0x30
        len -= 1
    end
    first_non_zero#=::Int32=# = int32(1)
    while first_non_zero < len && buffer[first_non_zero] == 0x30
        first_non_zero += 1
    end
    if first_non_zero != 1
        for i = first_non_zero:(len-1) # len-1?
            buffer[i - first_non_zero + 1] = buffer[i]
        end
        len -= first_non_zero-1
        decimal_point -= first_non_zero-1
    end
    return len, decimal_point
end

function fastfixedtoa(v,fractional_count,buffer)
    v = float64(v)
    kMaxUInt32#=::Uint32=# = uint32(0xFFFFFFFF)
    significand#=::Uint64=# = _significand(v)
    exponent#=::Int32=# = _exponent(v)
    exponent > 20 && return false, 0, buffer
    fractional_count > 20 && return false, 0, buffer
    len#=::Int32=# = int32(1)
    if exponent + kDoubleSignificandSize > 64
        kFive17::Uint64 = divisor::Uint64 = uint64(5^17)
        divisor_power::Int32 = 17
        dividend::Uint64 = significand
        if exponent > divisor_power
            dividend <<= exponent - divisor_power
            quotient::Uint32 = div(dividend,divisor)
            remainder::Uint64 = (dividend % divisor) << divisor_power
        else
            divisor <<= divisor_power - exponent
            quotient = div(dividend,divisor)
            remainder = (dividend % divisor) << exponent
        end
        len = FillDigits32(quotient, buffer, len)
        len = FillDigits64FixedLength(remainder, buffer, len)
        decimal_point = int32(len-1)
    elseif exponent >= 0
        significand <<= exponent
        len = FillDigits64(significand, buffer, len)
        decimal_point = int32(len-1)
    elseif exponent > -kDoubleSignificandSize
        integrals#=::Uint64=# = uint64(significand >> -exponent)
        fractionals#=::Uint64=# = uint64(significand - (integrals << -exponent))
        if integrals > kMaxUInt32
            len = FillDigits64(integrals,buffer,len)
        else
            len = FillDigits32(uint32(integrals),buffer,len)
        end
        decimal_point = int32(len-1)
        len, decimal_point = FillFractionals(fractionals,exponent,fractional_count,
                                                    buffer,len, decimal_point)
    elseif exponent < -128
        len = int32(1)
        decimal_point = int32(-fractional_count)
    else
        decimal_point = int32(0)
        len, decimal_point = FillFractionals(significand,exponent,fractional_count,
                                                    buffer,len, decimal_point)
    end
    len, decimal_point = TrimZeros(buffer,len,decimal_point)
    buffer[len] = 0
    if (len-1) == 0
        decimal_point = -fractional_count
    end
    return len, decimal_point, buffer
end