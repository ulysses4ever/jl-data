using Distributions

# Sigma (for component or mixture):
# Inverse Wishart distrbution
type Sigma
    d::Int
    S
    nu
end

# Mixture component/category:
# N-dimensional Gaussian distribution
type Cat
    mu
    kappa
    sigma::Sigma
end

# Mixture:
# Mixture of d-dimensional Gaussians
type Mix
    d::Int
    a
    stick
    alpha
    phi
    cats
    sigma::Sigma
end

#------------------------------------------------------------------------------------------------------
# Utility Functions:

# Get expected value of Inverse Wishart distribution
function mean(s::Sigma)
    return s.S/(s.nu-s.d-1);
end


#------------------------------------------------------------------------------------------------------
# Sampling from mixtures:
# Sampling from Posterior distribution or using MAP estimates (probably. Not quite sure about MAP for NW^-1)
function sample(c::Cat,post=true)
    if post == true
        sigma = rand(InverseWishart(c.sigma.nu,c.sigma.S));
        mu = rand(MvNormal(c.mu,s.sigma.S/c.kappa));
        return rand(MvNormal(mu,sigma));
    else
        return rand(MvNormal(c.mu,mean(c.sigma)));
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
            out[:,i] = vcat(sample(m.cats[cat_i],post=false),cat_i);
        end
    end
end



#------------------------------------------------------------------------------------------------------
# Updates:

function update(m::Mix,x,reg::Float64)
    new = rand(Bernoulli(m.stick));
    if bool(new)
        w_new = rand(Beta(1,m.a))*m.stick;
        m.stick = m.stick - w_new;
        if m.cats == {};
            m.cats = cat(1,m.cats,{Cat(x,m.alpha[1],m.sigma)});
        else
            # Calculating phi for new category:
            # un-normalize current vector phi (divide by 1-current stick length)
            phi_un = m.phi/(1-m.stick);
            phi_un = cat(1,phi_un,{w_new});
            alpha_new = (w_new/sum(phi_un))*sum(m.alpha);
            m.alpha = cat(1,m.alpha,{alpha_new});
            sigma_new = m.sigma;
            m.cats = cat(1,m.cats,{Cat(x,alpha_new+m.d,sigma_new)});
        end
    else
        post_pred = {MvTDist(c.sigma.nu+m.d+1.0,c.mu,
                     c.sigma.S*(c.kappa+1)/(c.kappa*(c.sigma.nu-m.d-1)))
                     for c in m.cats};
        resp = [log(m.phi[i])+logpdf(post_pred[i],x) for i=1:length(post_pred)];
        #resp = [m.phi[i]*pdf(post_pred[i],x) for i=1:length(post_pred)];
        #resp = float(resp/sum(resp));
        #w_ind = indmax(rand(Multinomial(1,resp)));
        w_ind = indmax(resp);
        w = m.cats[w_ind];
        # updates for winner here
        mu_update = w.mu*(w.kappa/(w.kappa+1)) + x*(1/(w.kappa+1));
        S_update = (((x-w.mu)*(x-w.mu)'))*w.kappa/(w.kappa+1);
        w.sigma.nu += 1;
        w.kappa += 1;
        w.sigma.S = (1-reg)*w.sigma.S+reg*mean(m.sigma)+S_update;
        m.sigma.S += S_update;
        m.sigma.nu += 1;
        m.cats[w_ind] = w;
        m.alpha[w_ind] += 1;        
    end
    m.phi = {m.alpha[i]/sum(m.alpha) for i=1:length(m.alpha)};
    prune = m.phi .> 0.0005;
    m.alpha = m.alpha[prune];
    m.cats = m.cats[prune];
    m.phi = {m.alpha[i]/sum(m.alpha) for i=1:length(m.alpha)};
end

