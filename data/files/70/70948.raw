module Direct

using Winston

using DtPlot
using DtProtos.Pdfs

using DtProtos


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


function run_direct()
    obs = create_historic_obs(0, 20)
    
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

end



end # module
