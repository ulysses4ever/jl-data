using GeneralizedMaps
using Base.Test
using FactCheck

# write your own tests here
g = GeneralizedMaps.GeneralizedMap(Int32, Int32)
GeneralizedMaps.polygon!(g, convert(Int32, 2), 4)
# count verts
facts() do
    @fact GeneralizedMaps.countkcells(g, 0) => 4
    # count edges
    @fact GeneralizedMaps.countkcells(g, 1) => 4
    # count faces
    @fact GeneralizedMaps.countkcells(g, 2) => 1
end
