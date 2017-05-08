using Distributions

# Sigma (for component or mixture):
# Inverse Wishart distrbution
type Sigma
    d::Int
    S
    nu::Float64
end

# Mixture component/category:
# N-dimensional Gaussian distribution
type Cat
    mu
    kappa::Float64
    sigma::Sigma
end

# Mixture:
# Mixture of d-dimensional Gaussians
type Mix
    d::Int
    a::Float64
    stick::Float64
    alpha
    phi
    cats
    sigma::Sigma
end

#------------------------------------------------------------------------------------------------------
# Utility Functions:

# Get expected value of Inverse Wishart distribution
function smean(s::Sigma)
    return s.S/(s.nu-s.d-1);
end


#------------------------------------------------------------------------------------------------------
# Sampling from mixtures:
# Sampling from Posterior distribution or using posterior means for mu and sigma
function sample(c::Cat,post=false)
    if post == true
        sigma = rand(InverseWishart(c.sigma.nu,inv(c.sigma.S)));
        mu = rand(MvNormal(c.mu,sigma/c.kappa));
        return rand(MvNormal(mu,sigma));
    else
        return rand(MvNormal(c.mu,smean(c.sigma)));
    end
end

function sample(m::Mix,n,post=true)
    out = Array(Float64,m.d+1,n);
    if post==true
        for i=1:n
            cat_i = indmax(rand(Multinomial(1,float(m.phi))));
            out[:,i] = vcat(sample(m.cats[cat_i]),cat_i);
        end
    else
        for i=1:n
            cat_i = indmax(rand(Multinomial(1,float(m.phi))));
            out[:,i] = vcat(sample(m.cats[cat_i],false),cat_i);
        end
    end
    return out
end



#------------------------------------------------------------------------------------------------------
# Updates:

function update(c::Cat,x,d)
    mu_update = c.mu*(c.kappa/(c.kappa+1)) + x*(1/(c.kappa+1));
    S_update = (((x-c.mu)*(x-c.mu)'))*c.kappa/(c.kappa+1);
    # Need to check this line.
    scaling = c.sigma.nu-d-1;
    weight = c.kappa/(c.kappa+1);
    return Any[mu_update,S_update,scaling,weight];
end

function post_pred(m::Mix,x,det=true)
    dists = Any[MvTDist(c.sigma.nu+m.d+1.0,c.mu,
             c.sigma.S*(c.kappa+1)/(c.kappa*(c.sigma.nu-m.d+1)))
             for c in m.cats];
    resp = [log(m.phi[i])+logpdf(dists[i],x) for i=1:length(dists)];
    if det == true
        # deterministically select most probable category
        return indmax(resp);
    else
        # Sample based on posterior probabilities:
        resp = exp(resp);
        resp = float(resp/sum(resp));
        return indmax(rand(Multinomial(1,resp)));
    end
end

function update(m::Mix,x)
    new = rand(Bernoulli(m.stick));
    if new != 0
        w_new = rand(Beta(1,m.a))*m.stick;
        m.stick = m.stick - w_new;
        if m.cats == [];
            m.cats = cat(1,m.cats,[Cat(x,m.alpha[1],deepcopy(m.sigma))]);
        else
            # Calculating phi for new category:
            # un-normalize current vector phi (divide by 1-current stick length)
            phi_un = m.phi*(1-m.stick);
            phi_un = cat(1,phi_un,[w_new]);
            alpha_new = (w_new/sum(phi_un))*sum(m.alpha);
            m.alpha = cat(1,m.alpha,[alpha_new]);
            # initializing categories
            nu_new = m.sigma.nu*w_new+m.sigma.d+1
            S_new = smean(m.sigma)*(nu_new-m.sigma.d-1)
            sigma_new = Sigma(m.sigma.d,S_new,nu_new);
            m.cats = cat(1,m.cats,[Cat(x,alpha_new+m.d,sigma_new)]);
        end
    else
        w_ind = post_pred(m,x,true);
        w = m.cats[w_ind];
        # calculate updates for mu, sigma
        updates = update(w,x,m.d);
        # apply for w:
        w.mu = updates[1];
        w.sigma.nu += 1; w.kappa += 1;
        # Weights for local and global covariance for update:
        weights = [w.kappa,10]; weights = weights/sum(weights)
        # apply updates:
        w.sigma.S = weights[1]*(w.sigma.S +updates[2]) + weights[2]*smean(m.sigma)*updates[3]
        m.sigma.S = m.sigma.S + ((m.sigma.nu/(m.sigma.nu+1))*updates[2])/updates[4]; m.sigma.nu += 1;
        # finish updating
        m.cats[w_ind] = w;
        m.alpha[w_ind] += 1;        
    end
    m.phi = [m.alpha[i]/sum(m.alpha) for i=1:length(m.alpha)];
    prune = m.phi .> 0.001;
    m.alpha = m.alpha[prune];
    m.cats = m.cats[prune];
    m.phi = [m.alpha[i]/sum(m.alpha) for i=1:length(m.alpha)];
end




#------------------------------------------------------------------------------------------------------
# Simulation functions:

function simMix(nSims::Int,nX::Int,alpha::Float64,s,d,n,data,dims)
    #sInit = Sigma(d, eye(d)*s, n);
    sInit = Sigma(d, eye(d)*s*(n-d-1), n);
    mix1 = [Mix(d,alpha,1,[20],[],[],deepcopy(sInit)) for i=1:nSims];
    for i=1:nSims
           for j=1:nX
               update(mix1[i],data[dims,j]);
           end
           if nSims > 100
               if i % 100 == 0
                   print(i,", ")
               end
           end
    end
    return mix1
end

function simMix(m,nSims::Int,nX::Int,alpha::Float64,s,d,n,data,dims)
    for i=1:nSims
        for j=1:nX
            update(m[i],data[dims,j]);
        end
        if nSims > 100
            if i % 100 == 0
                print(i,", ")
            end
        end
    end
    return m
end


function resetMix(m::Mix,stick,kappa,flat::Bool,alpha)
    m.stick = stick
    if flat == true
        m.alpha = [alpha for i=1:length(m.alpha)]
    else
        m.alpha = [a/alpha for a in m.alpha]
    end
    for c in m.cats
        c.kappa = kappa
    end
end

function catCount(x,N)
    n_comps = zeros(N)
    for j=1:N
        n = 0
        for i=1:length(x[j].cats)
            if x[j].phi[i] > 0.03
                n += 1
            end
        end
        n_comps[j] += n
    end
    return n_comps
end

#------------------------------------------------------------------------------------------------------
# testing functions:

function classify(m::Mix,xs,dims)
    labels = zeros(size(xs,2))
    for i=1:size(xs,2)
        labels[i] = post_pred(m,xs[dims,i])
    end
    return labels
end

function pruneMix(m::Mix,threshold)
    newMix = deepcopy(m)
    prune = newMix.phi .> threshold;
    newMix.alpha = newMix.alpha[prune];
    newMix.cats = newMix.cats[prune];
    newMix.phi = [newMix.alpha[i]/sum(newMix.alpha) for i=1:length(newMix.alpha)];
    return newMix
end