module LossLocalGlobal

importall rowblock
export loss, lossGradient, lossGradientNormalized

typealias SgdModel Dict{UInt64, Float64}

#abstract loss

function loss(losstype::Int, x::Float64)

	if (losstype == 1)
		return log(1 + exp(-x))

	elseif (losstype == 2)
		return max(0, 1-x)

	elseif (losstype == 3)
		return max(0, 1-x)^2

	else
		println(STDERR, "unknown loss")
	end
end

function loss(losstype::Int, w::SgdModel, mb::RowBlock)
	res = 0
	for i in 1:size(m)
		r = mb[i]
		res += loss(losstype, r.label * dot(r, w))	
	end
	return res
end

function lossGradient(losstype::Int, x::Float64)
	if (losstype == 1)
		return -1.0/(1.0+exp(x))

	elseif (losstype == 2)
		if (x > 1.0)
			return 0.0
		else
			return -1.0
		end

	elseif (losstype == 3)
		if (x > 1.0)
			return 0.0
		else
			return 2.0*(x-1.0)
		end

	else
		println(STDERR, "unknown loss")
	end
end

function lossGradient(losstype::Int, wlocal::SgdModel, wglobal::SgdModel, local_features::Set{UInt64}, mb::RowBlock, lg_type=2.0)
	grad_l = Dict{UInt64, Float64}()
	grad_g = Dict{UInt64, Float64}()
	for ii in 1:size(mb)
		r = mb[ii]
		lossD = lossGradient(losstype, r.label * (dot(r, wlocal) + dot(r, wglobal)))
		for j in 1:size(r)
			idx = r.idxs[j]
			val = get_value(r, j) * r.label * lossD
			if (∈(idx, local_features) || (length(local_features) == 1))
				grad_l[idx] = get(grad_l, idx, 0.0) + val
        if (lg_type == 2)
			    grad_g[idx] = get(grad_g, idx, 0.0) + val
        end
			else 
			  grad_g[idx] = get(grad_g, idx, 0.0) + val
			end	
			#grad_g[idx] = get(grad_g, idx, 0.0) + val
		end
	end
	return grad_l, grad_g
end

function lossGradientNormalized(losstype::Int, wlocal::SgdModel, wglobal::SgdModel, local_features::Set{UInt64}, mb::RowBlock, lg_type=2.0)
	grad_l = Dict{UInt64, Float64}()
	grad_g = Dict{UInt64, Float64}()
	for ii in 1:size(mb)
		r = mb[ii]
		lossD = lossGradient(losstype, r.label * (dot(r, wlocal) + dot(r, wglobal)))
		for j in 1:size(r)
			idx = r.idxs[j]
			val = get_value(r, j) * r.label * lossD
			if (∈(idx, local_features) || (length(local_features)==1))
				grad_l[idx] = get(grad_l, idx, 0.0) + val/size(mb)
        if (lg_type == 2)
			    grad_g[idx] = get(grad_g, idx, 0.0) + val/size(mb)
        end
			else 
			  grad_g[idx] = get(grad_g, idx, 0.0) + val/size(mb)
			end	
		end
	end
	return grad_l, grad_g
end


end #module
