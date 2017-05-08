using Compat
using GeneralizedMaps: GeneralizedMap, polygon!, countkcells, ids, collectcelldarts, id, intersperseLeadingZeros
using Base.Test
using FactCheck

# write your own tests here

facts("Check polygon construction.") do
    g = GeneralizedMaps.GeneralizedMap(Int64, Int64)
    GeneralizedMaps.polygon!(g, convert(Int64, 2), 4)
    context("Ensure polygon produces the appropriate number of 0-, 1-, and 2-cells.") do
        # count verts
        @fact countkcells(g, 0) => 4
        # count edges
        @fact countkcells(g, 1) => 4
        # count faces
        @fact countkcells(g, 2) => 1
    end

    context("Check that collectcelldarts returns the right answers.") do
        @fact map((i) -> foldl((a, x) -> setindex!(a, map(id, collectcelldarts(x[2], i)), id(x[2])), Dict(), g.darts), 0:2) =>
        [{
         1 => [1,8],
         2 => [2,3],
         3 => [3,2],
         4 => [4,5],
         5 => [5,4],
         6 => [6,7],
         7 => [7,6],
         8 => [8,1] },
         {
         1 => [1,2],
         2 => [2,1],
         3 => [3,4],
         4 => [4,3],
         5 => [5,6],
         6 => [6,5],
         7 => [7,8],
         8 => [8,7] },
         {
         1 => [1,2,3,4,5,6,7,8],
         2 => [2,1,8,7,6,5,4,3],
         3 => [3,4,5,6,7,8,1,2],
         4 => [4,3,2,1,8,7,6,5],
         5 => [5,6,7,8,1,2,3,4],
         6 => [6,5,4,3,2,1,8,7],
         7 => [7,8,1,2,3,4,5,6],
         8 => [8,7,6,5,4,3,2,1] }
        ]
    end   
end

facts("Test parallelpiped construction.") do
    g = GeneralizedMaps.GeneralizedMap(Int64, Int64)
    GeneralizedMaps.parallelepiped!(g, 2)
    context("Ensure appropriate number of 0-, 1-, 2-, and 3-cells.") do
        rightanswers = [8, 12, 6, 1]
        for (i, x) in enumerate(rightanswers)
            @fact countkcells(g, i-1) => x
        end
    end
end

facts("Check interspersLeadingZeros.") do
    @fact intersperseLeadingZeros( [ 1, 2, 3, 4, 6 ] ) => [ 0, 1, 0, 2, 0, 3, 0, 4, 0, 6 ] 
end


facts("Check that data is properly embeded and shared upon sewing.") do
    g = GeneralizedMaps.GeneralizedMap(Int64, Int64)
    push!(g, GeneralizedMaps.Dart(2, Int64, Int64))
    push!(g, GeneralizedMaps.Dart(2, Int64, Int64))
    d = g.darts[1]
    GeneralizedMaps.setembed!(d, 0, Nullable(100))
    GeneralizedMaps.setembedloc!(d, 0, d)
    GeneralizedMaps.sew!(g.darts[1], g.darts[2],1)
    @fact get(g.darts[2].embedloc[1]) => g.darts[1]
end

# vim: set ts=4 sw=4:
