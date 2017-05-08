#Kevin Gerad Menzes thesis, 1998
using PyPlot

function BPLewis(VD,BP0)
	#VD = volume deficit
	#BP0 = initial blood pressure, 120 mmHg in healthy adult, 100 in child, 140 in elderly
	#alpha = curve parameter 
	#beta = curve parameter
	#TDV=percent terminal volume deficit
	#V0 = initial blood volume
	alpha = 2.0
	beta = 1.68
	TDV = .65

	BP = BP0.*(1-(VD./(TDV.*V0)).^beta).^alpha
	return BP
	
end

function calculateBleedRate(R0,BP,BP0)
	#R0 = initial bleeeding rate, ml/min
	#BP0 = initial blood pressure, mmHg
	#BP = present blood pressure, mmHg
	
	R = R0*BP/BP0
	return R
end


function runModel()
	close("all")
	global BP0 = 120.0 #mmHg
	global V0 = 5000.0 #mL 
	th = 10 #min
	#global k = -1/th*l
	dt = .01
	t = collect(0:dt:100)
	currBP = BP0
	R0 = 10 #mL/min
	currVD = 0.0

	BP = Float64[]
	R = Float64[]
	VD = Float64[]
	
	for time in t
		currBP = BPLewis(currVD,BP0)
		currR = calculateBleedRate(R0,currBP, BP0)
		currVD = currVD +currR*dt

		push!(BP, currBP)
		push!(R, currR)
		push!(VD, currVD)
	end

	figure()
	hold("on")
	plt[:subplot](2,2,1)
	plot(t,BP, "k")
	title("Blood Pressure (mmHg)")
	plt[:subplot](2,2,2)
	plot(t,R, color = ".75")
	title("Bleed Out Rate (mL/min)")
	plt[:subplot](2,2,3)
	plot(t,VD, color = ".5")
	title("Volume Deficit (mL)")
end
