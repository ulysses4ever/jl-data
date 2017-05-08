# Mixture component
type GAGauss
    d
    mu
    sigma
end


# Mixture
type GAMix
    d::Int
    phi
    components
end

function MixInit(d::Int,N::Int,lims,dist="normal",scale = 0.2)
    phi = ones(N)/N
    out = GAMix(d,phi,{})
    if dist == "normal"
        mu_dist = MvNormal(lims,eye(d)*3)
    end
    if dist == "uniform"
        dims = {Uniform(dim[1],dim[2]) for dim in lims}
    end
    for i=1:N
        if dist == "normal"
            mu = rand(mu_dist)
        end
        if dist == "uniform"
            mu = [rand(dims[i]) for i in length(dims)]
        end
        sigma = eye(d)*scale
        out.components = cat(1,out.components,{GAGauss(d,mu,sigma)})
    end
    return out
end

function update(G::GAGauss,x,resp,rate)
    G.sigma += rate*resp*((x-G.mu)*(x-G.mu)'- G.sigma)
    G.mu += rate*resp*(x-G.mu)
end

function update(M::GAMix,x,rate)
    p_r = {MvNormal(G.mu,G.sigma) for G in M.components};
    resp = [M.phi[i]*pdf(p_r[i],x) for i=1:length(p_r)]
    resp = resp/sum(resp)
    for i=1:length(M.components)
        update(M.components[i],x,resp[i],rate)
    end
    winner = indmax(resp)
    M.phi[winner] += rate
    M.phi = M.phi/sum(M.phi)
end
