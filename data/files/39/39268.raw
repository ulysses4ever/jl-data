using FactCheck
using BioFeatures
using Compat
include(Pkg.dir("GenomicTiles", "src","Tiles.jl"))


# --- Test tiles with overlap
tile = Tile(1,160,1)
df1 = DataFrame( region_id = ["R1","R1"],
                 start     = [1,100],
                 stop      = [50,300],
                 rtype     = ["NT","NB"] )
F = Features(df1)
dmap = @Compat.Dict("NT"=> 3.0,
                    "NB"=-3.0,
                    "MIXED"=1.0)
set_tile_value(tile,F,:rtype,dmap)
tile


# --- Test tiles with proportional overlap
expected_value = 49/299 + 200/299
49/299
200/299

tile = Tile(1,300,0)
set_tile_value1(tile,F)
tile


expected_value = 49/159 + 60/159
49/159
60/159
tile = Tile(1,160,0)
set_tile_value1(tile,F)
tile


expected_value= 100/200
tile = Tile(200,400,0)
set_tile_value1(tile,F)

expected_value =1
tile = Tile(1,100,0)
set_tile_value1(tile,F)
tile

expected_value = 50/50
tile = Tile(1,50,0)
set_tile_value1(tile,F)
tile

expected_value = 1
tile = Tile(1,45,0)
set_tile_value1(tile,F)
tile
