@__FILE__

include("EA.jl")
include("RobotGene.jl")
include("VarLengthIndividual.jl")
include("GAPopulation.jl")

using HDF5, JLD

A = [100,1000,10000,100000,1000000]
B = [100,10000,1000000]
Y = 1
dataOut = {}

POPsize = 500
gen = 2000
p = Progress(15,1)
for a in A
  for b in B
    testPop = Population(POPsize,a,b,1)
    elite, results = evolve!(testPop, gen)
    push!(dataOut, (a,b,elite))
    next!(p)
  end
end
dir = abspath("")
fName = tempname()
fName = basename(fName)
fName = splitext(fName)[1]

folderCount = 1
while(isdir(dir*string(folderCount)))
  folderCount += 1
end
mkdir(dir*string(folderCount))
finalName = dir * string(folderCount) * "\\" * fName * ".jld"

@save finalName dataOut
println("Saved")
