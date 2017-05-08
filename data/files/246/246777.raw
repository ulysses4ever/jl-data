using HDF5, JLD

include("EA.jl")
include("RobotGene.jl")
include("VarLengthIndividual.jl")
include("GAPopulation.jl")

allData = Any[]

prefix = "data ("
suffix = ").jld"
fileCount = 1
curTime = time()
while (isfile(prefix*string(fileCount)*suffix))
  file = jldopen(prefix*string(fileCount)*suffix, "r")
  curData = read(file, "dataOut")
  close(file)
  append!(allData, curData)
  fileCount += 1
end

println("READ TIME: ",time() - curTime)
curTime = time()

@save "allData.jld" allData
println("WRITE TIME: ",time() - curTime)
println("SUCCESS!")
println(length(allData)," entries successfully saved.")