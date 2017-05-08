using Distributions
using PyPlot

# Mixture component
type GaussND
    d
    mu
    sigma
    kappa
    nu
end

# utility function because this is annoying to type every time.
function getsigma(G::GaussND)
    return G.sigma/(G.nu-G.d-1)
end


# Mixture
type ItterMix
    d::Int
    a
    stick
    alpha
    phi
    components
    mean_sigma
    ms_nu
end

# for pooled covariance
function getsigma(M::ItterMix)
    return M.mean_sigma/(M.ms_nu-M.d-1)
end

# another utility function:
function component_means(M::ItterMix,threshold = 0.01)
    j = 1
    for i=1:length(M.components)
        if M.phi[i]>threshold
            print(j,' ', M.components[i].mu)
            print('\n')
            j+=1
        end
    end
end

# Component update
function update(G::GaussND,x,weight = 1)
    G.sigma += weight*((x-G.mu)*transpose(x-G.mu))*G.kappa/(G.kappa+1);
    G.mu = weight*G.mu*(G.kappa/(G.kappa+1)) + x*(1/(G.kappa+1));
    G.kappa += weight*1;
    G.nu += weight*1;
end


# Mixture update with competition
function update(M::ItterMix,x,comp::Int=1)
    # determine if new or old category
    # p(new) decreases as stick-length decreases
    isnew = rand(Bernoulli(M.stick));
    
    # generate posterior predictive densities
    # currently terribly clunky
    
    if !bool(isnew)
        post_pred = {MvTDist(float(G.nu-M.d+1),G.mu,G.sigma*((G.kappa+1)/(G.kappa*(G.nu-M.d-1)))) for G in M.components};
        # Calculate and normalize cluster responsibilities
        resp = [M.phi[i]*pdf(post_pred[i],x) for i=1:length(post_pred)];
        resp = float(resp/sum(resp));
        if comp == 1
            winner = indmax(resp);
        else
            winner = indmax(rand(Multinomial(1,resp)));
        end
        #mu_temp = M.components[winner].mu
        kappa_temp = M.components[winner].kappa
        update(M.components[winner],x);
        #mean_sigma += ((x-mu_temp)*transpose(x-mu_temp))*kappa_temp/(kappa_temp+1);
        #ms_nu += 1
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
    prune = M.phi .> 0.0005;
    M.alpha = M.alpha[prune];
    M.components = M.components[prune];
    M.phi = {M.alpha[i]/sum(M.alpha) for i=1:length(M.alpha)};
    mean_sigma = mean({G.sigma/(G.nu-M.d-1) for G in M.components});
end

function sample(G::GaussND,s_type ="posterior")
    if s_type == "posterior"
        sigma = rand(InverseWishart(G.nu,G.sigma));
        mu = rand(MvNormal(G.mu,(G.sigma/G.kappa)));
        return rand(MvNormal(mu,sigma))
    else
        return rand(MvNormal(G.mu,getsigma(G)))
    end
end

function sample(M::ItterMix,n,s_type ="posterior")
    out = Array(Float64,M.d+1,n)
    for i=1:n
        cat_i = indmax(rand(Multinomial(1,float(M.phi))));
        out[:,i] = vcat(sample(M.components[cat_i],s_type),cat_i)
    end
    return out
end
    

#-----------------------------------------------------------------------------------------------------
# regularized version:

#Component update with regularized Sigma
function update(G::GaussND,x,Sigma,nu)
    conf = [G.nu; nu];
    #conf = [7;3];
    conf = conf/sum(conf);
    G.sigma += (((x-G.mu)*transpose(x-G.mu))*conf[1]+Sigma*conf[2])*G.kappa/(G.kappa+1);
    G.mu = G.mu*(G.kappa/(G.kappa+1)) + x*(1/(G.kappa+1));
    G.kappa += 1;
    G.nu += 1;
end


# Mixture update with regularized Sigma
function update(M::ItterMix,x,comp::Int,reg::Int)
    # determine if new or old category
    # p(new) decreases as stick-length decreases
    isnew = rand(Bernoulli(M.stick));
    
    # generate posterior predictive densities
    # currently terribly clunky
    
    if !bool(isnew)
        post_pred = {MvTDist(float(G.nu-M.d+1),G.mu,G.sigma*((G.kappa+1)/(G.kappa*(G.nu-M.d-1)))) for G in M.components};
        # Calculate and normalize cluster responsibilities
        resp = [M.phi[i]*pdf(post_pred[i],x) for i=1:length(post_pred)];
        resp = float(resp/sum(resp));
        if comp == 1
            winner = indmax(resp);
        else
            winner = indmax(rand(Multinomial(1,resp)));
        end
        nu_temp = M.ms_nu/length(M.components)
        mu_temp = M.components[winner].mu
        kappa_temp = M.components[winner].kappa
        # Not working as it's supposed to
        update(M.components[winner],x,M.mean_sigma/(M.ms_nu-M.d-1),nu_temp);
        M.mean_sigma += ((x-mu_temp)*transpose(x-mu_temp))*kappa_temp/(kappa_temp+1);
        M.ms_nu += 1
        M.alpha[winner] += 1;
    else
        w_new = rand(Beta(1,M.a))*M.stick;
        M.stick = M.stick - w_new;
        if M.components == {}
            sigma_new = M.mean_sigma*(M.alpha[1]);
            M.components = cat(1,M.components,{GaussND(M.d,x,sigma_new,M.alpha[1],M.alpha[1]+M.d+M.ms_nu)});
        else
            # Calculating phi for new category:
            # un-normalize current vector phi (divide by 1-current stick length)
            phi_un = M.phi/(1-M.stick);
            phi_un = cat(1,phi_un,{w_new});
            alpha_new = max((w_new/sum(phi_un))*sum(M.alpha),1);
            M.alpha = cat(1,M.alpha,{alpha_new});
            sigma_new = M.mean_sigma*alpha_new;
            M.components = cat(1,M.components,{GaussND(M.d,x,sigma_new,alpha_new+M.d,alpha_new+M.d+M.ms_nu)});
        end
    end
    M.phi = {M.alpha[i]/sum(M.alpha) for i=1:length(M.alpha)};
    prune = M.phi .> 0.0005;
    M.alpha = M.alpha[prune];
    M.components = M.components[prune];
    M.phi = {M.alpha[i]/sum(M.alpha) for i=1:length(M.alpha)};
end


function print_mix(M::ItterMix,print_mu=true,print_sigma=true)
    for i=1:length(M.components)
        if print_mu & print_sigma
            if M.phi[i]>0.05
                print(M.phi[i],'\n','\n',M.components[i].mu,'\n','\n',getsigma(M.components[i]),'\n','\n')
            end
        elseif print_mu
            if M.phi[i] > 0.5
                print(test1.phi[i],'\n','\n',M.components[i].mu,'\n','\n')
            end
        else
            print(M.phi[i])
        end
    end
end




# Mixture update with regularized Sigma and fixed relationship between pooled and local sigma
function update(M::ItterMix,x,comp::Int,w::Float64)
    # determine if new or old category
    # p(new) decreases as stick-length decreases
    isnew = rand(Bernoulli(M.stick));
    
    # generate posterior predictive densities
    # currently terribly clunky
    
    if !bool(isnew)
        post_pred = {MvTDist(float(G.nu-M.d+1),G.mu,G.sigma*((G.kappa+1)/(G.kappa*(G.nu-M.d-1)))) for G in M.components};
        # Calculate and normalize cluster responsibilities
        resp = [M.phi[i]*pdf(post_pred[i],x) for i=1:length(post_pred)];
        resp = float(resp/sum(resp));
        if comp == 1
            winner = indmax(resp);
        else
            winner = indmax(rand(Multinomial(1,resp)));
        end
        #nu_temp = M.ms_nu/length(M.components)
        mu_temp = M.components[winner].mu
        kappa_temp = M.components[winner].kappa
        # Not working as it's supposed to
        update(M.components[winner],x,M.mean_sigma/(M.ms_nu-M.d-1),w);
        M.mean_sigma += ((x-mu_temp)*transpose(x-mu_temp))*kappa_temp/(kappa_temp+1);
        M.ms_nu += 1
        M.alpha[winner] += 1;
    else
        w_new = rand(Beta(1,M.a))*M.stick;
        M.stick = M.stick - w_new;
        if M.components == {}
            sigma_new = M.mean_sigma*(M.alpha[1]);
            M.components = cat(1,M.components,{GaussND(M.d,x,sigma_new,M.alpha[1],M.alpha[1]+M.d+M.ms_nu)});
        else
            # Calculating phi for new category:
            # un-normalize current vector phi (divide by 1-current stick length)
            phi_un = M.phi/(1-M.stick);
            phi_un = cat(1,phi_un,{w_new});
            alpha_new = max((w_new/sum(phi_un))*sum(M.alpha),1);
            M.alpha = cat(1,M.alpha,{alpha_new});
            sigma_new = M.mean_sigma*(alpha_new);
            M.components = cat(1,M.components,{GaussND(M.d,x,sigma_new,alpha_new+M.d,alpha_new+M.d+M.ms_nu)});
        end
    end
    M.phi = {M.alpha[i]/sum(M.alpha) for i=1:length(M.alpha)};
    prune = M.phi .> 0.0005;
    M.alpha = M.alpha[prune];
    M.components = M.components[prune];
    M.phi = {M.alpha[i]/sum(M.alpha) for i=1:length(M.alpha)};
end

# Modify update function
function update(G::GaussND,x,Sigma,w::Float64)
    conf = [w; 1-w];
    conf = conf/sum(conf);
    G.sigma += (((x-G.mu)*transpose(x-G.mu))*conf[1]+Sigma*conf[2])*G.kappa/(G.kappa+1);
    G.mu = G.mu*(G.kappa/(G.kappa+1)) + x*(1/(G.kappa+1));
    G.kappa += 1;
    G.nu += 1;
end


#-----------------------------------------------------------------------------------------------------
# classification of new data:
function categorize(M::ItterMix,data)
    labels = Array(Float64,size(data,2),1)
    for i=1:size(data,2)
        x = data[:,i];
        post_pred = {MvTDist(float(G.nu-M.d+1),G.mu,G.sigma*((G.kappa+1)/(G.kappa*(G.nu-M.d-1)))) for G in M.components};
        # Calculate and normalize cluster responsibilities
        resp = [M.phi[i]*pdf(post_pred[i],x) for i=1:length(post_pred)];
        resp = float(resp/sum(resp));
        labels[i] = indmax(resp);
    end
    return labels
end