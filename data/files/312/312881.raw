#! /usr/bin/julia

# Rosetta Code, Fibonacci n-step number sequences

type NFib{T<:Integer}
    n::T
    klim::T
    seeder::Function
end

type FState
    a::Array{BigInt,1}
    adex::Integer
    k::Integer
end

function Base.start{T<:Integer}(nf::NFib{T})
    a = nf.seeder(nf.n)
    adex = 1
    k = 1
    return FState(a, adex, k)
end

function Base.done{T<:Integer}(nf::NFib{T}, fs::FState)
    fs.k > nf.klim
end

function Base.next{T<:Integer}(nf::NFib{T}, fs::FState)
    f = sum(fs.a)
    fs.a[fs.adex] = f
    fs.adex = rem1(fs.adex+1, nf.n)
    fs.k += 1
    return (f, fs)
end

function fib_seeder{T<:Integer}(n::T)
    a = zeros(BigInt, n)
    a[1] = one(BigInt)
    return a
end

function fib{T<:Integer}(n::T, k::T)
    NFib(n, k, fib_seeder)
end

function luc_rc_seeder{T<:Integer}(n::T)
    a = zeros(BigInt, n)
    a[1] = 3
    a[2] = -1
    return a
end

function luc_rc{T<:Integer}(n::T, k::T)
    NFib(n, k, luc_rc_seeder)
end

function luc_seeder{T<:Integer}(n::T)
    a = -ones(BigInt, n)
    a[end] = big(n)
    return a
end

function luc{T<:Integer}(n::T, k::T)
    NFib(n, k, luc_seeder)
end

lo = 2
hi = 10
klim = 16

print("n-step Fibonacci for n = (", lo, ",", hi)
println(") up to k = ", klim, ":")
for i in 2:10
    print(@sprintf("%5d => ", i))
    for j in fib(i, klim)
        print(j, " ")
    end
    println()
end

println()
print("n-step Rosetta Code Lucas for n = (", lo, ",", hi)
println(") up to k = ", klim, ":")
for i in 2:10
    print(@sprintf("%5d => ", i))
    for j in luc_rc(i, klim)
        print(j, " ")
    end
    println()
end

println()
print("n-step MathWorld Lucas for n = (", lo, ",", hi)
println(") up to k = ", klim, ":")
for i in 2:10
    print(@sprintf("%5d => ", i))
    for j in luc(i, klim)
        print(j, " ")
    end
    println()
end
