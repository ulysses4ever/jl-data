function chain_length(n::Int)
    cl = 1
    while true
        n == 1 && break
        n = iseven(n) ? div(n,2) : 3n+1
        cl += 1
    end
    cl
end

immutable Collatz
    n::Int
    cl::Int
    Collatz(n::Int) = new(n, chain_length(n))
end

function Base.max(x::Collatz, y::Collatz)
    x.cl > y.cl ? x : y
end

function plongest_chain(nmax::Int)
    @parallel max for i=1:nmax
        Collatz(i)
    end
end

# note:
#  $ jl -p 8
#  julia> @everywhere include("q014.jl")
#  julia> @timed plongest_chain(nmax)



# serially
function longest_chain(nmax::Int)
    n = cmax = 0
    for i=1:nmax
        cl = chain_length(i)
        if cl > cmax
            cmax = cl
            n = i
        end
    end
    n
end


