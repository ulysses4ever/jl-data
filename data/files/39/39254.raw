using GenomicTiles
using BioFeatures
using DataFrames

function get_sub_regions(region_id, start, stop)
    subregions = DataFrame( gene_id = [region_id,region_id], start = [start, start + 50], stop = [start+60, start + 100])
    #return Features( subregions, region_id_field = :gene_id  )
    return subregions
end

## example where we do genes and some feature that happens in genes
region_lengths = int( rand(100)*1000 )
starts = 1:1000:100000
stops = starts + region_lengths
gene_id = zeros(ASCIIString,100)
for i=1:100
  gene_id[i] = "GENE$i"
end
# Read these into a BioFeature -
#  in the Description field you have GENE_ID --> LENGTH
#  in the features
regions   = DataFrame(gene_id = gene_id, start = starts, stop= stops)
features  = Features( regions, region_id_field=:gene_id, regions=true )
#features.description
## Features in genes
for i = 1:100
  subfeatures = get_sub_regions("GENE$i",starts[i],stops[i])
  add_dataframe_to_features!(features,subfeatures, region_id_field=:gene_id)
end

features.features
# Then get tiles in one step.
# plot_tiles(features, clustering=kmeans)
# plot_cluster_bar_char(Feature)
