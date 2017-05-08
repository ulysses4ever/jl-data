using MCMC

#Define our likelihood as a simple 2D Gaussian
function lnprob(v)
    -dot(v,v)
end

mod = MCMCLikModel(lnprob, init=ones(3), scale=ones(3))

mychain = run(mod, RWM(1.0), SerialMC(steps=50000, burnin=10000))

println("Calling acceptance")
println(acceptance(mychain))

describe(mychain)

#println(std(mychain))
