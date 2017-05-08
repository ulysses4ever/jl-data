using MatlabCompat, DataFrames, Distances, Jewel
using Distances.pairwise, Distances.Euclidean


dataFrame = DataFrame(nucleus_ID = ASCIIString["B02_1_1", "", ""], mean_Intensity_GFP = Float64[1., 1., 1.], mean_Intensity_TRITC = Float64[1., 1., 1.], mean_Intensity_Virus = Float64[1., 1., 1.], location_X = Float64[5., 4., 3.], location_Y = Float64[5., 4., 3.], well_ID = ASCIIString["B02", "B02", "B02"], site_ID = ASCIIString["1", "2", "3"], time_Point = Float64[1., 2., 3.])

trackedDataFrame = DataFrame(nucleus_ID = ASCIIString[], mean_Intensity_GFP = Float64[], mean_Intensity_TRITC = Float64[], mean_Intensity_Virus = Float64[], location_X = Float64[], location_Y = Float64[], well_ID = ASCIIString[], site_ID = ASCIIString[], time_Point = Float64[], distances = Float64[])

grouppedWellDataFrame = groupby(dataFrame, :well_ID)
for iWell = 1:length(grouppedWellDataFrame)
  println("processing well $(grouppedWellDataFrame[iWell][:well_ID][1])")
  grouppedSiteDataFrame = groupby(grouppedWellDataFrame[iWell], :site_ID)
  for iSite = 1:length(grouppedSiteDataFrame)
    println("processing site $(grouppedSiteDataFrame[iSite][:site_ID][1])")
    grouppedTPDataFrame = groupby(grouppedSiteDataFrame[iSite], :time_Point)
    println("this site has $(length(grouppedTPDataFrame[1][:nucleus_ID])) nuclei")

    # add the first time point to the new dataframe
    nucleusID = convert(Array,grouppedTPDataFrame[1][:nucleus_ID])
    meanIntensityGFP = convert(Array,grouppedTPDataFrame[1][:mean_Intensity_GFP])
    meanIntensityTRITC = convert(Array,grouppedTPDataFrame[1][:mean_Intensity_TRITC])
    meanIntensityVirus = convert(Array,grouppedTPDataFrame[1][:mean_Intensity_Virus])
    locationX = convert(Array,grouppedTPDataFrame[1][:location_X])
    locationY = convert(Array,grouppedTPDataFrame[1][:location_Y])
    wellID = convert(Array,grouppedTPDataFrame[1][:well_ID])
    siteID = convert(Array,grouppedTPDataFrame[1][:site_ID])
    timePoint = convert(Array,grouppedTPDataFrame[1][:time_Point])
    distancesMeasurement = Array(Float64, length(timePoint))
    distancesMeasurement[:] = 0.

    println("size of the first time point $(length(nucleusID))")
    for i in 1:length(nucleusID)

      push!(trackedDataFrame, [nucleusID[i], meanIntensityGFP[i], meanIntensityTRITC[i], meanIntensityVirus[i], locationX[i], locationY[i], wellID[i], siteID[i], timePoint[i], distancesMeasurement[i]])
    end
     println("line 36")
     for iTP = 2:length(grouppedTPDataFrame)
       currentTPData = grouppedTPDataFrame[iTP]
       println("line 39")
       previousTPData = grouppedTPDataFrame[iTP-1]

       # this is needed to get indeces of the IDs from the ungrouped permutable array rather than non-permutable DataFrame
       #previousTPLength = length(previousTPData)
       #previousTPid = trackedNucleusID[end-previousTPLength:end]
       #println(typeof(previousTPData[:nucleus_ID]))
       previousTPid = convert(Array, previousTPData[:nucleus_ID])
       #previousTPid = previousTPData[:nucleus_ID]
       # create a sub array to be permuted

       arrayOfIDs = convert(Array{ASCIIString,1}, grouppedTPDataFrame[iTP][:nucleus_ID])
       arrayOfDistances = Array(Float64, length(arrayOfIDs))
       arrayOfDistances[:] =  0.
       for iLine = 1:length(previousTPData)
         if previousTPid[iLine] == ""
          println("line 55")
          distanceToPrevious = 0.
          push!(arrayOfDistances, distanceToPrevious)
          println("empty nucleusID")
         else
          current = [currentTPData[:location_X] currentTPData[:location_Y]]'
          #println(size(current))

          previous = [repmat([previousTPData[:location_X][iLine]], size(current,2)) repmat([previousTPData[:location_Y][iLine]], size(current,2))]'
          println(previous)
          println(current)

          # compute the euclidean distances, works like in the example below
          # A = [8 1; 2 1; 3 3; 4 5; 5 4; 6 2]' # has to be transposed
          # B = [8 1; 2 1; 3 3; 4 1; 1 1; 3 7]'
          # println(Distances.colwise(Euclidean(), A, B))

          distanceVector = Distances.colwise(Euclidean(), previous, current)
          distanceToPrevious = minimum(distanceVector)
          println("type of stuff to push in line 129 $(typeof(distanceToPrevious))")
          push!(arrayOfDistances, distanceToPrevious)
          neighborIndex = find(x -> x == minimum(distanceVector) , distanceVector)

          #if minimum(distanceVector) <= maximumRelocationDistance
            println("in time point $iTP found a neighbor, updating index $neighborIndex with $(previousTPid[iLine])")
            arrayOfIDs[neighborIndex] = previousTPid[iLine]
            println("result is $(arrayOfIDs[neighborIndex])")
          #end
         end
       end
       # add the first time point to the new dataframe
       nucleusID = arrayOfIDs
       meanIntensityGFP = convert(Array,grouppedTPDataFrame[iTP][:mean_Intensity_GFP])
       meanIntensityTRITC = convert(Array,grouppedTPDataFrame[iTP][:mean_Intensity_TRITC])
       meanIntensityVirus = convert(Array,grouppedTPDataFrame[iTP][:mean_Intensity_Virus])
       locationX = convert(Array,grouppedTPDataFrame[iTP][:location_X])
       locationY = convert(Array,grouppedTPDataFrame[iTP][:location_Y])
       wellID = convert(Array,grouppedTPDataFrame[iTP][:well_ID])
       siteID = convert(Array,grouppedTPDataFrame[iTP][:site_ID])
       timePoint = convert(Array,grouppedTPDataFrame[iTP][:time_Point])
       distancesMeasurement = arrayOfDistances

       println("pushing array of $(length(nucleusID))$(length(meanIntensityGFP))$(length(meanIntensityTRITC))$(length(meanIntensityVirus))$(length(locationX))$(length(locationY))$(length(wellID))$(length(siteID))$(length(timePoint))$(length(distancesMeasurement)) elements")

       for i = 1:length(nucleusID)
         push!(trackedDataFrame, [nucleusID[i], meanIntensityGFP[i], meanIntensityTRITC[i], meanIntensityVirus[i], locationX[i], locationY[i], wellID[i], siteID[i], timePoint[i], distancesMeasurement[i]])
       end
   end
  end
end
trackedDataFrame
