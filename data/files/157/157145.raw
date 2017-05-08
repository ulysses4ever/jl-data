module DensityJenerator

# package code goes here
using NetCDF
using Logging
using PyPlot

Logging.configure(level=INFO)
#export bla


flatten{T}(a::Array{T,1}) =
    any(map(x->isa(x,Array),a))? flatten(vcat(map(flatten,a)...)): a
flatten{T}(a::Array{T}) = reshape(a,prod(size(a)))
#flatten(a)=a

#works for both cases and mixed cases like
#flatten({3,zeros(2,2,2),{2,3,{1,zeros(2,2)}}})


function buildA(v)
    # 
    info("Building A")
    A = Sparse(I, J, V)
    return A
end

function buildF(v, vo, mu) 
    # The function
    info("Building F")
    F = zeros(npts*2)
    # u rows
    ## for m = [3:2:2*npts-3]
    ##     u  = v[m]
    ##     uo = vo[m]
    ##     twouo = 2*uo
    ##     F[m] = kappa*u/dt - twouo * mu

    # phi rows
    for m = [4:2:2*npts-3]
        u = v[m-1]
        println(u)
        #mesh_idx = int(m/2)
        mesh_idx = (m)/2
        #println("m,mesh_idx $(m), $(mesh_idx)")
        bi = b[mesh_idx]
        #println("b=$(b)")
        F[m] = bi + -u^2

    end
    return F
end

function solve(A, F) 
    info("Building A")
    v = Sparsesolve(A,F)
    return v
end

function updateMu(mu, v) 
    u = v[1:2:end]
    intu2 = sum(u^2) * dx
    mu += omega * (intu2 - N)
    return mu
end
    
function createmesh_uniform(x, npts) 
    # create "optimal" mesh that includes t2m points
    xmin = minimum(x) 
    xmax = maximum(x)
    range = xmax - xmin
    xmin = xmin - 0.5*range
    xmax = xmax + 0.5*range
    dx = (xmax - xmin) / npts
    return [xmin:dx:xmax]
end

function createmesh_nonuniform(w, npts) 
    # create "optimal" mesh that includes t2m points
    min = min(w) 
    max = max(w)
    dw = diff(w)
    error("Implementation not finished")
    return dw
end
    
function gaussian(x, x0, sigma, N) 
    # array, float, float, float
    k = 1 / (sqrt(2 * pi * sigma^2))
    a = -1.0 / (2 * sigma^2)
    r = x - x0
    r2 = map((ri) -> ri^2, r)
    return N * k * exp(a * r2)
end

function buildatoms(x, w, sigma, N)
    # grid vec, variable vec, float, float
    b = zeros(length(x))
    for pt = w
        b += gaussian(x, pt, sigma, N)
    end
    return b
end
    
function uniform(x,N) 
    return ones(length(x)) / N
end
    
function buildpotential(b)
    # solve poisson with b
    error("")
end
    
    
    
    path = "/home/jade/.julia/v0.3/DensityJenerator/test/03647-14022512.nc"
    t2m = ncread(path, "t2m")
    pp  = ncread(path, "prognosis_period")
    println("Data loaded")
    #@info("Logger set to info")
    info("Logger set to info")
    info("t2m: $(size(t2m))")
    info("pp : $(size(pp))")
    
    #[plot(pp,t2m[1:end,1,i]) for i=[1:20]]
    [plot(pp/3600, t2m[1:end,1,i], "ko-") for i=[1:size(t2m)[3]]]
    show()
        
    t2m = sort(flatten(t2m[5,1,:])) # pp=1, bt=1, all ens mems
    sigma = 0.005 #1.0
    #N = length(t2m) # or just 1
    N=1   
    omega = 1
    npts = 10000 #10*N
    kappa
    
    x = createmesh_uniform(t2m, npts)
    b = -buildatoms(x, t2m, sigma, N) 
    u = sqrt(buildatoms(x, t2m, sigma, N))
    #p = gaussian(t2m, x)
    p = uniform(x, N)
    mu = 0
    
    #figure();plot(x,b);title("b")
    figure();plot(x,map((ui) -> ui^2, u), "o-"); title("u^2")
    [axvline(x=xi,color="red") for xi=t2m]
    show()
    
    v = zeros(length(x)*2)
    v[1:2:end] = u
    v[2:2:end] = p
    #v = flatten(collect(zip(u,p)))
    println(v)
    ncount = -1
    maxcount = 1
    while ncount < maxcount
        ncount += 1
        vo = v
        F  = buildF(v, vo, mu)
        #A  = buildA(v, vo)
        #v  = solve(A, F)
        #mu = updateMu(mu, v)
    end    
        
end # module
