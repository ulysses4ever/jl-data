using Iterators

include("nt.jl")
include("utils.jl")

""" The raw version of U """
function Uslow(d::Int64, Z::Int64)
    total = 0
    for n in 1:Z
        total += kron(d, n)
    end
    return total
end

""" The sum of Kronecker symbols `(d/n)` for `1 ≤ n ≤ Z`. Only defined for d % 4 \in [0, 1] """
function U(d::Int64, Z::Int64)
    rem = posrem(d, 4)
    if !(rem == 0 || rem == 1)
        @printf "d %d rem %d" d rem
        @assert false
    end

    # If d == 0, then `(0|n)` is always 0
    if d == 0
        return 0
    end

    # If d == 1, then `(1/n)` is always `1`
    if d == 1
        return Z
    end

    # `(4|n)` only takes the value 1, but only at odd integers.
    # At even integers it is 0
    if d == 4
        return div(Z + 1, 2)
    end

    # From the orthogonality relations of characters, the sum is periodic
    # with period d. So we only need to sum Z % |d| terms
    return Uslow(d, Z % abs(d))
end

"""
This is the version of T which takes quite a bit of time to compute.
However, the values should be identical, and in fact we test this
in the tests
"""
function Tslow(c2::Int64, c2prime::Int64, dI::Int64, D::Int64, Y::Int64)
    total::Int64 = 0
    for m in 1:Y
        subtotal::Int64 = 0
        for n in 1:div(Y,m)
            subtotal += kron(div(c2prime * D, dI), n)
        end
        total += kron(c2 * dI, m) * subtotal
    end
    return total
end


"""
Compute T_chi(c, Y) where
* χ = ψχ_I where χ is a character of the ray class group CL_c^2 where
* χ_I is the class group character determined by dI,
* ψ is the character (c2|.)
* c2prime is the associated modification when D ≡ 1 (mod 8), c2 = 4, and
  c = p2, and so c2prime = 1 (otherwise, c2prime = c2)
* D is the discriminant of the quadratic field, and
* Y is the bound
"""
function T(c2::Int64, c2prime::Int64, dI::Int64, D::Int64, Y::Int64)

    total::Int64 = 0

    E::Int64 = 1
    F = sqrt(dI^2 * c2 / c2prime * Y / abs(D))
    E = Int64(round(F))

    c2_dI = c2 * dI
    c2prime_D_by_dI = div(c2prime * D, dI)

    for m in 1:E
        Y_by_m = div(Y, m)
        total += kron(c2_dI, m) * U(c2prime_D_by_dI, Y_by_m)
    end

    Y_by_E = Y
    if E != 0
        Y_by_E = div(Y, E)
    end
    for m in 1:Y_by_E
        Y_by_m = div(Y, m)
        total += kron(c2prime_D_by_dI, m) * U(c2_dI, Y_by_m)
    end

    total -= U(c2_dI, E) * U(c2prime_D_by_dI, Y_by_E)
    return total
end


"""
Return the value of Cohen's mu_D(n)
"""
function μ(n::Int64, D::Int64)
    n_factored = factor(n)
    ret::Int64 = 1
    for p in keys(n_factored)
        power = n_factored[p]
        if D % p == 0
            # ramified
            if power == 1
                ret = -ret
            else
                return 0
            end
        else
            if kron(D, p) == 1
                # split
                if power == 1
                    ret *= -2
                elseif power != 2
                    return 0
                end
            else
                # inert
                if power == 2
                    ret = -ret
                else
                    return 0
                end
            end
        end
    end
    return ret
end


function S5(D::Int64, Y::Int64)
    @assert posrem(D, 8) == 5
    D_factored = sqfactor(D)
    total::Int64 = 0
    for subset in subsets(D)
        dI = prod(subset)
        if abs(dI) > abs(div(D, dI))
            # Only take one of dI and D/dI
            continue
        end

        # 4 * T_{chi, 1}((1), Y/16)
        total += 4 * T(1, 1, dI, D, div(Y, 16))

        # T_{chi, 4} T(2, Y)
        for c2 in [4, -4]
            if D > 0 && c2 * dI < 0
                # For real qudratic fields, we skip negative characters
                continue
            end
            total += T(c2, c2, dI, D, Y)
        end
    end
    return total
end

function S1(D::Int64, Y::Int64)
    @assert posrem(D, 8) == 1
    D_factored = sqfactor(D)
    total::Int64 = 0
    for subset in subsets(D)
        dI = prod(subset)
        if abs(dI) > abs(div(D, dI))
            # Only take one of dI and D/dI
            continue
        end

        # 4 * T_{chi, 1}((1), Y/16)
        total += 4 * T(1, 1, dI, D, div(Y, 16))

        # 4 * T_{chi, 1}(p2, Y/4)
        total += 4 * T(1, 1, dI, D, div(Y, 4))

        # T_{chi, 4} T(2, Y)
        for c2 in [4, -4]
            if D > 0 && c2 * dI < 0
                # For real qudratic fields, we skip negative characters
                continue
            end
            total += T(c2, c2, dI, D, Y)
        end
    end
    return total
end

function S8(D::Int64, Y::Int64)
    @assert posrem(D, 16) == 8
    D_factored = sqfactor(D)
    total::Int64 = 0
    for subset in subsets(D)
        dI = prod(subset)
        if abs(dI) > abs(div(D, dI))
            # Only take one of dI and D/dI
            continue
        end

        # 4 * T_{chi, 1}((1), Y/16)
        total += 4 * T(1, 1, dI, D, div(Y, 16))

        # 2 * T_{chi, 4}(p2, Y/4)
        for c2 in [4, -4]
            total += 2 * T(c2, c2, dI, D, div(Y, 4))
        end

        # T_{chi, 4} T(2, Y)
        for c2 in [4, -4]
            if D > 0 && c2 * dI < 0
                # For real qudratic fields, we skip negative characters
                continue
            end
            total += T(c2, c2, dI, D, Y)
        end
    end
    return total
end

function S12(D::Int64, Y::Int64)
    @assert posrem(D, 16) == 12
    D_factored = sqfactor(D)
    total::Int64 = 0
    for subset in subsets(D)
        dI = prod(subset)
        if abs(dI) > abs(div(D, dI))
            # Only take one of dI and D/dI
            continue
        end

        # 4 * T_{chi, 1}((1), Y/16)
        val = 4 * T(1, 1, dI, D, div(Y, 16))
        total += val

        # 2 * T_{chi, 1}(p2, Y/4)
        val = 2 * T(1, 1, dI, D, div(Y, 4))
        total += val

        # T_{chi, 4} (2, Y)
        for c2 in [4, 8]
            if D > 0 && c2 * dI < 0
                # For real qudratic fields, we skip negative characters
                continue
            end
            val = T(c2, c2, dI, D, Y)
            total += val
        end
    end
    return total
end

function S(D::Int64, Y::Int64)
    if posrem(D, 8) == 5
        return S5(D, Y)
    elseif posrem(D, 8) == 1
        return S1(D, Y)
    elseif posrem(D, 16) == 8
        return S8(D, Y)
    elseif posrem(D, 16) == 12
        return S12(D, Y)
    end
end


"""
Count the number of quadratic extensions of Q(sqrt(D))
with norm bounded by X.
"""
function N(D::Int64, X::Int64)
    ret::Int64 = 0

    # If the bound is 0, then there's nothing to do
    upper_bound = Int64(floor(sqrt(X)))
    if upper_bound == 0
        return 0
    end

    for n in 1:upper_bound
        val = μ(n, D) * S(D, div(X, n^2))
        ret += val
    end
    if D < 0
        ret = div(ret, 2)
    end
    return ret - 1
end
