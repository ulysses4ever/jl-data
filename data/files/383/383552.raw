using ODE
using PyPlot

function volume_balance(t, y, data_dict)
	V = y[1]
	IVin= data_dict[1]
	IVdecay = data_dict[2]
	vol_lost = data_dict[3]
	k = data_dict[4]
	BP0= data_dict[5]
	terminal_vol_lost = data_dict[5]
	alpha = data_dict[6]
	beta = data_dict[7]
	phi = data_dict[8]
	psi = data_dict[9]
	Qctr = data_dict[10]
	V0 = data_dict[11]
	prevt = data_dict[12]
	BP = calculate_BP(BP0, vol_lost[end], terminal_vol_lost, alpha, beta)
	Qtcr = calculate_Qtcr(Qctr, BP, BP0, V0, phi, psi)
	
	dVdt = IVin-IVdecay+Qtcr[end]-k*V
	Vlost = dVdt*(prevt-t)+vol_lost[end]
	@show Vlost
	vol_lost = saveVols(Vlost, vol_lost)
	@show dVdt,t
	@show Qctr
	return [dVdt]
end

function calculate_Qtcr(Qtcr, BPcurr, BP0, V0, phi, psi)
	Qtcr_curr = phi*(BPcurr-BP0)*V0*(1-exp((sum(Qtcr)-V0*psi)/100))
	push!(Qtcr, Real(Qtcr_curr))
	return Qtcr
end

function calculate_BP(BP0, vol_lost, terminal_vol_lost, alpha, beta)
	BP = BP0*(1-(vol_lost/terminal_vol_lost)^beta)^alpha
	@show (vol_lost/terminal_vol_lost)
	return BP
end

function calculate_k(V0, BV, tBV)
	k = -1/tBV*log((V0-BV)/V0)
	return k
end

function saveVols(V, Vols)
	@show V, Vols
	push!(Vols, V)
	return Vols
end


function runSimulation(tend, tIV_insert)
	V0 = 5000.0 #assume starting with 5000 mL blood, about normal for 70 kg man
	BP0 = 120.0 #start at BP = 120 mmHg
	alpha = .63
	beta = 1.6
	phi = .00015
	psi= 15
	V_terminal = .5*V0
	times = collect(1:tend) # solve in seconds
	initial_BV = 5.0 #assume the person bleeds out 5 mL in first minute
	initial_k = calculate_k(V0, initial_BV, 1.0) 

	IVin_rates = [fill(0.0, tIV_insert); fill(5.0/60.0, tend-tIV_insert)] #assume IV inserted at time tIV_insert at a rate of 5mL/min
	IVdecay_rates = fill(0.0, tend) #right now, just make zeros. Should actually find values
	Qctr= Float64[0.0]

	data_dict = Dict()
	data_dict[3] = Float64[0.0]
	data_dict[4] = initial_k
	data_dict[5]= BP0
	data_dict[5] = V_terminal
	data_dict[6] = alpha
	data_dict[7] = beta
	data_dict[8] = phi
	data_dict[9] = psi
	data_dict[10] = Qctr
	data_dict[11] = V0
	data_dict[12] = 0.0 #prev t
	counter =1

	currIVin = IVin_rates[counter]
	currIVdecay = IVdecay_rates[counter]
	solvingTimes = collect(0:1:tend)
	data_dict[1] = IVin_rates[counter]
	data_dict[2] = IVdecay_rates[counter]
	vb(solvingTimes,y) = volume_balance(solvingTimes,y,data_dict)
	t,y = ODE.ode45(vb, V0, solvingTimes, points=:specified, reltol = 1E-4, abstol = 1E-4)
	V = [a[1] for a in y]
	plot(t,V) 

end
