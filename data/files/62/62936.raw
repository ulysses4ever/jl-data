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

# No competition mixture update
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

# Mixture update with competition
function update(M::ItterMix,x,comp::Int)
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

function sample(G::GaussND)
    sigma = rand(InverseWishart(G.sigma,G.nu));
    #return rand(NormalInverseWishart(G.mu,G.kappa,G.sigma,G.nu))
end

function sample(M::ItterMix,n)
    out = Array(Float64,M.d+1,n)
    for i=1:n
        cat_i = indmax(rand(Multinomial(1,float(M.phi))));
        out[:,i] = vcat(sample(M.components[cat_i]),cat_i)
    end
    return out
end
    