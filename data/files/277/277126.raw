using GeneralizedMaps: GeneralizedMap, polygon!, countkcells, ids, collectcelldarts, id
using Base.Test
using FactCheck

# write your own tests here
g = GeneralizedMaps.GeneralizedMap(Int32, Int32)
GeneralizedMaps.polygon!(g, convert(Int32, 2), 4)
# count verts
facts() do
    @fact countkcells(g, 0) => 4
    # count edges
    @fact countkcells(g, 1) => 4
    # count faces
    @fact countkcells(g, 2) => 1

    @fact map( (i) -> foldl( (a, x) -> setindex!( a, ids( collectcelldarts( x[2], i ) ), id( x[2] )  ), Dict(), g.darts ), range(0, 3 ) ) => 
[
 Dict{Any,Any}( 
		1 => Set( [ 1, 8 ] ),
		2 => Set( [ 2, 3 ] ),
		3 => Set( [ 2, 3 ] ),
		4 => Set( [ 4, 5 ] ),
		5 => Set( [ 4, 5 ] ),
		6 => Set( [ 6, 7 ] ),
		7 => Set( [ 6, 7 ] ),
		8 => Set( [ 1, 8 ] ) ),
 Dict{Any,Any}( 
		1 => Set( [ 1, 2 ] ),
		2 => Set( [ 1, 2 ] ),
		3 => Set( [ 3, 4 ] ),
		4 => Set( [ 3, 4 ] ),
		5 => Set( [ 5, 6 ] ),
		6 => Set( [ 5, 6 ] ),
		7 => Set( [ 7, 8 ] ),
		8 => Set( [ 7, 8 ] ) ),
 Dict{Any,Any}(
	       1 => Set( [ 1, 2, 3, 4, 5, 6, 7, 8 ] ),
	       2 => Set( [ 1, 2, 3, 4, 5, 6, 7, 8 ] ),
	       3 => Set( [ 1, 2, 3, 4, 5, 6, 7, 8 ] ),
	       4 => Set( [ 1, 2, 3, 4, 5, 6, 7, 8 ] ),
	       5 => Set( [ 1, 2, 3, 4, 5, 6, 7, 8 ] ),
	       6 => Set( [ 1, 2, 3, 4, 5, 6, 7, 8 ] ),
	       7 => Set( [ 1, 2, 3, 4, 5, 6, 7, 8 ] ),
	       8 => Set( [ 1, 2, 3, 4, 5, 6, 7, 8 ] ) ),
]
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
