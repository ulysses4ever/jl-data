@everywhere include("HW6_Q2_planet_populations.jl")
@everywhere include("HW6_Q2_planet_populations_once.jl")

function eval_model_on_grid_map(etas::Array, shapes::Array, scales::Array, num_stars = 1600; num_evals = 1, 
                            true_eta = 0.2, true_shape = 0.1, true_scale = 1.0)
	const solar_radius_in_AU = 0.00464913034
	minP = (2.0*solar_radius_in_AU)^1.5
	maxP = 4*days_in_year/3
	data_obs = generate_transiting_planet_sample(true_eta, true_shape, true_scale, num_stars; minP=minP, maxP=4*days_in_year/3)
	stats_obs = compute_stats(data_obs)
	
	idx= [ (i,j,k) for i in 1:length(etas), j in 1:length(shapes), k in 1:length(scales) ]
	#idx= [ (i,j,k) for i in 1:length(etas), j in 1:length(shapes), k in 1:length(scales) ]
	d_idx = distribute(idx)
	proclist = procs(d_idx)
	refs = [@spawnat proclist[p] map(tuple -> evaluate_model(stats_obs, etas[tuple[1]], shapes[tuple[2]], scales[tuple[3]], num_stars, minP=minP, maxP=maxP, num_evals=num_evals),localpart(d_idx)) for p in 1:length(proclist)]
	tic()
	result = Any[]
	for p in 1:length(proclist)
		local_result = fetch(refs[p])
		println("result = ",local_result)
		#append!(result,local_result)
	end
	println("result = ",result)
	file_name = string("lab7_3_procs_",length(proclist))
	s = open(file_name,"w+")
	write(s,result)
	close(s)
	println("time to write results : ",toq())
end

array_size =3 
etas =	linspace(0.,1.,array_size)
shapes = linspace(0.01,1.,array_size)
scales = linspace(0.01,5.,array_size)
tic()
eval_model_on_grid_map(etas,shapes,scales)
println(" Process time: ", toq())
