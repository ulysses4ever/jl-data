# Prepare Data Set
using DataFrames

dataSet = DataFrame()
dataSet[:Labels]  = ["Person One", "Person Two", "Person 3"]
dataSet[:Feature]  = {rand(0:255,5,5), zeros(5,5), ones(5,5)}

SUCCESSED = true
FAILED    = false

if FAILED

  # JSON
  using JSON

  jsonFileName = "dataSet.JSON"
  isfile(jsonFileName) && rm(jsonFileName)
  touch(jsonFileName)
  outfile = open(jsonFileName, "w")
  write(outfile, JSON.json(dataSet))
  close(outfile)

  infile = open(jsonFileName)
  inJsonContent = readall(infile)
  dataSetJson = JSON.parse(inJsonContent) # Error read in Strings

  @test dataSetJson == dataSet


  # MAT
  using MAT

  matFileName = "dataSet.mat"
  isfile(matFileName) && rm(matFileName)

  matwrite(matFileName, {
    "Labels" => dataSet[:Labels], # Error writing the file, "ERROR: access to undefined reference"
    "Feature" => dataSet[:Feature]
    })

  inMatContent = matread(matFileName)
  dataSetMat = DataFrame()
  dataSetMat["Labels"] = inMatContent[:Labels]
  dataSetMat["Feature"] = inMatContent[:Feature]

  @test dataSetMat == dataSet

  # DataFrames readtable, writetable
  csvFileName = "dataSet.csv"
  isfile(csvFileName) && rm(csvFileName)
  open(io -> print(io, ""), csvFileName, "bw")
  writetable(csvFileName, dataSet)

  dataSetCsv = DataFrame()
  dataSetCsv = readtable(csvFileName) # Error read in Strings

  @test dataSetCsv == dataSet

  # Pandas

end

if SUCCESSED
  # serialize/deserialize
  jldFileName = "dataSet.jld"
  isfile(jldFileName) && rm(jldFileName)
  touch(jldFileName)
  jldFile = open(jldFileName,"w")
  serialize(jldFile, dataSet)
  close(jldFile)

  dataSetJld = DataFrame()
  dataSetJld = open(deserialize, jldFileName)

  @test dataSetJld == dataSet

end