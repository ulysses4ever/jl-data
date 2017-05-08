using MatlabCompat, DataFrames, DataFramesMeta
include("minmaxnorm.jl")

#######################
#  Parameters
#######################
dataTablePath  = "U:\\Data\\150415-Francesca-Hela-Fucci-timelapse_Plate_15\\analysis\\all_timepoints\\csv\\trackedData.csv";
folderPath = "U:\\Data\\150415-Francesca-Hela-Fucci-timelapse_Plate_15\\analysis\\all_timepoints\\csv\\";

trackedDataFrame = readtable(dataTablePath);

minTrackLength = 35;




#######################
#  Filtering
#######################

# filter out empty values
filteredDataFrame = @where(trackedDataFrame, :nucleus_ID .!= "");


# filter out tracks that are shorter than minTrackLength
groupedFilteredDataFrame = groupby(filteredDataFrame, :nucleus_ID)
numberOfNuclei = length(groupedFilteredDataFrame)
finalDataFrame = DataFrame(nucleus_ID = UTF8String[], mean_Intensity_GFP = Float64[], mean_Intensity_TRITC = Float64[], mean_Intensity_Virus = Float64[], location_X = Float64[], location_Y = Float64[], well_ID = UTF8String[], site_ID = Int64[], time_Point = Float64[], distances = Float64[])


for iNucleus in 1:numberOfNuclei
  if size(groupedFilteredDataFrame[iNucleus],1) >= minTrackLength
    append!(finalDataFrame, groupedFilteredDataFrame[iNucleus][:])
  end
end

#######################
#  Normalize Global
#######################
# minmax normalize red and green
finalDataFrame = @transform(finalDataFrame, normalized_mean_Intensity_GFP =  minmaxnorm(:mean_Intensity_GFP), normalized_mean_Intensity_TRITC =  minmaxnorm(:mean_Intensity_TRITC))

# compute cell cycle score as green - red and brightness score as (green+red)/2
finalDataFrame = @transform(finalDataFrame, cell_cycle_score = :normalized_mean_Intensity_GFP - :mean_Intensity_TRITC, brightness_score = (:normalized_mean_Intensity_GFP + :mean_Intensity_TRITC)/2)
#######################
#  Grouping & Saving
#######################

# save the filted results

#all results
savePath = string(folderPath, "trackedDataFiltered.csv")
writetable(savePath, finalDataFrame)

# groupped results by column
for iCol in 2:10
  selectedDataFrame = DataFrame(nucleus_ID = UTF8String[], mean_Intensity_GFP = Float64[], mean_Intensity_TRITC = Float64[], mean_Intensity_Virus = Float64[], location_X = Float64[], location_Y = Float64[], well_ID = UTF8String[], site_ID = Int64[], time_Point = Float64[], distances = Float64[], normalized_mean_Intensity_GFP = Any[], normalized_mean_Intensity_TRITC = Any[], cell_cycle_score = Any[], brightness_score = Float64[])
  if  iCol < 10
    column = "0$iCol"
  else
    column = "$iCol"
  end
  for iRow in ["B", "C", "D"]
    println("$iRow$column")
    selectedData = @where(finalDataFrame, :well_ID .== "$iRow$column", );
    append!(selectedDataFrame, selectedData)
  end
  savePath = string(folderPath, "col_","$(iCol)_", "trackedDataFiltered.csv")
  println("$(size(selectedDataFrame))")
  writetable(savePath, selectedDataFrame)
  selectedDataFrame = DataFrame()
end

#typeof(finalDataFrame[:brightness_score])
#selesctedDataFrame = DataFrame(nucleus_ID = UTF8String[], mean_Intensity_GFP = Float64[], mean_Intensity_TRITC = Float64[], mean_Intensity_Virus = Float64[], location_X = Float64[], location_Y = Float64[], well_ID = UTF8String[], site_ID = Int64[], time_Point = Float64[], distances = Float64[], normalized_mean_Intensity_GFP = Any[], normalized_mean_Intensity_TRITC = Any[])
#selectedDataFrame = DataFrame()
