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
        println(a)
        println(as)
        push!(as, a)
    end
    A = mean(as)
end

function ign(p::SimplePdf, o::Float64)
    return -log(pdf(p,o))
end


function run_direct()
    obs = create_historic_obs(0, 100)
    
    c1 = create_historic_forecasts(obs, 1., 1.)
    c2 = create_historic_forecasts(obs, 2., 1.)

    # do leaf plot here
    # date; obs, c1, c2
    leaf(c1,"baz")

    
    A1 = expected_score(obs, c1, ign)
    


end



end # module
