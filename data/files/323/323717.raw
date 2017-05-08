
using Optim

function readAndProcCoinData(filename)
  data = readdlm(filename)
  ndata = length(data)
  nheads = int(zeros(ndata))
  procdata = int(zeros(ndata))
  for i=1:ndata
    nheads[i] = length(matchall(r"H", data[i]))
    procdata[i] = binomial(50, nheads[i])
  end
  return nheads, procdata
end

function sigmoid(x)
  return 1.0./(1.0.+exp(-x))
end

function bin50(k, p)
  # d here is (50 choose d)
  # println(exp(log(d) + d*log(p)  ))
  return procdata[k]*(p^nheads[k])*((1.0-p)^(50-nheads[k]))
end

function loglik(x)
  dists = Any[]
  theta = sigmoid(x[1:4])
  cs = sigmoid(x[5:end])
  ntheta = length(theta)

  cs = reshape(cs, nprocdata, 4)
  cs = cs ./ sum(cs,2)

  ll = 0
  for k=1:length(procdata)
    for i=1:ntheta
      ll += bin50(k, theta[i])*cs[k,i]
    end
  end
  ll *= -1
end

function getMeSomeMLE(procdata, theta)
  optimize(loglik, theta, show_trace=true, autodiff=true,
            method = :cg, ftol = 1e-12, iterations=5000)
end

# read in and process the data
nheads, procdata = readAndProcCoinData("coindata.txt")
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
