"""
Number theory related functions.

@author Kevin Wilson - khwilson@gmail.com
""";

include("utils.jl")

KRON_SQUARE_MOD_8 = [0, 1, 0, -1, 0, -1, 0, 1]

"""
Compute the Kronecker symbol `(a/b)`, which in the case where
b is prime is 1 if a is a square mod b, -1 if not, and 0 if
`a % b == 0`
"""
function kron(a:: Int64, b:: Int64)
    # Step 1
    if b == 0
        if a == 1 || a == -1
            return 1
        else
            return 0
        end
    end

    # Step 2
    if b % 2 == 0 && a % 2 == 0
        return 0
    end

    # Reduce b and let b = 2 ** v * b' with b' odd
    v = 0
    while b % 2 == 0
        v += 1
        b = div(b, 2)
    end

    if v % 2 == 0
        k = 1
    else
        k = KRON_SQUARE_MOD_8[a & 7 + 1]
    end

    if b < 0
        b = -b
        if a < 0
            k = -k
        end
    end

    while true
        # This will loop until a = 0, which will eventually happen, a la Euclid's algorithm
        if a == 0
            if b == 1
                return k
            end
            return 0
        end

        # Repeat removal of 2s from a
        v = 0
        while a % 2 == 0
            v += 1
            a = div(a, 2)
        end
        if v % 2 == 1
            k *= KRON_SQUARE_MOD_8[b & 7 + 1]
        end

        if (a & b & 2 != 0)
            k = -k
        end
        r = abs(a)
        a = b % r
        b = r
    end
end


"""
Factors a number D into prime factors. If D is not a
fundamental disriminant, then [] is returned.
"""
function sqfactor(D::Int64)
    # We'll output this array
    factors = Array{Int64, 1}()

    # Unless we short circuit, in which case, we'll output
    empty_array = Array{Int64, 1}()

    # Hold the sign
    signD = sign(D)
    D = abs(D)

    if D == 1
        return empty_array
    end

    has_two = D % 2 == 0

    if D % 16 == 0
        # Not a fundamental discriminant
        return empty_array
    end

    if D % 8 == 0
        push!(factors, 8)
        D = div(D, 8)
    elseif D % 4 == 0
        push!(factors, 4)
        D = div(D, 4)
    elseif D % 2 == 0
        # Not a fundamental discriminant
        return empty_array
    end

    p = 3
    recovered_sign = 1
    while p <= D
        if D % p != 0
            p += 2
            continue
        end
        v = 0
        while D % p == 0
            v += 1
            D = div(D, p)
        end
        if v > 1
            # Not squarefree
            return empty_array
        end
        if p % 4 == 3
            # 3 mod 4 gets a minus sign
            push!(factors, -p)
            recovered_sign *= -1
        else
            push!(factors, p)
        end
        p += 2
    end

    if !has_two && recovered_sign != signD
        return empty_array
    end

    if factors[1] == 4
        # In this case, the only possibility is that we have -4 in the
        # fundamental discriminant. So we'll pick up an extra minus
        # So if we've already got everything, we're screwed
        if recovered_sign == signD
            return empty_array
        end
        factors[1] = -4
    else
        # On the other hand, both positive and negative 8s are allowed, so check
        # if we need to flip the sign
        if recovered_sign != signD
            factors[1] = -8
        end
    end

    # If we get here, the number is squarefree, and has the appropriate sign
    return factors
end
