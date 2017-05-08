#!/usr/bin/env julia

using sgd_local_global

function main()
	#args: dataset expt numPart numPasses 	
	num_args::Int8 = 1
	#const trainfile = ARGS[num_args] ; num_args += 1
	#const testfile = ARGS[num_args] ; num_args += 1
  const dataset = ARGS[num_args] ; num_args += 1 
  const expt = parse(Int, ARGS[num_args]) ; num_args += 1
  const numPart = parse(Int, ARGS[num_args]) ; num_args += 1
	const num_passes = parse(Int, ARGS[num_args]) ; num_args += 1
  if (length(ARGS) < num_args)
    lg_1_or_2 = 2.0
  else
    lg_1_or_2 = parse(Float64, ARGS[num_args]) ; num_args += 1
  end

  #params: lg_1_or_2, lambda_l1_l, lambda_l1_g, lambda_l2, alpha_l, alpha_g, beta, reset_time, t_factor, accuracy_step
  #reset_time: default value is Inf;
  #t_factor: default value is 1
  println(lg_1_or_2)
  if (dataset == "ctra")
    if (lg_1_or_2 == 1)
      params = [lg_1_or_2 1e-2 1e-3 1e-4 0.2 1 1 Inf 5 30] 
    else
      params = [lg_1_or_2 1e-2 1e-3 1e-4 0.09 0.09 1 Inf 5 30]
    end
  elseif (dataset == "criteo_s")
    if (lg_1_or_2 == 1)
      params = [lg_1_or_2 5e-4 5e-5 1e-4 0.6 600 1 200 1 100] 
    else
      params = [lg_1_or_2 5e-4 5e-5 1e-4 0.8 0.8 1 200 1 100]
    end
  else
    println("Supply parameters!")
    return
  end

  lambda_l1_local = params[2]
  lambda_l1_global = params[3]
	lambda_l2 = params[4]
	const mb_size = 5000
  #params[5:6] = params[5:6] * mb_size / 1e4
	println("Starting: lambda_l1_local = $(lambda_l1_local) ; lambda_l1_global = $(lambda_l1_global) ; lambda_l2 = $(lambda_l2)")
  println("mb_size: $(mb_size)")

	trainfile = AbstractString[]
	testfile = AbstractString[]
  #numPart = 8
	for i in 0:(numPart-1)
		#push!(trainfile, "../ctra/parts/0$(i)")
    push!(trainfile, "../../learn/data/$(dataset)/experiment$(expt)/dispatched/train/$(i)_train.txt")
		push!(testfile, "../../learn/data/$(dataset)/experiment$(expt)/dispatched/test/$(i)_train.txt")
	end

	#println(trainingfile)
	#println(testingfile)
	temp = readdlm("../../learn/data/$(dataset)/features", UInt64)
	features = Set{UInt64}(temp[:, 1])

#function run_sgd(losstype::Int, k::Int, lambda_l1_local::Float64, lambda_l2::Float64, trainingfile::Vector{AbstractString}, testfile::Vector{AbstractString}, mb_size::Int, max_data_pass::Int, local_features::Set{Int})

	loss_dict = Dict("logistic" => 1, "logloss" => 1, "1" => 1, "hinge" => 2, "2" => 2, "l1svm" => 2, "svm" => 2, "sqhinge" => 3, "l2svm" => 3, "3" => 3)
	loss = "sqhinge"
	w = run_sgd(loss_dict[loss], numPart, lambda_l1_local, lambda_l1_global, lambda_l2, trainfile, testfile,  mb_size, num_passes, features, params)
	println("Done learning")
	#acc = predict(testfile, w)
	#println("Accuracy = $(acc)")
end

main()
