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
    cats
end

function MixInit(d::Int,N::Int,lims,dist="normal",scale = 0.2)
    phi = ones(N)/N
    out = GAMix(d,phi,Any[])
    if dist == "normal"
        mu_dist = MvNormal(lims,eye(d)*3)
    end
    if dist == "uniform"
        dims = Any[Uniform(dim[1],dim[2]) for dim in lims]
    end
    for i=1:N
        if dist == "normal"
            mu = rand(mu_dist)
        end
        if dist == "uniform"
            mu = [rand(dims[i]) for i in length(dims)]
        end
        sigma = eye(d)*scale
        out.cats = cat(1,out.cats,Any[GAGauss(d,mu,sigma)])
    end
    return out
end

function update(G::GAGauss,x,resp,rate)
    G.sigma += rate*resp*((x-G.mu)*(x-G.mu)'- G.sigma)
    G.mu += rate*resp*(x-G.mu)
end

function update(M::GAMix,x,rate)
    p_r = Any[MvNormal(G.mu,G.sigma) for G in M.cats];
    resp = [M.phi[i]*pdf(p_r[i],x) for i=1:length(p_r)]
    resp = resp/sum(resp)
    for i=1:length(M.cats)
        update(M.cats[i],x,resp[i],rate)
    end
    winner = indmax(resp)
    M.phi[winner] += rate
    prune = M.phi .> 0.0005;
    M.cats = M.cats[prune];
    M.phi = M.phi[prune];
    M.phi = M.phi/sum(M.phi)
end




#-----------------------------------------------------------------------------------------------------
# classification of new data:
function classify(M::GAMix,data,dims)
    labels = Array(Float64,size(data,2),1);
    for i=1:size(data,2)
        x = data[dims,i];
        p_r = Any[MvNormal(G.mu,G.sigma) for G in M.cats];
        resp = [M.phi[i]*pdf(p_r[i],x) for i=1:length(p_r)]
        resp = resp/sum(resp)
        labels[i] = indmax(resp);
    end
    return labels
end


#-----------------------------------------------------------------------------------------------------
# Batch Simulation:
function simMix(nSims::Int,nX::Int,d,rate,data,dims)
    mix1 = [MixInit(d,1000,repmat([0.],d),"normal",0.02) for i=1:nSims];
    for i=1:nSims
           for j=1:nX
               update(mix1[i],data[dims,j],rate);
           end
           if nSims > 100
               if i % 100 == 0
                   print(i,", ")
               end
           end
    end
    return mix1
end

# Batch Simulation with previously trained models:
function simMix(m,nSims::Int,nX::Int,d,rate,data,dims)
    for i=1:nSims
           for j=1:nX
               update(m[i],data[dims,j],rate);
           end
           if nSims > 100
               if i % 100 == 0
                   print(i,", ")
               end
           end
    end
    return m
end

#--------------------------------------------------------------------------------------------------------------
# sampling

function sample(c::GAGauss)
    return rand(MvNormal(c.mu,c.sigma));
end

function sample(m::GAMix,n)
    out = Array(Float64,m.d+1,n);
    for i=1:n
        cat_i = indmax(rand(Multinomial(1,float(m.phi))));
        out[:,i] = vcat(sample(m.cats[cat_i]),cat_i);
    end
    return out
end