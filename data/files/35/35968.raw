"Representation of a bijective (1 to 1 and onto) function between finite sets."
immutable Bijection{K,V}
    f::Dict{K,V}
    g::Dict{V,K}
    Bijection() = new(Dict{K,V}(), Dict{V,K}())
end

function Bijection{K,V}(d::Dict{K,V})
    b = Bijection{K,V}()
    for (k, v) in d
        b[k] = v
    end
    return b
end

function Base.setindex!{K,V}(b::Bijection{K,V}, v::V, k::K)
    delete!(b.f, k)
    delete!(b.g, v)
    b.f[k] = v
    b.g[v] = k
end

Base.getindex{K,V}(b::Bijection{K,V}, k::K) = b.f[k]

Base.inv(b::Bijection) = b.g

Base.length(b::Bijection) = length(b.f)

Base.keys(b::Bijection) = keys(b.f)

Base.values(b::Bijection) = values(b.f)

function Base.show{K,V}(io::IO, b::Bijection{K,V})
    mkl = maximum(map(k -> length(string(k)), keys(b)))
    mkl = max(mkl, length(string(K)))
    mvl = maximum(map(v -> length(string(v)), values(b)))
    # print(io, lpad("B: $K", mkl + 3, "-"), " -> ", V)
    print(io, "B: ", K, " -> ", V)
    for k in keys(b)
        print(io, "\n   ", lpad(k, mkl, " "), " => ", rpad(b[k], mvl, " "))
    end
end
