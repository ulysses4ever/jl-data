importall ParameterServer
typealias SgdModel Dict{UInt64, Float64}

function norm(w::SgdModel)
	n = 0.0
	for x in values(w)
		n += x^2
	end
	return sqrt(n)
end

function init_sgd(lambda_l1_local::Float64, lambda_l1_global::Float64, lambda_l2::Float64, filename::Vector{AbstractString}, mb_size::Int, k::Int)
	ps_g = init_PS(lambda_l1_global, lambda_l2)
	ps_l = Vector{PS}()
	mb_iter = Vector{minibatch_iter}()
	for i in 1:k
		push!(ps_l, init_PS(lambda_l1_local, lambda_l2))
		push!(mb_iter, minibatch_iter(filename[i], mb_size))
	end
	return ps_g, ps_l, mb_iter
end

function min_num_pass(mb_iter::Vector{minibatch_iter})
	m::Int = mb_iter[1].num_passes
	for i in 2:length(mb_iter)
		m = min(m,mb_iter[i].num_passes)
	end
	return m
end

function run_sgd(losstype::Int, k::Int, lambda_l1_local::Float64,lambda_l1_global::Float64, lambda_l2::Float64, trainingfile::Vector{AbstractString}, testfile::Vector{AbstractString}, mb_size::Int, max_data_pass::Int, local_features::Set{UInt64}, params)


  println("beta:$(params[7]) alpha_l: $(params[5]) alpha_g: $(params[6])  t-factor: $(params[9])  reset: $(params[8])  ")

	beta_l = params[7]; alpha_l = params[5] #defaults
	beta_g = params[7]; alpha_g = params[6] #defaults
	eta_l = 0.0; eta_g = 0.0
	ps_global::PS, ps_local::Vector{PS}, mb_iter::Vector{minibatch_iter} = init_sgd(lambda_l1_local, lambda_l1_global, lambda_l2, trainingfile, mb_size, k)
	t::Float64 = 1.0
	new_iter = 0
	counter = 0
	while (new_iter < max_data_pass)
		counter += 1
		eta_l =( (beta_l + sqrt(t/params[9])) / alpha_l) #step size
		eta_g =( (beta_g + sqrt(t/params[9])) / alpha_g) #step size
		old_iter = min_num_pass(mb_iter)
		for ii in 1:k
			mb = read_mb(mb_iter[ii])
			#pull
			req_ks = unique(mb.idxs)
			w_ks, w_vals = pull(ps_global, req_ks)
			w_g = [w_ks[i]::UInt64 => w_vals[i]::Float64 for i in 1:length(w_ks)]

			grad_l, grad_g = lossGradientNormalized(losstype, ps_local[ii].w, w_g, local_features, read_mb(mb_iter[ii]), params[1])
			println("$(counter): $(ii): $(norm(grad_l)) $(norm(grad_g))")
			old_iter = min_num_pass(mb_iter)

			#push				
			push(ps_local[ii], collect(keys(grad_l)), collect(values(grad_l)), eta_l)
			push(ps_global, collect(keys(grad_g)), collect(values(grad_g)), eta_g)

			new_iter =  min_num_pass(mb_iter)
			#println("norm : $(norm(w))")
			if (new_iter != old_iter)
				acc = predict(testfile, w_local, w_global)
				println("Iteration $(new_iter): Accuracy $(acc), Sparsity $(length(collect(keys(w_global))))")
				flush(STDOUT)
			end	
		end
		if (rem(counter, convert(Int, params[10])) == 0)
			acc = predict(testfile, ps_local, ps_global)
			println("Iteration $(new_iter): Accuracy $(acc), Sparsity $(length(collect(keys(ps_global.w))))")
			flush(STDOUT)
		end	
		t += one(t)
    if (t > params[8])
      println("RESET TIME")
      t -= params[8]/2
    end
	end
	acc = predict(testfile, ps_local, ps_global)
	println("Iteration $(new_iter): Accuracy $(acc), Sparsity $(length(collect(keys(w_global))))")
	flush(STDOUT)
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
				ix = parse(UInt64, token[1:colon_ix-1])
				e = parse(Float64, token[colon_ix+1:end])
			else
				ix = parse(UInt64, strip(token))
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


function predict(testfile::Vector{AbstractString}, ps_local::Vector{PS}, ps_global::PS)
	correct = 0
	total = 0
	for i in 1:length(testfile)
		c1, t1 = predict_one(testfile[i], ps_local[i].w, ps_global.w)
		correct += c1
		total += t1
	end
	println("Final: $(correct)/$(total)")
	return correct/total	
end

