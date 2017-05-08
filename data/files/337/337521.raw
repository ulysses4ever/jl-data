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


g = GeneralizedMaps.GeneralizedMap(Int64, Int64)
push!(g, GeneralizedMaps.Dart(2, Int64, Int64))
push!(g, GeneralizedMaps.Dart(2, Int64, Int64))
d = g.darts[1]
GeneralizedMaps.setembed!(d, 0, Nullable(100))
GeneralizedMaps.setembedloc!(d, 0, d)
GeneralizedMaps.sew!(g.darts[1], g.darts[2],1)
facts() do
    @fact get(g.darts[2].embedloc[1]) => g.darts[1]
end
