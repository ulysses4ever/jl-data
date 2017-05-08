const BIGNUM_DTOA_SHORTEST = 1
const BIGNUM_DTOA_SHORTEST_SINGLE = 2
const BIGNUM_DTOA_FIXED = 3
const BIGNUM_DTOA_PRECISION = 4

function NormalizedExponent(significand::Uint64, exponent::Int32)
    @assert(significand != 0)
    while (significand & HiddenBit(Float64)) == 0
        significand::Uint64 <<= 1
        exponent -= 1
    end
    return int32(exponent)
end

function bignumdtoa(v,mode,requested_digits::Int,buffer)
    @assert(v > 0)
    significand::Uint64
    exponent::Int32
    lower_boundary_is_closer::Bool
    if mode == BIGNUM_DTOA_SHORTEST_SINGLE
        f = float32(v)
        @assert(f == v)
        significand = _significand(f)
        exponent = _exponent(f)
        lower_boundary_is_closer = lowerboundaryiscloser(f)
    else
        significand = _significand(v)
        exponent = _exponent(v)
        lower_boundary_is_closer = lowerboundaryiscloser(v)
    end
    need_boundary_deltas =
            (mode == BIGNUM_DTOA_SHORTEST || mode == BIGNUM_DTOA_SHORTEST_SINGLE)

    is_even = (significand & 1) == 0
    normalized_exponent = NormalizedExponent(significand, exponent)
    estimated_power = EstimatePower(normalized_exponent)

    if mode == BIGNUM_DTOA_FIXED && -estimated_power - 1 > requested_digits
        buffer[1] = 0
        len = 1
        decimal_point = -requested_digits
        return len, decimal_point, buffer
    end
    num = den = minus = plus = BigInt(0)
    num, den, minus, plus = InitialScaledStartValues(significand,exponent,lower_boundary_is_closer,
                              estimated_power,need_boundary_deltas,
                              num,den,minus,plus);
    num, den, minus, plus, decimal_point = FixupMultiply10(
        estimated_power,is_even,num,den,minus,plus);

    if mode == BIGNUM_DTOA_SHORTEST || mode == BIGNUM_DTOA_SHORTEST_SINGLE
        len, buffer = GenerateShortestDigits(num,den,minus,plus,is_even,buffer)
    elseif mode == BIGNUM_DTOA_FIXED
        len, decimal_point, buffer = BignumToFixed(requested_digits,num,den,buffer,decimal_point)
    elseif mode == BIGNUM_DTOA_PRECISION
        len, decimal_point, buffer = GenerateCountedDigits(requested_digits,num,den,buffer,decimal_point)
    end
    buffer[len] = 0
    return len, decimal_point, buffer
end

function GenerateShortestDigits(num,den,minus,plus,is_even,buffer)
    len = 1
    while true
        digit#=::Uint16=#, num = divrem(num,den)
        buffer[len] = 0x30 + digit
        len += 1
        in_delta_room_minus = is_even ? num <= minus : num < minus
        in_delta_room_plus = is_even ? num + plus >= den : num + plus > den
        
        if !in_delta_room_minus && !in_delta_room_plus
            num *= 10
            minus *= 10
            if minus != plus
                plus *= 10
            end
        elseif in_delta_room_minus && in_delta_room_plus
            compare = num + num
            if compare < den
            elseif compare > den
                @assert(buffer[len - 1] != 0x39)
                buffer[len - 1] += 1
            else
                if (buffer[len - 1] - 0x30) % 2 == 0
                else
                    @assert(buffer[len - 1] != 0x39)
                    buffer[len - 1] += 1
                end
            end
            return len, buffer
        elseif in_delta_room_minus
            return len, buffer
        else
            buffer[len - 1] += 1
            return len, buffer
        end
    end
end


function GenerateCountedDigits(count,num,den,buffer,decimal_point)
    # assume count is 1-indexed
    @assert(count >= 0)
    digit::Uint16
    for i = 1:(count-1)
        digit, num = divrem(num,den)
        buffer[i] = 0x30 + digit
        num *= 10
    end
    digit, num = divrem(num,den)
    if num + num >= den
        digit += 1
    end
    @assert(digit <= 10)
    buffer[count] = 0x30 + digit
    for i = count:-1:2
        buffer[i] != 0x30 + 10 && break
        buffer[i] = 0x30
        buffer[i - 1] += 1
    end
    if buffer[1] == 0x30 + 10
        buffer[1] = 0x31
        decimal_point += int32(1)
    end
    len = count+1
    return len, decimal_point, buffer
end

function BignumToFixed(requested_digits,num,den,buffer,decimal_point)
    if -decimal_point > requested_digits
        decimal_point::Int32 = -requested_digits
        len = 1
        return len, decimal_point, buffer
    elseif -decimal_point == requested_digits
        den *= 10
        if num + num >= den
            buffer[1] = 0x31
            len = 2
            decimal_point += 1
        else
            len = 1
        end
        return len, decimal_point, buffer
    else
        needed_digits#=::Int32=# = decimal_point + requested_digits
        len, decimal_point, buffer = GenerateCountedDigits(
              needed_digits,num,den,buffer,decimal_point)
    end
    return len, decimal_point, buffer
end


function EstimatePower(exponent::Int32)
    k1Log10 = 0.30102999566398114
    kSignificandSize::Int32 = SignificandSize(Float64)
    estimate = ceil((exponent + kSignificandSize - 1) * k1Log10 - 1e-10)
    return int32(estimate)
end


function InitialScaledStartValuesPositiveExponent(
        significand::Uint64, exponent::Int32,
        estimated_power::Int32, need_boundary_deltas::Bool,
        num,den,minus,plus)
    @assert(estimated_power >= 0)
    num::BigInt = BigInt(significand)
    num <<= exponent
    den::BigInt = BigInt(10)^estimated_power
    if need_boundary_deltas
        den <<= 1
        num <<= 1
        plus::BigInt = BigInt(1)
        plus <<= exponent
        minus::BigInt = BigInt(1)
        minus <<= exponent
    end
    return num, den, minus, plus
end


function InitialScaledStartValuesNegativeExponentPositivePower(
        significand::Uint64, exponent::Int32,
        estimated_power::Int32, need_boundary_deltas::Bool,
        num,den,minus,plus)
    num::BigInt = BigInt(significand)
    den::BigInt = BigInt(10)^estimated_power
    den <<= -exponent
    if need_boundary_deltas
        den <<= 1
        num <<= 1
        plus::BigInt = 1
        minus::BigInt = 1
    end
    return num, den, minus, plus
end

function InitialScaledStartValuesNegativeExponentNegativePower(
        significand::Uint64, exponent::Int32,
        estimated_power::Int32, need_boundary_deltas::Bool,
        num,den,minus,plus)
    num#=::BigInt=# = BigInt(10)^-estimated_power
    if need_boundary_deltas
        plus = num
        minus = num
    end
    num *= significand
    den::BigInt = BigInt(1)
    den <<= -exponent
    if need_boundary_deltas
        num <<= 1
        den <<= 1
    end
    return num, den, minus, plus
end

function InitialScaledStartValues(significand::Uint64,
            exponent,lower_boundary_is_closer,estimated_power,
            need_boundary_deltas,num,den,minus,plus)
    if exponent >= 0
        num,den,minus,plus = InitialScaledStartValuesPositiveExponent(
                significand, exponent, estimated_power, need_boundary_deltas,
                num,den,minus,plus)
    elseif estimated_power >= 0
        num,den,minus,plus = InitialScaledStartValuesNegativeExponentPositivePower(
                significand, exponent, estimated_power, need_boundary_deltas,
                num,den,minus,plus)
    else
        num,den,minus,plus = InitialScaledStartValuesNegativeExponentNegativePower(
                significand, exponent, estimated_power, need_boundary_deltas,
                num,den,minus,plus)
    end
    if need_boundary_deltas && lower_boundary_is_closer
         den::BigInt <<= 1
         num::BigInt <<= 1
        plus::BigInt <<= 1
    end
    return num, den, minus, plus
end

function FixupMultiply10(estimated_power,is_even,num,den,minus,plus)
    in_range = is_even ? num + plus >= den : num + plus > den
    if in_range
        decimal_point::Int32 = estimated_power + 1
    else
        decimal_point = estimated_power
        num::BigInt *= 10
        if minus == plus
            minus::BigInt *= 10
             plus::BigInt = minus
        else
            minus *= 10
            plus *= 10
        end
    end
    return num, den, minus, plus, decimal_point
end