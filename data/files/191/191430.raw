#!/usr/bin/env julia

using sgd_local_global

function main()
	#args: trainfilename testfilename, num_passes, lambda_l1_local, lambda_l2, 	
	num_args::Int8 = 1
	#const trainfile = ARGS[num_args] ; num_args += 1
	#const testfile = ARGS[num_args] ; num_args += 1
	const num_passes = parse(Int, ARGS[num_args]) ; num_args += 1
	const lambda_l1_local = 1e-2
	const lambda_l1_global = 1e-4
	const lambda_l2 = 1e-3
	const mb_size = 10000
	println("Starting")

	trainfile = AbstractString[]
	testfile = AbstractString[]

	for i in 0:7
		push!(trainfile, "../ctra/parts/0$(i)")
		push!(testfile, "../ctra/test_old.txt")
	end

	#println(trainingfile)
	#println(testingfile)
	temp = readdlm("../ctra/features", Int)
	features = Set{Int}(temp[:, 1])

#function run_sgd(losstype::Int, k::Int, lambda_l1_local::Float64, lambda_l2::Float64, trainingfile::Vector{AbstractString}, testfile::Vector{AbstractString}, mb_size::Int, max_data_pass::Int, local_features::Set{Int})

	loss_dict = Dict("logistic" => 1, "logloss" => 1, "1" => 1, "hinge" => 2, "2" => 2, "l1svm" => 2, "svm" => 2, "sqhinge" => 3, "l2svm" => 3, "3" => 3)
	loss = "sqhinge"
	w = run_sgd(loss_dict[loss], 8, lambda_l1_local, lambda_l1_global, lambda_l2, trainfile, testfile,  mb_size, num_passes, features)
	println("Done learning")
	#acc = predict(testfile, w)
	#println("Accuracy = $(acc)")
end

main()
