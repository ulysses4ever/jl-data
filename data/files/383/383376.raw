include("runModel.jl")

function validate_model()
	pathsToData = ["../data/Luan2010Fig5A.csv", "../data/Luan2010Fig5B.csv","../data/Luan2010Fig5C.csv", "../data/Luan2010Fig5D.csv", "../data/Luan2010Fig5E.csv","../data/Luan2010Fig5F.csv"]

	allexperimentaldata = Array[]
	for j in collect(1:size(pathsToData,1))
		experimentaldata = readdlm(pathsToData[j], ',')	
		push!(allexperimentaldata, experimentaldata)
	end
	for j in collect(1:3)
		pathToParams = string("parameterEstimation/LOOCVSavingAllParams_2017_02_02/bestParamSetsFromLOOCV", j, "excluded.txt")
		savestr = string("figures/LOOCVValidation_Predicting_set_", j, "-2017_02_02.pdf")
		currdata = allexperimentaldata[j]
		runModelWithMultipleParams(pathToParams, pathsToData[j],j,savestr)
	end
end

validate_model()
