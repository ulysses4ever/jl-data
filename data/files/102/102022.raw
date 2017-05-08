
module taxis
using sequenceCompare
using DataFrames
using JSON
using Iterators

export Point, SequenceRef, LoadData, GetUniqueCoords, GetTableOrderedSubset, ConstructCoordsDatabase, ConstructCoordsDatabase2, PlotPaths, findClosestTrainingExample, findClosestTrainingExampleForTestSet

    immutable Point{T}
      x::T
      y::T
    end

    type SequenceRef
        TripId::Int64
        SequenceIndex::Int64
        LengthRemaining::Int64
    end


    function LoadData(train_path, test_path)
        println("Begin")

        println("loading csv files")
        taxi_df = readtable(train_path)
        taxi_validation_df = readtable(test_path)

        println("loading coords")
        taxi_df[:COORDS] = [float(hcat(JSON.parse(x)...)) for x in  taxi_df[:POLYLINE]]
        taxi_validation_df[:COORDS] = [float(hcat(JSON.parse(x)...)) for x in taxi_validation_df[:POLYLINE]]

        println("getting coords counts")
        taxi_df[:NUM_COORDS] = [int(length(x)/2)::Int64 for x in taxi_df[:COORDS]]
        taxi_validation_df[:NUM_COORDS] = [int(length(x)/2)::Int64 for x in taxi_validation_df[:COORDS]]

        println("deleting unneeded data rows/columns")
        delete!(taxi_validation_df, :POLYLINE)
        delete!(taxi_df, :POLYLINE)

        taxi_df[:START] = [x[:,1] for x in taxi_df[:COORDS]]
        taxi_validation_df[:START] = [x[:,1] for x in taxi_validation_df[:COORDS]]

        taxi_df[:END] = [x[:,end] for x in taxi_df[:COORDS]]
        taxi_validation_df[:END] = [x[:,end] for x in taxi_validation_df[:COORDS]]

        #These examples are not going to be useful!
        deleterows!(taxi_df, find(taxi_df[:NUM_COORDS] .== 0))
    
    taxi_df[:COORDS_TEST] = [c[:,1:int(floor((0.3 + 0.7*rand(1)[1])*size(c,2)))] for c in taxi_df[:COORDS]]

        println("done!")
    
        return taxi_df, taxi_validation_df
    end


    function GetUniqueCoords(c, round_len=4)
        c = round(c, round_len)
        c2 = Set([(c[i,1]::Float64, c[i,2]::Float64) for i in 1:size(c, 1)])
        println("all coords: ", length(c), ", unique coords: ", length(c2))
        return c2
    end


    function GetTableOrderedSubset(df, num_records=100000)
        idxs = sort(shuffle([1:size(df,1)])[1:num_records])
        return df[idxs,:]
    end

    # Constructing a coords database

    function ConstructCoordsDatabase(df, round_len=5)
        print(length(df[:TRIP_ID]), ", ", length(df[:COORDS]))
        return ConstructCoordsDatabase2(df[:TRIP_ID], df[:COORDS], round_len)
    end


    function ConstructCoordsDatabase2(TripIds, Coords, round_len=5)
        #println("num trip_ids/coords: ", length(TripIds), " ", length(Coords))
        #print("coords:", Coords)
        D = Dict{(Float64,Float64),Array{SequenceRef,1}}()
        num_coords = size(TripIds,1)
        for i=1:num_coords
            trip_id = TripIds[i]

            coords = Coords[i]
            if length(coords) == 0
                continue
            end

            coords = round(Coords[i],round_len)       

            num_coords = size(coords,2)
            #println("num_coords: ", num_coords)
            for j=1:num_coords
                coord_pair = (coords[1,j], coords[2,j])
                #println("coord_pair: ", coord_pair, ", j/num_coords: ", j, "/", num_coords, ", thing: ", [SequenceRef(trip_id, j, num_coords-j)])
                if !haskey(D, coord_pair)
                    D[coord_pair] = [SequenceRef(trip_id, j, num_coords-j)]
                else
                    push!(D[coord_pair], SequenceRef(trip_id, j, num_coords-j))
                end        
            end
        end

        return D    
    end

    # Finding similar paths using Dynamic Path Warping

    function findClosestTrainingExample(all_train_coords, test_path, w=1)
        num_paths = length(all_train_coords)
        best_dist = 9999.0
        best_path = all_train_coords[1]
        for k=1:num_paths
            train_path = all_train_coords[k]
        
            if size(train_path, 2) < size(test_path, 2)
                continue
            end
        
            if w == 1
                dist = sequenceCompare.DTWDistance(train_path, test_path) 
            else
                dist = sequenceCompare.DTWDistance(train_path, test_path, w) 
            end
            #println("k=", k, " dist=", dist)
            if dist < best_dist
                #println(k, ", old best: ", best_dist, " new best: ", dist)
                best_dist = dist
                best_path = all_train_coords[k]
            end
        end

        return best_path
    end



    function findClosestTrainingExampleForTestSet(all_train_paths, all_test_paths, w=1)
        num_train_paths = length(all_train_paths)
        num_test_paths = length(all_test_paths)
        closest_examples = cell(num_test_paths)
        for k=1:num_test_paths
            if k % 20 == 0
                println(k, "/", num_test_paths, " for ", num_train_paths, " train path examples") 
            end
            test_path = all_test_paths[k]
            closest_training_example = findClosestTrainingExample(all_train_paths, test_path, w) 
            closest_examples[k] = closest_training_example
        end

        return closest_examples
    end

    function pFindClosestTrainingExampleForTestSet(all_train_paths, all_test_paths)
        getClosestExample = p -> findClosestTrainingExample(all_train_paths, p)
        return pmap(getClosestExample, all_test_paths)
    end



    # Didn't want to throw these away..
    function GetAverageDistanceFromCoordsSequence(coords)
        #Outline of the basic algorithm
        #for coord_pair c_1..c_n
        # estimate <- for i=1:n average(15*(i-1) + average(for c_j in D[c+i] * exp(-|L_j-L_i|) * L_j)
        coords = round(Coords[i],round_len)       
    end

    function GetAverageDistancesByCoordsDict(TripIds, Coords, round_len=5)
        distaces = Array{Float64,0}()
        num_coords = size(TripIds,1)
        for i=1:num_coords
            trip_id = TripIds[i]

            coords = Coords[i]
            if length(coords) == 0
                continue
            end

            coords = round(Coords[i],round_len)       

            num_coords = size(coords,2)
            #println("num_coords: ", num_coords)
            for j=1:num_coords
                coord_pair = (coords[1,j], coords[2,j])
                #println("coord_pair: ", coord_pair, ", j/num_coords: ", j, "/", num_coords, ", thing: ", [SequenceRef(trip_id, j, num_coords-j)])
                if !haskey(D, coord_pair)
                    D[coord_pair] = [SequenceRef(trip_id, j, num_coords-j)]
                else
                    push!(D[coord_pair], SequenceRef(trip_id, j, num_coords-j))
                end        
            end
        end

        return D    
    end


# ******************** Visualizations ******************************

    function PlotPaths(coords, show_limit=40)
        num_paths = min(length(coords), show_limit)
        num_coords = length(coords)
        coordsToPlot = coords[randperm(num_coords)[1:num_paths]]
        layers = [layer(x=round(c'[:,1],3),y=round(c'[:,2],3),Geom.point, Geom.path, Theme(default_color=RGB(rand(3)...))) for c in coordsToPlot]
        Gadfly.plot(layers...) 
    end

end