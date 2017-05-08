const kMinimalTargetExponent = -60
const kMaximalTargetExponent = -32

function roundweed(buffer,len,rest,tk,unit,kappa,too_high::Uint64,unsafe_interval::Uint64)
    small::Uint64 = too_high - unit
    big::Uint64 = too_high + unit
    #@assert(rest <= unsafe_interval)
    while rest < small &&
            unsafe_interval - rest >= tk &&
            (rest + tk < small ||
            small - rest >= rest + tk - small)
        buffer[len-1] -= 1
        rest += tk
    end
    if rest < big &&
        unsafe_interval - rest >= tk &&
        (rest + tk < big ||
        big - rest > rest + tk - big)
        return false, kappa
    end
    return (2 * unit <= rest) && (rest <= unsafe_interval - 4 * unit), kappa
end

function roundweed(buffer,len,rest,tk,unit,kappa,null1::Int=0,null2::Int=0)
    #@assert(rest < tk)
    unit >= tk && return false, kappa
    tk - unit <= unit && return false, kappa
    tk - rest > rest && (tk - 2 * rest >= 2 * unit) && return true, kappa
    if rest > unit && (tk - (rest - unit) <= (rest - unit))
        buffer[len-1] += 1
        for i = (len-1):-1:2
            buffer[i] != '0' + 10 && break
            buffer[i] = '0'
            buffer[i-1] += 1
        end
        if buffer[1] == '0' + 10
            buffer[1] = '1'
            kappa += 1
        end
        return true, kappa
    end
    return false, kappa
end

const SmallPowersOfTen = Uint32[
        0, 1, 10, 100, 1000, 10000, 100000, 
        1000000, 10000000, 100000000, 1000000000]

function BiggestPowerTen(n::Uint32,n_bits::Int)
    #@assert(n < (uint32(1) << (n_bits + 1)))
    guess = (n_bits + 1) * 1233 >> 12
    guess += 1
    i = SmallPowersOfTen[guess+1]
    return n < i ? (SmallPowersOfTen[guess], guess-1) : (i,guess)
end

function DigitGen(low::Float,w::Float,high::Float,
                  buffer,requested_digits=1000,shortest=true)
    unit::Uint64 = 1
    one = Float(unit << -w.e, w.e)
    if shortest
        too_low = Float(low.s-unit,low.e)
        too_high = Float(high.s+unit,high.e)
        unsafe_interval = too_high - too_low
        ref = too_high
    else
        ref = w
        unsafe_interval = w
    end
    integrals::Uint32 = ref.s >> -one.e
    fractionals::Uint64 = ref.s & (one.s-1)
    divisor::Uint32, divisor_exp_plus_one::Int32 = BiggestPowerTen(integrals, 64 + one.e)
    kappa::Int32 = divisor_exp_plus_one
    len::Int32 = 1
    rest::Uint64 = 0
    check = false
    while kappa > 0
        digit::Int32 = div(integrals,divisor)
        #@assert(digit <= 9)
        buffer[len] = '0' + digit
        len += 1
        requested_digits -= 1
        integrals %= divisor
        kappa -= 1
        rest = (uint64(integrals) << -one.e) + fractionals
        check = shortest ? (rest < unsafe_interval.s) : (requested_digits == 0)
        check && break
        divisor = div(divisor,10)
    end
    if check
        a,b = shortest ? ((too_high - w).s, unsafe_interval.s) : (0,0)
        r, kappa = roundweed(buffer, len, rest, uint64(divisor) << -one.e,
                    unit,kappa,a,b)
        return r, kappa, len
    end
    #@assert(one.e >= -60)
    #@assert(fractionals < one.s)
    #@assert(div(0xFFFFFFFFFFFFFFFF,10) >= one.s)
    while true
        !shortest && (requested_digits <= 0 || fractionals < unit) && break
        fractionals *= 10
        unit *= 10
        unsafe_interval = Float(unsafe_interval.s*10,unsafe_interval.e)
        digit::Int32 = fractionals >> -one.e
        #@assert(digit <= 9)
        buffer[len] = '0' + digit
        len += 1
        requested_digits -= 1
        fractionals &= one.s - 1
        kappa -= 1
        shortest && fractionals < unsafe_interval.s && break
    end    
    if shortest
        a,b = (too_high - w).s*unit,unsafe_interval.s
    else
        requested_digits != 0 && return false, kappa, len
        a,b = 0, 0
    end
    r, kappa = roundweed(buffer,len,fractionals,one.s,
                         unit,kappa,a,b)
    return r, kappa, len
end

function fastdtoa(v,mode,requested_digits=1000,buffer=Array(Char,100))
    v = float64(v)
    f = normalize(v)
    shortest = true
    if mode == FAST_DTOA_SHORTEST
        bound_minus, bound_plus = normalizedbound(v)
    elseif mode == FAST_DTOA_SHORTEST_SINGLE
        single_v = float32(v)
        bound_minus, bound_plus = normalizedbound(single_v)
    else
        bound_minus, bound_plus = f,f
        shortest = false
    end
    #@assert(bound_plus.e == f.e)
    ten_mk_minimal_binary_exponent = 
        kMinimalTargetExponent - (f.e + FloatSignificandSize)
    ten_mk_maximal_binary_exponent = 
        kMaximalTargetExponent - (f.e + FloatSignificandSize)
    cp = GetCachedPowerForBinaryExponentRange(
           ten_mk_minimal_binary_exponent,
           ten_mk_maximal_binary_exponent)
    #@assert(kMinimalTargetExponent <= f.e + cp.e + 64)
    #@assert(kMaximalTargetExponent >= f.e + cp.e + 64)
    scaled_w = f * cp
    #@assert(scaled_w.e == bound_plus.e + cp.e + 64)
    scaled_bound_minus = bound_minus * cp
    scaled_bound_plus = bound_plus * cp
    r, kappa, len = DigitGen(scaled_bound_minus,scaled_w,
                             scaled_bound_plus,buffer,
                             requested_digits,shortest)
    decimal_exponent = -cp.de + kappa
    return r, len-1, decimal_exponent+len-1, buffer
end

const FAST_DTOA_SHORTEST = int32(1)
const FAST_DTOA_SHORTEST_SINGLE = int32(2)
const FAST_DTOA_PRECISION = int32(3)