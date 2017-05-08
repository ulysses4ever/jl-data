using GenomicTiles
using BioFeatures
using DataFrames

function get_sub_regions(start, stop)
    subregions = DataFrame( start = [start, start + 50], stop = [start+60, start + 100])
    return Features( subregions )
end

#
# GET SOME COORDINATES TO SERVE AS A BASE THAT WILL BE SPLIT INTO TILES
#
region_lengths = int( rand(100)*1000 )
starts = 1:1000:100000
stops = starts + region_lengths

# Read these into a BioFeature - FeatureRegion
regions = DataFrame(start = starts, stop= stops)
FeaturesToBeSplitIntoTiles = Features( regions )

tiles = nothing
tiles_matrix = nothing
for features = values( FeaturesToBeSplitIntoTiles.features )
    for feature in values(features)
         subregions = get_sub_regions( feature[:start][1],feature[:stop][1] )
         tiles = make_tiles(feature, num_tiles=30, default_value = 1)
         #println(tiles)
         for tile in tiles
            tile = calculate_tile_value( tile, subregions, 0 )
         end
         tiles_matrix = add_tiles_to_tiles_matrix(tiles_matrix, tiles)
    end
end

(tiles_matrix_clustered,cluster_assignments) = cluster_tiles(tiles_matrix)
path = "/home/nic/Desktop/test.png"
plot_matrix2(tiles_matrix_clustered,path)
path = "/home/nic/Desktop/test-bar.png"
plot_cluster_bar_chart(tiles_matrix,cluster_assignments,path)

cluster_assignments
tiles_matrix'[1,:]
tiles_matrix'[100,:]
cluster_assignments
#clustered_tiles = cluster_tiles_matrix(tiles_matrix; method="kmeans",num_clusters=5)
#clustered_tiles is a tuple that includes the categories/assignments
#plot_cluster_tiles(clustered_tiles, path)
#plot_cluster_barplot(clustered_tiles, path)

#matrix = nothing
#tiles
# This first example considers the case where you havese several regions
# that overlap tiles. If the region overlaps the tiles then that tile should
# be counted as an overlap.

# The regions might have categories - but cannot overlap each other.
#  e.g. -----111---222-11-21-11

# for region in FeaturesToBeSplitIntoTiles
#   * generate some sub regions that will be tiled
#       subregions = get_sub_region(region.start,region.stop)
#   * get an array of tiles for the region to be tiled
#      tiles = make_tile(region)
#   for tile in tiles
#    *see which tiles the sub regions overlap and count, value_assignment is a vector for the values that should be assigned,
#    * if this is nothing - then just a count is made should an overlap be registered
#    * this sets a property in the tile
#       set_tile(tile,subregions,value_assignment)
# end

## Then put tiles into a matrix
#   matrix = nothing
#   foreach region ..
#      matrix_row = map(x -> x.value, tiles )
#      if matrix = nothing
#         matrix = matrix_row
#      else
#         hcat(matrix,matrix_row)
#      end
#

### Then
#
#   cluster_tiles = kmeans_tile_cluster(matrix,num_clusters)
#   plot_cluster_tile(cluster)
#   plot_cluster_barplot(cluster)
#
#   or
#
#   cluster_tiles = aff_prop_cluster(matrix, num_clusters)
#   ....

#=
starts_a = zeros(Int64,100)
stops_a  = zeros(Int64,100)
for i = 1:50
   starts_a[i] = starts[i]
   stops_a[i]  = starts[i] + 100
end

for i = 51:100
    starts_a[i] = stops[i] - 50
    stops_a[i] =  stops[i]
end

regions_a = DataFrame( start = starts_a, stop = stops_a)
FeaturesToBeCountedOverTiles = FeatureRegions(regions_a)


=#
