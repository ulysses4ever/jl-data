include("runModel.jl")
include("plotcomparisonSelectedLabels.jl")

function runPatient(patientID)
	savestr = string("outputJul13/", patientID)
	datasource = string("/home/rachel/Documents/modelingHR/LinkedRecordsTimeData10min/", patientID)
	runModel(savestr,datasource)
	plotcomparison(savestr)
end
