include("runModel.jl")

function validate_model()
	pathsToData = ["../data/Luan2010Fig5A.csv", "../data/Luan2010Fig5B.csv","../data/Luan2010Fig5C.csv", "../data/Luan2010Fig5D.csv", "../data/Luan2010Fig5E.csv","../data/Luan2010Fig5F.csv"]
	for j in collect(1:6)
		pathToParams = string("parameterEstimation/LOOCVSavingAllParams_2017_1_31_No_specific_bounds/bestParamSetsFromLOOCV", j, "excluded.txt")
		savestr = string("figures/LOOCVValidation_Predicting_set_", j, "-2017_1_31.pdf")
		currdata = allexperimentaldata[j]
		runModelWithMultipleParams(pathToParams, pathsToData[j],j,savestr)
	end
end
