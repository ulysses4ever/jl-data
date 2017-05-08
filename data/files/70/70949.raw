module Direct

using Winston

using DtPlot
using DtProtos.Pdfs

using DtProtos


function buildA(f, fo)
    info("Building A")
    

end

"""
maximise ... blah

"""
function maximise()
    # blah
    info("Maximise")
    niter = -1
    nmax = 20
    while niter < nmax
        n += 1
        
    end
end


#-----------------------------
# From here down move to separate file

function create_candidate(mu, sigma, weight)
    n = GaussianPdf(mu, sigma, weight)
end

""" 
Create historical forecasts. 
 
"""

function create_historic_obs(d1, dn)
    # 0,100
    dates = [d1:dn]
    obs = sin(dates)
    return obs 
end


function create_historic_forecasts(obs::Array{Float64}, 
                                   errmu::Float64, errsig::Float64)
    fs = SimplePdf[]
    for o in obs
        mu = o + errmu*(rand() - 0.5)
        sig = errsig*rand()
        p = GaussianPdf(mu, sig, 1)
        push!(fs, p) # list of simplePdfs
    end
    return fs
end

function expected_score(obs::Array{Float64}, fs::Array{SimplePdf}, score)
    #as = Array{Float64}
    as = Float64[]
    n = length(obs)
    for i in [1:n]
        o = obs[i]
        f = fs[i]
        a = score(f,o)
        #println(a)
        push!(as, a)
    end
    A = mean(as)
end

function ign(p::SimplePdf, o::Float64)
    if isinf(-log(pdf(p,o)))
        println(o, ", ", p.mu, ", ", p.sigma, ", ", pdf(p,o))
    end
    return -log(pdf(p,o))
end


function buildF(fo, ao, lambda, mu) # B1T, B2
    info("Building F")
    F = zeros(nX)
    for i = [1:1:nX]
        g = (1/tau) * fo[i] .* log(fo[i])
        # for j = [1:1:ncAND]
        #     B1Tyk = a .* 
        # end
    end
    
end

function buildA()
    info("Building A")
    A = speye(nX)
    A = A ./ tau
end

function solve(A, F)
    info("Solve")
    blas_set_num_threads(16)
    #v = Sparsesolve(A,F)
    f = \(A, F)
    return f

end

function updateLambda(lambda, f, a)
    for i in [1:length(lambda)]
        lambda[i] += sum(f[i] * a[1])
    end
    return lambda
end

function updateMu(mu, f)
    intf = sum(f^2) #* dx
    mu += omega * (intf - 1)
    return mu
end


function run_direct()
    # Setup data (historic)
    #
    obs = create_historic_obs(0, 20)
    
    ncandidates = 2
    c1 = create_historic_forecasts(obs, 0.25, 2.)
    c2 = create_historic_forecasts(obs, 0.50, 1.)

    # do leaf plot here
    # date; obs, c1, c2
    fp = FramedPlot()
    fp = leaf2(fp, c1, "red")
    fp = leaf2(fp, c2, "blue")

    obsp = Points([1:length(obs)], obs, color="black")
    style(obsp, kind="circle", size=0.3)
    obsc = Curve([1:length(obs)], obs, color="grey")
    add(fp, obsp)
    add(fp, obsc)    

    A1 = expected_score(obs, c1, ign)
    A1p = Slope(0, (0,A1), kind="dotted", color="red")
    setattr(A1p, label="A1")
    add(fp, A1p)
    println("------",A1)

    A2 = expected_score(obs, c2, ign)
    A2p = Slope(0, (0,A2), kind="dotted", color="blue")
    setattr(A2p, label="A2")
    add(fp, A2p)
    println("------",A2)

    l = Legend(.1, .9, {A1p, A2p})
    add(fp,l)
    
    display(fp)

    # Setup numerics
    #
    # X: observation domain (and space over which integration done)
    dobs = maximum(obs) - minimum(obs)
    obsrange = [minimum(obs)-dobs : maximum(obs)+dobs] # ie X
    X = obsrange
    nX = length(X)

    # # Main loop
    # #
    # f1 = zeros(X)
    # f0 = f1
    # mu = 0.
    # lambda = zeros(ncadidates)
    # tau = 1.0
    # ncount = -1
    # while ncount < maxcount
    #     ncount += 1
    #     F  = buildF(f, fo, mu)
    #     A  = buildA(f, fo)
    #     fo = f
    #     f  = solve(A, F)

    #     f[1] = f[2]
    #     f[end-1] = f[end-2]
        
    #     mu = updateMu(mu, f)
    #     info("mu = ", mu)

    #     lambda = updateLambda(lambda, f)
    #     info("lambda = ", lambda)
    # end
end



end # module
