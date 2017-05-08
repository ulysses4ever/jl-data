
typealias SgdModel Dict{Int, Float64}

function norm(w::SgdModel)
	n = 0.0
	for x in values(w)
		n += x^2
	end
	return sqrt(n)
end

function init_sgd(lambda_l1_local::Float64, lambda_l1_global::Float64, lambda_l2::Float64, filename::Vector{AbstractString}, mb_size::Int, k::Int)
	w_g = SgdModel()
	w_l = Vector{SgdModel}()
	mb_iter = Vector{minibatch_iter}()
	for i in 1:k
		push!(w_l, SgdModel())
		push!(mb_iter, minibatch_iter(filename[i], mb_size))
	end
	penalty_local = L1L2Penalty(lambda_l1_local, lambda_l2)
	penalty_global = L1L2Penalty(lambda_l1_global, lambda_l2)
	return w_g, w_l, mb_iter, penalty_local, penalty_global
end

function min_num_pass(mb_iter::Vector{minibatch_iter})
	m::Int = mb_iter[1].num_passes
	for i in 2:length(mb_iter)
		m = min(m,mb_iter[i].num_passes)
	end
	return m
end

function run_sgd(losstype::Int, k::Int, lambda_l1_local::Float64,lambda_l1_global::Float64, lambda_l2::Float64, trainingfile::Vector{AbstractString}, testfile::Vector{AbstractString}, mb_size::Int, max_data_pass::Int, local_features::Set{Int})
	beta_l = 1.0; alpha_l = 0.2 #defaults
	beta_g = 1.0; alpha_g = 0.99 #defaults
	eta_l = 0.0; eta_g = 0.0
	w_global::SgdModel, w_local::Vector{SgdModel}, mb_iter::Vector{minibatch_iter}, penalty_l::L1L2Penalty, penalty_g::L1L2Penalty = init_sgd(lambda_l1_local, lambda_l1_global, lambda_l2, trainingfile, mb_size, k)
	t::Float64 = 1.0
	new_iter = 0
	counter = 0
	while (new_iter < max_data_pass)
		counter += 1
		eta_l =( (beta_l + sqrt(t)) / alpha_l) #step size
		eta_g =( (beta_g + sqrt(t)) / alpha_g) #step size
		old_iter = min_num_pass(mb_iter)
		for ii in 1:k
			grad_l, grad_g = lossGradientNormalized(losstype, w_local[ii], w_global, local_features, read_mb(mb_iter[ii]))
			println("$(counter): $(ii): $(norm(grad_l)) $(norm(grad_g))")
			old_iter = min_num_pass(mb_iter)
			old_w::Float64 = 0.0
			new_w::Float64 = 0.0
			for (idx::Int, grad_val::Float64) in grad_l
				#update
				if (!∈(idx, local_features))
					println("WTF")
				end
				old_w = get(w_local[ii], idx, 0.0)
				new_w = update_model(penalty_l, old_w, grad_val, eta_l)
				if (new_w == 0.0)
					delete!(w_local[ii], idx)
				else
					w_local[ii][idx] = new_w
				end
			end
			for (idx::Int, grad_val::Float64) in grad_g
				#update
				if (∈(idx, local_features))
					println("WTF")
				end
				old_w = get(w_global, idx, 0.0)
				new_w = update_model(penalty_g, old_w, grad_val, eta_g)
				if (new_w == 0.0)
					delete!(w_global, idx)
				else
					w_global[idx] = new_w
				end
			end
      new_iter =  min_num_pass(mb_iter)
			#println("norm : $(norm(w))")
			if (new_iter != old_iter || rem(counter, 10) == 1)
				acc = predict(testfile, w_local, w_global)
				println("Iteration $(new_iter): Accuracy $(acc), Sparsity $(length(collect(keys(w_global))))")
			end	
		end
		t += one(t)
	end
	return 0
end

function predict_one(testfile::AbstractString, w_local::SgdModel, w_global::SgdModel)
	correct::Int = 0
	total::Int = 0
	fout = open(testfile, "r")
	has_value = true
	ix = 0; e = 0.0; 
	for line in eachline(fout)
		dotp = 0.0
		ix = findfirst(line, ' ')
		y = parse(Int, strip(line[1:ix-1]))
		if (y != 1)
			y = -1
		end
		tokens = split(strip(line[ix+1:end]), ' ')
		for token in tokens
			colon_ix = findfirst(token, ':')
			if (colon_ix != 0)
				ix = parse(Int, token[1:colon_ix-1])
				e = parse(Float64, token[colon_ix+1:end])
			else
				ix = parse(Int, strip(token))
				e = 1.0
			end
			dotp += (get(w_local, ix, 0.0) + get(w_global, ix, 0.0)) * e
		end
		if (sign(dotp) == y)
			correct += 1
		end
		total += 1
	end
	println("$(correct)/$(total)")

	return correct, total	
end


function predict(testfile::Vector{AbstractString}, w_local::Vector{SgdModel}, w_global::SgdModel)
	correct = 0
	total = 0
	for i in 1:length(testfile)
		c1, t1 = predict_one(testfile[i], w_local[i], w_global)
		correct += c1
		total += t1
	end
	println("Final: $(correct)/$(total)")
	return correct/total	
end

