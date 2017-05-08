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
  #println("$(num_args) $(length(ARGS))")
  if (length(ARGS) < num_args)
    lg_1_or_2 = 2.0
  else
    lg_1_or_2 = parse(Float64, ARGS[num_args]) ; num_args += 1
  end

  if (length(ARGS) < num_args)
    num_f = 10007
  else
    num_f = parse(Float64, ARGS[num_args]) ; num_args += 1
  end

  #params: lg_1_or_2, lambda_l1_l, lambda_l1_g, lambda_l2, alpha_l, alpha_g, beta, reset_time, t_factor, accuracy_step
  #reset_time: default value is Inf;
  #t_factor: default value is 1
  println(lg_1_or_2)
  if (dataset == "ctra")
    if (lg_1_or_2 == 1)
      if (num_f < 100)
        xxx = 0.2
      else
        xxx = 1 #larger learning rate for non-local features, but only if numf is large
      end
      params = [lg_1_or_2 1e-2 1e-3 1e-4 0.2 xxx 1 Inf 5 30] 
    else
      params = [lg_1_or_2 1e-2 1e-3 1e-4 0.12 0.12 1 Inf 5 30] #change 0.2 to 0.09
    end
  elseif (dataset == "ctrb")
    if (lg_1_or_2 == 1)
      params = [lg_1_or_2 5e-3 5e-4 1e-4 0.09 0.9 1 Inf 5 30] 
    else
      params = [lg_1_or_2 5e-3 5e-4 1e-4 0.09 0.09 1 Inf 5 30]
    end
 
  elseif (dataset == "criteo_s")
    if (lg_1_or_2 == 1)
      params = [lg_1_or_2 5e-4 5e-5 1e-4 0.8 600 1 Inf 1 100] 
    else
      params = [lg_1_or_2 5e-4 5e-5 1e-4 0.8 0.8 1 Inf 1 100] #change Inf to 200
    end
  else
    println("Supply parameters!")
    return
  end

  lambda_l1_local = params[2]
  lambda_l1_global = params[3]
	lambda_l2 = params[4]
	const mb_size = 10000
  #params[5:6] = params[5:6] * mb_size / 1e4
	println("Starting: lambda_l1_local = $(lambda_l1_local) ; lambda_l1_global = $(lambda_l1_global) ; lambda_l2 = $(lambda_l2)")
  println("mb_size: $(mb_size)")

	trainfile = AbstractString[]
	testfile = AbstractString[]
  #numPart = 8
	for i in 0:(numPart-1)
    push!(trainfile, "../../learn/data/$(dataset)/experiment$(expt)/dispatched/train/$(i)_train.txt")
		push!(testfile, "../../learn/data/$(dataset)/experiment$(expt)/dispatched/test/$(i)_train.txt")
	end

	#println(trainingfile)
	#println(testingfile)
	temp = readdlm("../../learn/data/$(dataset)/features", UInt64)
  if (num_f == 0)
    features = Set{UInt64}()
    println("num_f = 0; global")
  elseif (num_f >= size(temp, 1))
    features = Set{UInt64}(0) # singleton  set means all features are local
    println("num_f = infty ; fully local")
  else
	  features = Set{UInt64}(temp[1:min(num_f, size(temp, 1)), 1])
  end
#function run_sgd(losstype::Int, k::Int, lambda_l1_local::Float64, lambda_l2::Float64, trainingfile::Vector{AbstractString}, testfile::Vector{AbstractString}, mb_size::Int, max_data_pass::Int, local_features::Set{Int})

	loss_dict = Dict("logistic" => 1, "logloss" => 1, "1" => 1, "hinge" => 2, "2" => 2, "l1svm" => 2, "svm" => 2, "sqhinge" => 3, "l2svm" => 3, "3" => 3)
	loss = "sqhinge"
	w = run_sgd(loss_dict[loss], numPart, lambda_l1_local, lambda_l1_global, lambda_l2, trainfile, testfile,  mb_size, num_passes, features, params)
	println("Done learning")
	#acc = predict(testfile, w)
	#println("Accuracy = $(acc)")
end

main()
