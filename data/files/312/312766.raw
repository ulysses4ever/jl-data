#! /usr/bin/julia

# Rosetta Code, Vogel's approximation method

immutable TProblem{T<:Integer,U<:String}
    sd::Array{Array{T,1},1}
    toc::Array{T,2}
    labels::Array{Array{U,1},1}
    tsort::Array{Array{T,2}, 1}
end

function TProblem{T<:Integer,U<:String}(s::Array{T,1},
                                        d::Array{T,1},
                                        toc::Array{T,2},
                                        slab::Array{U,1},
                                        dlab::Array{U,1})
    scnt = length(s)
    dcnt = length(d)
    size(toc) = (scnt,dcnt) || error("Supply, Demand, TOC Size Mismatch")
    length(slab) == scnt || error("Supply Label Size Labels")
    length(dlab) == dcnt || error("Demand Label Size Labels")
    0 <= minimum(s) || error("Negative Supply Value")
    0 <= minimum(d) || error("Negative Demand Value")
    sd = Array{T,1}[]
    push!(sd, s)
    push!(sd, d)
    labels = Array{U,1}[]
    push!(labels, slab)
    push!(labels, dlab)
    tsort = Array{T,2}[]
    push!(tsort, mapslices(sortperm, toc, 2))
    push!(tsort, mapslices(sortperm, toc, 1))
    TProblem(sd, toc, labels, tsort)
end
isbalanced(tp::TProblem) = sum(tp.sd[1]) == sum(tp.sd[2])

type Resource{T<:Integer}
    dim::T
    i::T
    quant::T
    l::T
    m::T
    p::T
    q::T
end
function Resource{T<:Integer}(dim::T, i::T, quant::T)
    zed = zero(T)
    Resource(dim, i, quant, zed, zed, zed, zed)
end

isavailable(r::Resource) = 0 < r.quant
Base.isless(a::Resource, b::Resource) = a.p < b.p || (a.p == b.p && b.q < a.q)

function penalize!{T<:Integer,U<:String}(sd::Array{Array{Resource{T},1},1},
                                         tp::TProblem{T,U})
    avail = BitArray{1}[]
    for dim in 2:-1:1
        push!(avail, bitpack(map(isavailable, sd[dim])))
    end
    for dim in 1:2, r in sd[dim]
        if r.quant == 0
            r.l = r.m = r.p = r.q = 0
            continue
        end
        r.l == 0 || !avail[dim][r.l] || !avail[dim][r.m] || continue
        rsort = filter(x->avail[dim][x], vec(slicedim(tp.tsort[dim],dim,r.i)))
        rcost = vec(slicedim(tp.toc, dim, r.i))[rsort]
        if length(rsort) == 1
            r.l = r.m = rsort[1]
            r.p = r.q = rcost[1]
        else
            r.l, r.m = rsort[1:2]
            r.p = rcost[2] - rcost[1]
            r.q = rcost[1]
        end
    end
    nothing
end

function vogel{T<:Integer,U<:String}(tp::TProblem{T,U})
    sdcnt = collect(size(tp.toc))
    sol = spzeros(T, sdcnt[1], sdcnt[2])
    sd = Array{Resource{T},1}[]
    for dim in 1:2
        push!(sd, [Resource(dim, i, tp.sd[dim][i]) for i in 1:sdcnt[dim]])
    end
    while any(map(isavailable, sd[1])) && any(map(isavailable, sd[2]))
        penalize!(sd, tp)
        a = maximum([sd[1], sd[2]])
        b = sd[rem1(a.dim+1,2)][a.l]
        if a.dim == 2 # swap to make a supply and b demand
            a, b = b, a
        end
        expend = min(a.quant, b.quant)        
        sol[a.i, b.i] = expend
        a.quant -= expend
        b.quant -= expend
    end
    return sol
end

sup = [50, 60, 50, 50]
slab = ["W", "X", "Y", "Z"]
dem = [30, 20, 70, 30, 60]
dlab = ["A", "B", "C", "D", "E"]
c = [16 16 13 22 17;
     14 14 13 19 15;
     19 19 20 23 50;
     50 12 50 15 11]

tp = TProblem(sup, dem, c, slab, dlab)
sol = vogel(tp)
cost = sum(tp.toc .* sol)

println("The solution is:")
print("        ")
for s in tp.labels[2]
    print(@sprintf "%4s" s)
end
println()
for i in 1:size(tp.toc)[1]
    print(@sprintf "    %4s" tp.labels[1][i])
    for j in 1:size(tp.toc)[2]
        print(@sprintf "%4d" sol[i,j])
    end
println()
end
println("The total cost is:  ", cost)
