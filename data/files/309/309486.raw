abstract Split

typealias SplitOut (Vector, GRanges)


type FullSplit <: Split
    ranges::GRanges
    a::Vector
    b::Vector
    on_a::Bool
end

current(s::FullSplit) = (s.on_a ? s.a : s.b, s.ranges)
proposed!(s::FullSplit) = (shuffle!(s.on_a ? s.b : s.a), s.ranges)
accept!(s::FullSplit) = s.on_a = !s.on_a
reject!(s::FullSplit) = nothing


type UpdatingSplit <: Split
    ranges::GRanges
    a::Vector
    last::Vector{(Int,Int)}
    num::Int
    max::Int
end

current(s::UpdatingSplit) = (s.a, s.ranges)
function proposed!(s::UpdatingSplit)
    s.num = rand(1:s.max)
    a = s.a
    n = length(a)
    for i in 1:s.num
        inds = tuple(rand(1:n, 2)...)
        swap!(a, inds)
        s.last[i]= inds
    end
    (a, s.ranges)
end
accept!(s::UpdatingSplit) = nothing
function reject!(s::UpdatingSplit)
    for i in s.num:1
        swap!(s.a, s.last[i])
    end
end

function swap!(a::Array, inds::(Int, Int))
    i, j = inds
    tmp = a[i]
    a[i] = a[j]
    a[j] = tmp
end


splitby(a::Vector, g::Groups) = FullSplit(groups2ranges(g), copy(a), copy(a), true)
splitby(a::Vector, g::Groups, max::Int) = 
    UpdatingSplit(groups2ranges(g), copy(a), Array((Int,Int), max), max, max)
