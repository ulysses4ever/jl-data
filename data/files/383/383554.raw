using ODE
using PyPlot

function volume_balance(t, y, data_dict)
	V = y[1]
	IVin= data_dict[1]
	IVdecay = data_dict[2]
	vol_lost = data_dict[3]
	k = data_dict[4]
	BP0= data_dict[5]
	terminal_vol_lost = data_dict[13]
	alpha = data_dict[6]
	beta = data_dict[7]
	phi = data_dict[8]
	psi = data_dict[9]
	Qctr = data_dict[10]
	V0 = data_dict[11]
	prevt = data_dict[12]
	terminal_vol_lost = data_dict[13]
	BP = calculate_BP(BP0, vol_lost[end], terminal_vol_lost, alpha, beta,t)
	Qtcr = calculate_Qtcr(Qctr, BP, BP0, V0, phi, psi)
	
	dVdt = IVin-IVdecay+(Qtcr[end])-k*V
#	Vlost = dVdt*(t-prevt)+vol_lost[end]
#	@show Vlost
#	vol_lost = saveVols(Vlost, vol_lost)
#	@show dVdt,t
#	@show Qctr
	return [dVdt]
end

function calculate_Qtcr(Qtcr, BPcurr, BP0, V0, phi, psi)
	Qtcr_curr = real(phi*(BPcurr-BP0)*V0*(1-exp((sum(Qtcr)-V0*psi)/100)))

	if(Qtcr_curr> 0)
		Qtcr_curr= 0.0
	end
		@show Qtcr_curr
	Qtcr_curr = real(Qtcr_curr)
	push!(Qtcr, (Qtcr_curr))

	return Qtcr
end

function calculate_BP(BP0, vol_lost, terminal_vol_lost, alpha, beta,t)
	#@show BP0, vol_lost, terminal_vol_lost, alpha, beta
	if(vol_lost > terminal_vol_lost)
		BP = 0
		#dead
		println(string("Dead at t = ", t))
		error("Patient is dead, lost too much blood")
	else
		BP = BP0*(1-(vol_lost/terminal_vol_lost+0im)^beta)^alpha
	end
	#@show BP
	return BP
end

function calculate_k(V0, BV, tBV)
	k = -1/tBV*log((V0-BV)/V0)
	return k
end

function recreateBP(BP0, vol_lost, terminal_vol_lost, alpha, beta)
	@show (vol_lost/terminal_vol_lost).^beta
	@show (1-(vol_lost/terminal_vol_lost).^beta).^alpha
	BP = BP0*real(1-real(vol_lost/terminal_vol_lost).^beta).^alpha
	@show size(BP)
	return BP
end

function runSimulation(tend, tIV_insert, initial_BV)
	#initial BV in mL/sec
	tic()
	close("all")
	V0 = 5000.0 #assume starting with 5000 mL blood, about normal for 70 kg man
	BP0 = 120.0 #start at BP = 120 mmHg
	alpha = .63
	beta = 1.6
	phi = .00015
	psi= 15
	V_terminal = .5*V0
	times = collect(1:tend) # solve in seconds
	#initial_BV = 5.0/60.0 #assume the person bleeds out 5 mL in first minute
	initial_k = calculate_k(V0, initial_BV, 1.0) 

	IVin_rates = [fill(0.0, tIV_insert); fill(30.0/60.0, tend-tIV_insert)] #assume IV inserted at time tIV_insert at a rate of 5mL/min
	IVdecay_rates = fill(0.0, tend) #right now, just make zeros. Should actually find values
	Qctr= Float64[0.0]

	data_dict = Dict()
	data_dict[3] = Float64[0.0]
	data_dict[4] = initial_k
	data_dict[5]= BP0
	data_dict[6] = alpha
	data_dict[7] = beta
	data_dict[8] = phi
	data_dict[9] = psi
	data_dict[10] = Qctr
	data_dict[11] = V0
	data_dict[12] = 0.0 #prev t
	data_dict[13] = V_terminal
	counter =1

	initalVolume = V0
	solvingTimes = collect(0:1:tend)

	VTimeSeries = Float64[]
	VLostTimeSeries = Float64[]
	CumVLostTimeSeries = Float64[]
	push!(CumVLostTimeSeries, 0.0)
	push!(VLostTimeSeries, 0.0)
	push!(VTimeSeries, initalVolume)
	for j in collect(1:length(solvingTimes)-1)
		data_dict[1] = IVin_rates[counter]
		@show IVin_rates[counter]
		data_dict[2] = IVdecay_rates[counter]
		innerTimes = [solvingTimes[j]; solvingTimes[j+1]]
		
		vb(innerTimes,y) = volume_balance(innerTimes,y,data_dict)
		t,y = ODE.ode45(vb, initalVolume, innerTimes, points=:specified, reltol = 1E-4, abstol = 1E-4)
		V = [a[1] for a in y]
		#@show V
		Vlost = V[1]-V[end]
		@show Vlost
		push!(VTimeSeries, V[end])
		push!(VLostTimeSeries, Vlost)
		initalVolume = initalVolume-Vlost;

		#@show CumVLostTimeSeries
		totalVlost = sum(VLostTimeSeries)
		#@show totalVlost
		data_dict[3]= totalVlost;
		push!(CumVLostTimeSeries, totalVlost+Vlost)
		k = calculate_k(V0, CumVLostTimeSeries[end],solvingTimes[j+1])
		#data_dict[4] = k

		counter = counter+1
	end
	toc()
	@show CumVLostTimeSeries
	BPTimeSeries = recreateBP(BP0, CumVLostTimeSeries, V_terminal, alpha, beta)
	fig = figure("pyplot_multiaxis",figsize=(10,10))
 	plot(solvingTimes/60.0,VTimeSeries, "k")
	plot(solvingTimes/60.0,CumVLostTimeSeries, "r")
	ylabel("Blood Volume, in mL")
	ax = gca()
	setp(ax[:get_yticklabels]())
	#create secondary axis
	ax = gca()
	ax2 = ax[:twinx]()
	plot(solvingTimes/60.0, BPTimeSeries, "kx", alpha = .5)
	new_position = [-.50,0.06,0.77,0.91]
	ax2[:spines]["right"][:set_position](("axes",1.01))
	setp(ax2[:get_yticklabels]())
	ylabel("Blood Pressure, in mmHg")
	
	ax2[:set_frame_on](true) # Make the entire frame visible
	ax2[:patch][:set_visible](false) # Make the patch (background) invisible so it doesn't cover up the other axes' plots
	ax2[:spines]["top"][:set_visible](false) # Hide the top edge of the axis
	ax2[:spines]["bottom"][:set_visible](false) # Hide the bottom edge of the axis
	ax2[:get_yaxis]()[:get_major_formatter]()[:set_useOffset](false)

	fig[:canvas][:draw]() # Update the figure

	xlabel("Time in Minutes")
	

end
