using GenomicTiles
using BioFeatures
using DataFrames
using Gadfly
using Clustering #need for assignments()
using Distances

function get_sub_regions(start, stop)
    subregions = DataFrame( start = [start, start + 50], stop = [start+60, start + 100],rtype=["A","B"])
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
         tiles = make_tiles(feature, num_tiles=30, default_value = 0)
         #println(tiles)
         for tile in tiles
            dmap = @Compat.Dict("A"=> 3.0,"B"=-3.0,"MIXED"=0.0)
            tile = set_tile_value( tile, subregions, :rtype,dmap)
         end
         tiles_matrix = add_tiles_to_tiles_matrix(tiles_matrix, tiles)
    end
end

tiles_matrix[1,:]

(tiles_matrix_clustered,kmeans_cluster_object,sil_df) = cluster_tiles(tiles_matrix',
                                                                      method="kmeans",
                                                                      num_clusters_range=5:10,
                                                                      kmeans_repeats=10)
path = "/home/nic/Desktop/test-kmeans.png"
colour_scale =Scale.discrete_color_manual("red","green")
plot_matrix2(tiles_matrix_clustered,path,colour_scale=colour_scale)
path = "/home/nic/Desktop/test-kmeans-bar.png"
plot_cluster_bar_chart(tiles_matrix',assignments(kmeans_cluster_object),path)

sil_df
Gadfly.plot(sil_df,x="r",y="ave_sil",color="k",Geom.line)

#tiles_matrix
#distance_matrix = pairwise(SqEuclidean(),tiles_matrix')
#length(assignments(kmeans_cluster_object))
#sil_val = silhouettes(kmeans_cluster_object,distance_matrix)
#mean(sil_val)
#=
(tiles_matrix_clustered,cluster_object,sil_val) = cluster_tiles(tiles_matrix, method="dbscan", eps=1,minpts=2)
path = "/home/nic/Desktop/test-dbscan.png"
colour_scale =Scale.discrete_color_manual("red","green")
plot_matrix2(tiles_matrix_clustered,path,colour_scale=colour_scale)
path = "/home/nic/Desktop/test-dbscan-bar.png"
plot_cluster_bar_chart(tiles_matrix, assignments( cluster_object), path)
=#




#cluster_object.assignments =cluster_object.assignments + 5
#(tiles_matrix_clustered,cluster_assignments) = cluster_tiles(tiles_matrix, method="affprop")
#path = "/home/nic/Desktop/test-affprop.png"
#plot_matrix2(tiles_matrix_clustered,path)
#path = "/home/nic/Desktop/test-affprop-bar.png"
#plot_cluster_bar_chart(tiles_matrix,cluster_assignments,path)
#cluster_assignments
#tiles_matrix'[1,:]
#tiles_matrix'[100,:]
#cluster_assignments
