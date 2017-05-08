using MatlabCompat, DataFrames, Distances, Jewel
using Distances.pairwise, Distances.Euclidean

maximumRelocationDistance = 100; # pixels
matFileDir = "U:\\Data\\150415-Francesca-Hela-Fucci-timelapse_Plate_15\\analysis\\all_timepoints\\"
matFileDirArray = readdir(matFileDir)
#matFilesArray = sub(matFileDirArray, find( , matFileDirArray)
fileCommon = ".mat"

filteredFileNameArray = filter(matFileDirArray->contains(matFileDirArray,fileCommon), matFileDirArray)
sort!(filteredFileNameArray)
numberOfTimePoints = length(filteredFileNameArray)
# preallocate a Dictionary

allTimePoints = Dict()
# read the mat-files loop
for iTP in 1:numberOfTimePoints
  println(string("reading: ","$matFileDir","$(filteredFileNameArray[iTP])"))
  matFileDict = Dict([("$(iTP-1)", MatlabCompat.load(string("$matFileDir","$(filteredFileNameArray[iTP])")) )])
  allTimePoints = merge(allTimePoints, matFileDict)
end

println("finished reading files.\n Starting the Analysis...")

dataFrame = DataFrame(nucleus_ID = ASCIIString[], mean_Intensity_GFP = Float64[], mean_Intensity_TRITC = Float64[], mean_Intensity_Virus = Float64[], location_X = Float64[], location_Y = Float64[], well_ID = ASCIIString[], site_ID = ASCIIString[], time_Point = Float64[])
# parse CP data structure to create a dataframe to work with
for iTP in 1:numberOfTimePoints
  numberOfUniqueSets = length((allTimePoints["0"]["handles"]["Measurements"]["Image"]["Metadata_Site"]))
  for iSet in 1:numberOfUniqueSets
    timePoint = "$(iTP-1)"
    siteID = allTimePoints[timePoint]["handles"]["Measurements"]["Image"]["Metadata_Site"][iSet]
    wellID = allTimePoints[timePoint]["handles"]["Measurements"]["Image"]["Metadata_Well"][iSet]
    numberOfNuclei = length(allTimePoints["$(iTP-1)"]["handles"]["Measurements"]["Nuclei"]["Intensity_MeanIntensity_GFP"][iSet]);
    # iterate through all the nuclei
    for iNucleus in 1:numberOfNuclei
      # get measurements for the new data array
      meanIntensityGFP = allTimePoints[timePoint]["handles"]["Measurements"]["Nuclei"]["Intensity_MeanIntensity_GFP"][iSet][iNucleus]
      meanIntensityTRITC = allTimePoints[timePoint]["handles"]["Measurements"]["Nuclei"]["Intensity_MeanIntensity_TRITC"][iSet][iNucleus]
      meanIntensityVirus = allTimePoints[timePoint]["handles"]["Measurements"]["Nuclei"]["Intensity_MeanIntensity_Virus"][iSet][iNucleus]
      locationX = allTimePoints[timePoint]["handles"]["Measurements"]["Nuclei"]["Location_Center_X"][iSet][iNucleus]
      locationY = allTimePoints[timePoint]["handles"]["Measurements"]["Nuclei"]["Location_Center_Y"][iSet][iNucleus]

      # create a unique nucleus id for the time point 0
      if timePoint == "0"
        nucleusID = string(wellID,"_",siteID,"_",iNucleus)
        #println(nucleusID)
      else
        nucleusID = ""
      end
      #construct dataframe with measurements
      push!(dataFrame, [nucleusID, meanIntensityGFP, meanIntensityTRITC, meanIntensityVirus, locationX, locationY, wellID, siteID, iTP])
    end
  end
end

#println(dataFrame)
sort!(dataFrame, cols = :time_Point)
#println(dataFrame[1,1])

# associate each nucleus of each timepoint with a single nearest neightbor from the previous time point
# for subTP in groupby(dataFrame, :time_Point)
#      subTP[:]
# end
trackedDataFrame = DataFrame(nucleus_ID = ASCIIString[], mean_Intensity_GFP = Float64[], mean_Intensity_TRITC = Float64[], mean_Intensity_Virus = Float64[], location_X = Float64[], location_Y = Float64[], well_ID = ASCIIString[], site_ID = ASCIIString[], time_Point = Float64[], distances = Float64[])

grouppedWellDataFrame = groupby(dataFrame, :well_ID)
for iWell = 1:length(grouppedWellDataFrame)
  currentWell = grouppedWellDataFrame[iWell][:well_ID][1]
  println("processing well $(currentWell)")
  grouppedSiteDataFrame = groupby(grouppedWellDataFrame[iWell], :site_ID)
  for iSite = 1:length(grouppedSiteDataFrame)
    currentSite = grouppedSiteDataFrame[iSite][:site_ID][1]
    println("processing site $(currentSite)")
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

    #println("size of the first time point $(length(nucleusID))")
    for i in 1:length(nucleusID)

      push!(trackedDataFrame, [nucleusID[i], meanIntensityGFP[i], meanIntensityTRITC[i], meanIntensityVirus[i], locationX[i], locationY[i], wellID[i], siteID[i], timePoint[i], distancesMeasurement[i]])
    end
     #println("line 36, $(length(grouppedTPDataFrame))")
     for iTP = 2:length(grouppedTPDataFrame)
       currentTPData = grouppedTPDataFrame[iTP]
       #println("line 39")
       #previousTPData = grouppedTPDataFrame[iTP-1]
       # get previous time point data

       previousTPData = trackedDataFrame[(trackedDataFrame[:well_ID] .== currentWell) & (trackedDataFrame[:site_ID] .== currentSite) & (trackedDataFrame[:time_Point] .== iTP-1), :]

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
       for iLine = 1:size(previousTPData,1)
         if previousTPid[iLine] == ""
          #println("line 55 $(length(previousTPData))")
          distanceToPrevious = 0.
          push!(arrayOfDistances, distanceToPrevious)
          #println("empty nucleusID")
         else
          current = [currentTPData[:location_X] currentTPData[:location_Y]]'
          #println(size(current))

          previous = [repmat([previousTPData[:location_X][iLine]], size(current,2)) repmat([previousTPData[:location_Y][iLine]], size(current,2))]'
          #println(previous)
          #println(current)

          # compute the euclidean distances, works like in the example below
          # A = [8 1; 2 1; 3 3; 4 5; 5 4; 6 2]' # has to be transposed
          # B = [8 1; 2 1; 3 3; 4 1; 1 1; 3 7]'
          # println(Distances.colwise(Euclidean(), A, B))

          distanceVector = Distances.colwise(Euclidean(), previous, current)
          distanceToPrevious = minimum(distanceVector)
          #println("type of stuff to push to arrayOfDistances $(typeof(distanceToPrevious))")
          push!(arrayOfDistances, distanceToPrevious)
          neighborIndex = find(x -> x == minimum(distanceVector) , distanceVector)

          #if minimum(distanceVector) <= maximumRelocationDistance
            #println("in time point $iTP found a neighbor, updating index $neighborIndex with $(previousTPid[iLine])")
            arrayOfIDs[neighborIndex] = previousTPid[iLine]
            #println("result is $(arrayOfIDs[neighborIndex])")
          #end
         end
       #println("line 84")
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

       #println("pushing array of $(length(nucleusID))$(length(meanIntensityGFP))$(length(meanIntensityTRITC))$(length(meanIntensityVirus))$(length(locationX))$(length(locationY))$(length(wellID))$(length(siteID))$(length(timePoint))$(length(distancesMeasurement)) elements")

       for i = 1:length(nucleusID)
         push!(trackedDataFrame, [nucleusID[i], meanIntensityGFP[i], meanIntensityTRITC[i], meanIntensityVirus[i], locationX[i], locationY[i], wellID[i], siteID[i], timePoint[i], distancesMeasurement[i]])
       end
   end
  end
end

println("finished processing, saving data...")

writetable("U:\\Data\\150415-Francesca-Hela-Fucci-timelapse_Plate_15\\analysis\\all_timepoints\\trackedData.csv", trackedDataFrame)
println("data saved")

# trackedDataFrame[:nucleus_ID=="B02_1_1"]
# trackedDataFrame[3800:3832]

# grouppedWellDataFrame[2000]
# grouppedSiteDataFrame = groupby(grouppedWellDataFrame[1], :site_ID)
# grouppedSiteDataFrame[1]

#  grouppedTPDataFrame = groupby(grouppedSiteDataFrame[1], :time_Point)
# grouppedTPDataFrame[1,]
# nucleusID = convert(Array,grouppedTPDataFrame[1,][:nucleus_ID])
# nucleusID[:]
# A = Array(Float64,3)
#trackedDataFrame[:nucleus_ID == "B02_1_1"]
#insert!(dataFrame, 1, trackedNucleusID, :tracked_Nucleus_ID)
#grouppedDataFrame[1][:nucleus_ID]
#trackedNucleusID[28000]
# size(trackedNucleusID)
# size(dataFrame)
# dataFrame[dataFrame[:time_Point == 2]]
# test = grouppedDataFrame[1]
# insert!(test[1], "item::AbstractVector", test[:nucleus_ID])
# test[:nucleus_ID][1] = "asdasd"
# test[:nucleus_ID][1]

# grouppedDataFrame[1][grouppedDataFrame[1][:nucleus_ID] .== "B02_1_22"][:location_X]
# println("complete")

# repmat([4], 4, 1)
# 60636*2
# print(find(x -> x == minimum(A) , A))
# df = DataFrame(A = [1, 2, 3], B = [1, 2, 3])
# insert!(df, 3, 5, :J)
# D = convert(Array, df)
# println(D)
