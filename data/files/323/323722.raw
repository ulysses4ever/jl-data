using Distributions
using Optim

function readAndProcCoinData(filename)
 data = readdlm(filename)
 ndata = length(data)
 heads = zeros(ndata)
 for i=1:ndata
   heads[i] = length(matchall(r"H", data[i]))
 end
 return int64(heads)
end

function sigmoid(x)
 return 1.0./(1.0.+exp(-x))
end

function loglik(x)
 dists = Any[]
 theta = x[1:4]
 cs = x[5:end]
 ntheta = length(theta)
 N = 50
 for i=1:ntheta
   push!(dists, Binomial(N, sigmoid(theta[i])))
 end

 cs = reshape(cs, nprocdata, 4)
 cs = sigmoid(cs)
 cs = cs ./ sum(cs,2)

 ll = 0
 for k=1:length(procdata)
 for i=1:ntheta
   ll += logpdf(dists[i], procdata[k])*cs[k,i]
 end
 end
 ll *= -1
end

function getMeSomeMLE(procdata, theta)
 optimize(loglik, theta, show_trace=true, method = :bfgs, ftol = 1e-12, iterations=5000)

end

# read in and process the data
procdata = readAndProcCoinData("coindata.txt")
nprocdata = length(procdata)

# optimize and return the maximum likelihood estimates
theta = rand(4)
cs = rand(nprocdata*4)
x = [theta; cs]
results = getMeSomeMLE(procdata, x)
x_opt = results.minimum
theta_opt = x_opt[1:4]
cs_opt = x_opt[5:end]
println("Maximum Likelihood Estimates: ", sigmoid(theta_opt))
