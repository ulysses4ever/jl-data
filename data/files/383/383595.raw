include("runModel.jl")

function runPatient(patientID,setnumber,tend)
	savestr = string("outputOct6/", patientID)
	datasource = string("/home/rachel/Documents/work/optimization/LinkedRecordsTimeData10min/", patientID)
	runModel(setnumber,datasource,savestr, tend)
end
