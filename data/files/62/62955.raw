# -*- coding: utf-8 -*-
# <nbformat>3.0</nbformat>

# <codecell>

using Distributions;
using PyPlot;

# <codecell>

# Define both distributions
mu1 = [10.0; 0; 0];
sigma1 = [3.0 0 0; 0 6 0; 0 0 4];
mu2 = ones(3)*10;
sigma2 = [4.0 1 0; 1 2 1; 0 1 4];
clust1 = MvNormal(mu1,sigma1);
clust2 = MvNormal(mu2,sigma2);
# generate samples from both
sample1 = rand(clust1,1000);
sample2 = rand(clust2,1000);
sample_all = cat(2,sample1,sample2);
ord = randperm(2000);
col1 = permute!(sample_all[1,:],ord);
col2 = permute!(sample_all[2,:],ord);
col3 = permute!(sample_all[3,:],ord);
sample_rand = cat(1,col1,col2,col3);

# <codecell>

type GaussND
    d
    mu
    sigma
    kappa
    nu
end

# <codecell>

type ItterMix
    d::Int
    a
    stick
    alpha
    phi
    components
    mean_sigma
end

# <codecell>

function update(G::GaussND,x,weight = 1)
    G.sigma += weight*((x-G.mu)*transpose(x-G.mu))*G.kappa/(G.kappa+1);
    G.mu = weight*G.mu*(G.kappa/(G.kappa+1)) + x*(1/(G.kappa+1));
    G.kappa += weight*1;
    G.nu += weight*1;
end

function getsigma(G::GaussND)
    return G.sigma/(G.nu-G.d-1)
end

# <codecell>

function update(M::ItterMix,x)
    # determine if new or old category
    # p(new) decreases as stick-length decreases
    isnew = rand(Bernoulli(M.stick));
    
    # generate posterior predictive densities
    # currently terribly clunky
    
    if !bool(isnew)
        post_pred = {MvTDist(float(G.nu-M.d+1),G.mu,G.sigma*((G.kappa+1)/(G.kappa*(G.nu-M.d-1)))) for G in M.components};
        # Calculate and normalize cluster responsibilities
        resp = {M.phi[i]*pdf(post_pred[i],x) for i=1:length(post_pred)};
        resp = resp/sum(resp);
        for i = 1:length(M.components);
            update(M.components[i],x,resp[i]);
            M.alpha[i] += 1*resp[i];
        end
    else
        w_new = rand(Beta(1,M.a))*M.stick;
        M.stick = M.stick - w_new;
        if M.components == {}
            sigma_new = M.mean_sigma*(M.alpha[1]);
            M.components = cat(1,M.components,{GaussND(M.d,x,sigma_new,M.alpha[1],M.alpha[1]+M.d+1)});
        else
            # Calculating phi for new category:
            # un-normalize current vector phi (divide by 1-current stick length)
            phi_un = M.phi/(1-M.stick);
            phi_un = cat(1,phi_un,{w_new});
            alpha_new = (w_new/sum(phi_un))*sum(M.alpha);
            M.alpha = cat(1,M.alpha,{alpha_new});
            sigma_new = M.mean_sigma*(alpha_new);
            M.components = cat(1,M.components,{GaussND(M.d,x,sigma_new,alpha_new+M.d,alpha_new+M.d+1)});
        end
        
    end
    M.phi = {M.alpha[i]/sum(M.alpha) for i=1:length(M.alpha)};
    mean_sigma = mean({G.sigma/(G.nu-M.d-1) for G in M.components});
end

# <codecell>

# initialize a mixture with d = 3, a = 2, stick = 1, alpha = {10}, phi = {1}, components = {},
# mean_sigma = 3-dimensional identity matrix
mixTest = ItterMix(3,2,1,{10},{1},{},eye(3));

# <codecell>

update(mixTest,sample_rand[:,1])

# <codecell>

for i=2:100
    update(mixTest,sample_rand[:,i]);
end

# <codecell>

mixTest.phi

# <codecell>

for i=101:1000
    update(mixTest,sample_rand[:,i]);
end

# <codecell>

mixTest.phi

# <codecell>

for i=1001:2000
    update(mixTest,sample_rand[:,i]);
end

# <codecell>

mixTest.phi

# <codecell>

for i =1:length(mixTest.components)
    if mixTest.phi[i]>0.05
        print(mixTest.components[i].sigma/(mixTest.components[i].nu-3-1))
        print('\n')
        print(mixTest.components[i].mu)
        print('\n')
    end
end

# <codecell>

function update_mix_comp(M::ItterMix,x)
    # determine if new or old category
    # p(new) decreases as stick-length decreases
    isnew = rand(Bernoulli(M.stick));
    
    # generate posterior predictive densities
    # currently terribly clunky
    
    if !bool(isnew)
        post_pred = {MvTDist(float(G.nu-M.d+1),G.mu,G.sigma*((G.kappa+1)/(G.kappa*(G.nu-M.d-1)))) for G in M.components};
        # Calculate and normalize cluster responsibilities
        resp = {M.phi[i]*pdf(post_pred[i],x) for i=1:length(post_pred)};
        winner = indmax(resp)
        update(M.components[winner],x);
        M.alpha[winner] += 1;
    else
        w_new = rand(Beta(1,M.a))*M.stick;
        M.stick = M.stick - w_new;
        if M.components == {}
            sigma_new = M.mean_sigma*(M.alpha[1]);
            M.components = cat(1,M.components,{GaussND(M.d,x,sigma_new,M.alpha[1],M.alpha[1]+M.d+1)});
        else
            # Calculating phi for new category:
            # un-normalize current vector phi (divide by 1-current stick length)
            phi_un = M.phi/(1-M.stick);
            phi_un = cat(1,phi_un,{w_new});
            alpha_new = (w_new/sum(phi_un))*sum(M.alpha);
            M.alpha = cat(1,M.alpha,{alpha_new});
            sigma_new = M.mean_sigma*(alpha_new);
            M.components = cat(1,M.components,{GaussND(M.d,x,sigma_new,alpha_new+M.d,alpha_new+M.d+1)});
        end
        
    end
    M.phi = {M.alpha[i]/sum(M.alpha) for i=1:length(M.alpha)};
    mean_sigma = mean({G.sigma/(G.nu-M.d-1) for G in M.components});
end

# <codecell>

mixTest2 = ItterMix(3,2,1,{10},{1},{},eye(3)*5);

for i=1:100
    update_mix_comp(mixTest2,sample_rand[:,i]);
end

mixTest2.phi

# <codecell>

for i=101:200
    update_mix_comp(mixTest2,sample_rand[:,i]);
end

mixTest2.phi

# <codecell>

for i=201:500
    update_mix_comp(mixTest2,sample_rand[:,i]);
end

mixTest2.phi

# <codecell>

mixTest2.components[1]

# <codecell>

getsigma(mixTest2.components[1])

# <codecell>

for i=100:200
    update_mix_comp(mixTest2,sample_rand[:,i]);
end

mixTest2.phi

# <codecell>

getsigma(mixTest2.components[4])

# <codecell>

mixTest2.components[4].mu

