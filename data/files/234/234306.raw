# Binomial coeffcient
function choose{T<:Integer}(n::T, k::T)
    k > n && return 0
    r = 1
    for d=1:k
        r *= n
        r /= d
        n -= 1
    end
    Int(r)
end

# The number of combinations follow Pascal's triangle.
# For a square of side-length `n`:
choose_routes(n::Int) = binomial(2n, n)


function cube_routes(n::Int)
    a = ones(Int, n+1)
    for i=1:n
        for j=1:i
            a[j+1] = a[j+1] + a[j]
        end
        a[i+1] = 2 * a[i]
    end
    a[n+1]
end
