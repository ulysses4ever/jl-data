function calculateLogProb(x,p::PrefEl)
	out = 0.0

	for i in 1:size(p.strict,1)
		d = p.data[p.strict[i,1],:] .- p.data[p.strict[i,2],:]
		varAlongD = d * p.Sigma * d'
		meanAlongD = dot(vec(d),vec(x))
		temp = Normal(0,sqrt(varAlongD[1]))
		out += logcdf(temp,meanAlongD)
	end

	for i in 1:size(p.indif,1)
		d = p.data[p.indif[i,1],:] .- p.data[p.indif[i,2],:]
		varAlongD = (d * p.Sigma * d')[1]
		meanAlongD = dot(vec(d),x)
		temp = Normal(0,sqrt(varAlongD))
		out += log(cdf(temp,meanAlongD + 0.5) - cdf(temp,meanAlongD - 0.5))
	end

	return out + logPrior(x,p.priors)
end

function logPrior{R <: Real}(x::Vector{R}, priors::Vector{Distribution})
	out = 0.0
	@simd for i in 1:length(x)
		if typeof(priors[i]) != Uniform || priors[i].a != -Inf
			@inbounds out += logpdf(priors[i],x[i])
		end
	end
	return out
end

using NLopt
function infer(p::PrefEl)
	n = size(p.data,2)
	opt = Opt(:LN_NEWUOA,n)
	xtol_rel!(opt,1e-4)
	
	f(x,grad) = calculateLogProb(x,p)
	max_objective!(opt,f)

	means = zeros(F,n)
	for i in 1:n
		means[i] = mean(p.priors[i])
		if isnan(means[i])
			means[i] = 0.0
		end
	end

	minF, maxX, ret = optimize(opt,means)

	return maxX
end