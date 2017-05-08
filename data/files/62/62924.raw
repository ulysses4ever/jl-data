# Mixture update with regularized Sigma
function update(M::ItterMix,x,comp::Int,reg::Int)
    # New or old category?
    isnew = rand(Bernoulli(M.stick));
    # if X belongs to an existing category:
    if !bool(isnew)
        n_cats = length(M.components)
        resp = zeros(Float64,n_cats)
        i = 1
        for G in M.components
            post_pred = MvTDist(G.nu-M.d+1.0, G.mu, G.sigma*((G.kappa+1)/(G.kappa*(G.nu-M.d-1))))
            resp[i] = pdf(post_pred,x)
            i += 1
        end
        # Normalize cluster responsibilities
        resp = float(resp/sum(resp));
        if comp == 1
            winner = indmax(resp);
        else
            winner = indmax(rand(Multinomial(1,resp)));
        end
        nu_temp = M.ms_nu/length(M.components)
        mu_temp = M.components[winner].mu
        kappa_temp = M.components[winner].kappa
        # Update for pooled sigma:
        ms_update = ((x-mu_temp)*(x-mu_temp)')*kappa_temp/(kappa_temp+1);
        update(M.components[winner],x,ms_update,nu_temp);
        M.ms_nu += 1
        M.alpha[winner] += 1;
    # If X belongs to a new category:
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
