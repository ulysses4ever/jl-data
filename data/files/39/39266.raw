using BioFeatures
using DataFrames
using IntervalTrees

type Tile
  start::Int64
  stop::Int64
  value::Float64
end

function make_tiles( start, stop; num_tiles = 20, default_value = 0 )
     #bin_size
     #println("Making tiles $gene_start")
     length = stop - start
     bin_size = int64( length / num_tiles)
     tiles = Tile[]
     tile_start = start
     tile_end = tile_start + (bin_size - 1)
     for t = 1:num_tiles
         tile = Tile(tile_start,tile_end, default_value)
         #println(join([tile_start,tile_end, bin_size], "\t") )
         push!(tiles,tile)
         tile_start = tile_end + 1
         tile_end = tile_start + bin_size -1
     end
     return tiles
end

function make_tiles( feature::DataFrame; num_tiles = 20,default_value = 0  )
    start = int( feature[:start][1] )
    stop  = int( feature[:stop][1] )
    tiles = make_tiles(start,stop,num_tiles=num_tiles, default_value=default_value)
end

#  calculate_tile_value: Checks whether a tile overlaps any features and sets the value field of the tile if so
#  Input:
#     tile :: Tile
#     region_features:: Dictionary of IntervalTrees containing Features - indexed by the region name e.g. chr name
#  region_features should hold only one region in the features object
function calculate_tile_value( tile, region_features, value=1 )
    features_interval_trees = collect( values( region_features.features ) )
    #println(features_interval_trees[1])
    features_interval_tree = features_interval_trees[1]
    #println(tile)
    intersected_start = IntervalTrees.hasintersection( features_interval_tree, int32(tile.start) )
    if intersected_start # change this to complete interval, not just point
      tile.value = value
      #println("Overlap Tile")
    end
    intersected_stop = IntervalTrees.hasintersection( features_interval_tree, int32(tile.stop) )
    if intersected_stop # change this to complete interval, not just point
      tile.value = value
      #println("Overlap Tile")
    end
end

function set_tile_value( tile, region_features, type_field, value_map::Dict{ASCIIString,Float64} )
    features_interval_trees = collect(  values( region_features.features ) )
    #println(features_interval_trees[1])
    features_interval_tree = features_interval_trees[1]
    #println(tile)
    intersected = IntervalTrees.intersect( features_interval_tree, (int32(tile.start),int32(tile.stop)) )
    intersected_array = collect(intersected)
    if length(intersected_array) > 0
        current_type = ""
        for ia in intersected_array
            df = ia[2]
            #println(df)
            feature_type = df[type_field][1]
            value_to_assign = value_map[feature_type]
            #println(value_to_assign)
            if current_type == ""
                current_type=df[type_field][1]
            elseif current_type != df[type_field][1]
                value_to_assign = value_map["MIXED"]
            end
            tile.value = value_to_assign
        end
    end
    #return tile
    #intersected_start = IntervalTrees.hasintersection( features_interval_tree, int32(tile.start) )
    #if intersected_start # change this to complete interval, not just point
    #  tile.value = value
    #  println("Overlap Tile")
    #end
    #intersected_stop = IntervalTrees.hasintersection( features_interval_tree, int32(tile.stop) )
    #if intersected_stop # change this to complete interval, not just point
    #  tile.value = value
    #  println("Overlap Tile")
    #end
end


function set_tile_value1(tile, region_features)
    features_interval_trees = collect(  values( region_features.features ) )
    #println(features_interval_trees[1])
    features_interval_tree = features_interval_trees[1]
    #println(tile)
    intersected = IntervalTrees.intersect( features_interval_tree, (int32(tile.start),int32(tile.stop)) )
    intersected_array = collect(intersected)
    value_to_assign = 0
    tile_length = tile.stop - tile.start
    if length(intersected_array) > 0
        current_type = ""
        for ia in intersected_array
            df = ia[2]
            #println(df)
            #println(tile)
            if df[:start][1] <= tile.start && df[:stop][1] >= tile.stop
                value_to_assign = 1
                #println("Assigned $value_to_assign as feature is larger than tile")
                continue
            end

            if  df[:start][1] >= tile.start && df[:stop][1] <= tile.stop
                rat =  (df[:stop][1] - df[:start][1]) / tile_length
                #println("adding $rat")
                value_to_assign += rat # (df[:stop][1] - df[:start][1]) / tile_length )
                #println("assigned $value_to_assign as feature ovelaps completely with tile")
                continue
            end

            if df[:start][1] > tile.start && df[:start][1] < tile.stop
                rat =  ( tile.stop - df[:start][1] ) / tile_length
                #println("adding $rat")
                value_to_assign += rat
                #println("assigned $value_to_assign (feature start overlaps with tile")
                continue
            elseif df[:stop][1] > tile.start && df[:stop][1] < tile.stop
                rat = ( df[:stop][1] - tile.start  ) / tile_length
                #println("adding $rat")
                value_to_assign += rat #( (tile.stop - df[:stop][1]  ) / tile_length )
                #println("assigned $value_to_assign (feature start overlaps with tile")
                continue
            end

            #value_to_assign = value_map[feature_type]
            #println(value_to_assign)
            #if current_type == ""
            #    current_type=df[type_field][1]
            #elseif current_type != df[type_field][1]
            #    value_to_assign = value_map["MIXED"]
            #end
            #tile.value = value_to_assign
        end
        tile.value = value_to_assign
    end
end



# Adds the values of a contiguous set of tiles
# to a row in a matrix
function add_tiles_to_tiles_matrix(tiles_matrix,tiles)
    tiles_matrix_row = map( x -> x.value, tiles)
    #println("CONCAT TILES TO MATRIX")
    if(tiles_matrix == nothing)
       tiles_matrix = tiles_matrix_row
       println("TILES: $tiles_matrix")
    else
       tiles_matrix = hcat(tiles_matrix,tiles_matrix_row)
    end
    return tiles_matrix
end

function add_tiles_to_tiles_matrix(tiles_matrix,tiles,idx)
   i=1
   for tile in tiles
     tiles_matrix[idx,i] = tile.value
     i +=1
   end
   #tiles_matrix_row = map( x -> x.value, tiles)
   #println("CONCAT TILES TO MATRIX")
   # if(tiles_matrix == nothing)
   #    tiles_matrix = tiles_matrix_row
   #    println("TILES: $tiles_matrix")
   # else
   #    tiles_matrix = hcat(tiles_matrix,tiles_matrix_row)
   # end
   # return tiles_matrix
end

function add_tiles_to_predefined_tiles_matrix(tiles_matrix,tiles,idx)
   i=1
   for tile in tiles
     tiles_matrix[idx,i] = tile.value
     i +=1
   end
   #tiles_matrix_row = map( x -> x.value, tiles)
   #println("CONCAT TILES TO MATRIX")
   # if(tiles_matrix == nothing)
   #    tiles_matrix = tiles_matrix_row
   #    println("TILES: $tiles_matrix")
   # else
   #    tiles_matrix = hcat(tiles_matrix,tiles_matrix_row)
   # end
   # return tiles_matrix
end
