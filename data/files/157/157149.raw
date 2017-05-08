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

## function LTF(u, C_F):
##     return (20.0/9.0) * C_F * sign(u) * pow(abs(u),1.0/3.0);

## function ATF(u, C_F):
##     return (5.0/9.0) * C_F * pow(abs(u), 4.0/3.0)

function buildA(v, vo)
    # 
    info("Building A")
    #B = Array(2*npts, 2*npts)
    #B = zeros(2*npts, 2*npts)
    #B = diagm(ones(2*npts))
   B = speye(2*npts, 2*npts)
        
    # u rows
    for m = [3:2:2*npts-2]
        u   = v[m]
        phi = v[m+1]
        uo  = vo[m]
        twouo = 2 * uo
        B[m,m]   = kappa/dt 
                   -twouo * C_W * (1./uo) * (-2.0)
        B[m,m+2] = twouo* - C_W * (1./uo) * (+1.0) # W
        B[m,m-2] = twouo* - C_W * (1./uo) * (+1.0) # W
        B[m,m+1] = twouo* -1.0                        # -phi
    end     
    # phi rows
    for m = [4:2:2*npts-2]
        u = v[m-1]
        B[m,m-1] = -2 * u # LU2 
        B[m,m+2] = (1./4*pi) * (1.0 / dx^2)      # phi_p
        B[m,m  ] = (1./4*pi) * (-2  / dx^2)      # phi_o
        B[m,m-2] = (1./4*pi) * (1.0 / dx^2)      # phi_m
    end
   
    #A = spdiagm(B, d[, m, n])
    #A = Sparse(I, J, V)
    #return sparse(B)
    return B
end

function buildF(v, vo, mu) 
    # The function
    info("Building F")
    F = zeros(npts*2)
    # u rows
    for m = [3:2:2*npts-2]
        u  = v[m]
        uo = vo[m]
        twouo = 2*uo
        F[m] = kappa*u/dt - twouo * mu
    end
    # phi rows
    for m = [4:2:2*npts-2]
        u = v[m-1]
        mesh_idx = (m)/2
        bi = b[mesh_idx]
        F[m] = -bi + -u.*u
        
    end
    println("is b sign right?")
    return F
end

function solve(A, F) 
    info("Solve")
    #v = Sparsesolve(A,F)
    v = \(A,F)
    return v
end

function updateMu(mu, v) 
    u = v[1:2:end]
    intu2 = sum(u .* u) #* dx
    println("dx here?")
    mu += omega * (intu2 - sum(b))
    return mu
end
    
function createmesh_uniform(x, npts) 
    # create "optimal" mesh that includes t2m points
    xmin = minimum(x) 
    xmax = maximum(x)
    range = xmax - xmin
    xmin = xmin - 0.5*range
    xmax = xmax + 0.5*range
    dx = (xmax - xmin) / (npts - 1)
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
    #return b / length(w)
    return b / sum(b)  
end
    
function uniform(x,N) 
    return ones(length(x)) / length(x)
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
    #[plot(pp/3600, t2m[1:end,1,i], "ko-") for i=[1:size(t2m)[3]]]
    #show()
        
    #t2m= sort(flatten(t2m[5,1,:])) # pp=1, bt=1, all ens mems
    t2m = sort(flatten(t2m[15,1,:])) # pp=1, bt=1, all ens mems
    sigma = 0.05 * 3 #1.0
    # use srot to generate this 
    #N = length(t2m)  #1   
    npts = 101 #10000 #10*N
    kappa = 1.0
    dt = 200.0
    C_W = 0.0 
    dt = 1.0
    C_W =  0.00001
    #omega = 0.0001
    omega = 0.1
    mu = 0.0 #0.1

    figure()
    
    x = createmesh_uniform(t2m, npts)
    dx = x[2] - x[1]
    b = buildatoms(x, t2m, sigma, 1.0)
    b = abs(b)
    b = b - minimum(b)
    #b = -1*b

    subplot(224)
    axhline(abs(sum(b)))

    u = sqrt(buildatoms(x, t2m, sigma*8, 1.0))
    #u = sqrt(buildatoms(x, t2m, sigma*2, 1.0))
    #u = uniform(x, 1)
    #p = gaussian(t2m, x)
    p = uniform(x, 1)
    

    subplot(221)
    plot(x,b);title("b")
    plot(x,map((ui) -> ui^2, u), "o-"); title("u^2")
    [axvline(x=xi,color="red") for xi=t2m]
    draw()
    sleep(1)

    v = zeros(length(x)*2)
    v[1:2:end] = u
    v[2:2:end] = p
    vo = v
    #v = flatten(collect(zip(u,p)))
    println(v)
    ncount = -1
    maxcount = 100-1
    while ncount < maxcount
        ncount += 1
        F  = buildF(v, vo, mu)
        A  = buildA(v, vo)
        vo = v
        v  = solve(A, F)
        
        ## d  = solve(A, F)
        ## vo = v
        ## v = v +d
        
        subplot(221); delaxes(); subplot(221)
        plot(x,b)
        [axvline(x=xi,color="red") for xi=t2m]
        plot(x, map((ui) -> ui^2, vo[1:2:end]), "k-"); title("u^2")
        plot(x, map((ui) -> ui^2, v[1:2:end]), "o-"); title("u^2")
        draw()
        sleep(0.001)
        
        subplot(223); delaxes(); subplot(223) 
        plot(x, map((ui) -> ui^2, v[2:2:end]), "o-"); title("phi")
        draw()
        #sleep(1)


        v[1] = v[3]
        v[end-1] = v[end-3]
        v[2] = v[4]
        v[end-0] = v[end-2]
        
        
        mu = updateMu(mu, v)
        println( mu)
        subplot(222)
        plot(ncount, mu, "ro")
        
        subplot(224)
        plot(ncount, sum(v[1:2:end].*v[1:2:end]), "ko")
        
        
    end    
        
end # module
