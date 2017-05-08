using PyPlot
using ExcelReaders

function plotAverageThrombin(pathToData, savestr)
	close("all")
	data = readdlm(pathToData)
	time = data[:,1]
	avg_run = mean(data[:,2:3],2);
	plot(time, avg_run, "k.");
	xlabel("Time in seconds");
	ylabel("Thrombin Concentration (micormolar)")
	savefig(savestr)
end

function plotAverageROTEM()
	close("all")
	pathToData="../data/Viscoelasticmeasurements.xlsx"
	p9caseWTPA="Timecourse!H3:J1166"
	p9caseNoTPA="Timecourse!K3:M1544"
	p10caseWTPA="Timecourse!A3:C1301"
	p10caseNoTPA="Timecourse!D3:F789"
	p6caseWTPA = "Timecourse!AC3:AE1097"
	p6caseNoTPA="Timecourse!AF3:AH988"
	cases = [p6caseWTPA,p6caseNoTPA,p9caseWTPA, p9caseNoTPA, p10caseWTPA, p10caseNoTPA]
	j = 1
	widths = [.5,.5, 1,1,2, 2]
	figure()
	for case in cases
		if(j%2 ==0)
			colorstr = "0.1"
		else
			colorstr=".5"
		end
		data=readxl(pathToData, case)
		data=Array{Float64}(data)
		time = data[:,1]
		avg_run = mean(data[:,2:3],2);
		plot(time, avg_run, "-", color= colorstr, linewidth = widths[j]);
		j = j+1
	end
	legend(["With tPA=2nM p6", "Without tPA p6","With tPA=2nM p9", "Without tPA p9","With tPA=2nM p10", "Without tPA p10"], loc="best")
	xlabel("Time in seconds");
	ylabel("ROTEM Curve")
	savefig("figures/ROTEMcurvesForP_9_10_6.pdf")
end
