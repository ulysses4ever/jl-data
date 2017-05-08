using GeneralizedMaps
using Base.Test
using FactCheck

function sew8darts()
    g = GeneralizedMaps.GeneralizedMap(Int32, Int32) 
    for i in range(1, 8)
        push!(g, GeneralizedMaps.Dart(2, Int32, Int32))
    end
    # first sew pairs of darts to each other to form vertices
    for i in range(1, 2, div(length(g.darts), 2))
        GeneralizedMaps.sew!(g.darts[i], g.darts[i+1], 0)
    end
    # now create edges
    for i in range(2, 2, div(length(g.darts), 2))
        GeneralizedMaps.sew!(g.darts[i], g.darts[(i+1)%8], 1)
    end
    return g
end

function countkcells(g, k)
    cells = Set{Set{eltype(g.darts)}}()
    for d in g.darts
        push!(cells, GeneralizedMaps.collectcelldarts(d, k))
    end
    return length(cells)
end

# write your own tests here
g = sew8darts()
# count verts
facts() do
    @fact countkcells(g, 0) => 4
    # count edges
    @fact countkcells(g, 1) => 4
    # count faces
    @fact countkcells(g, 2) => 1
end
