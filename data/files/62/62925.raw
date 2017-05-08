# Pulled from Diss.jl:

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


function prune(M::ItterMix,threshold)
    newmix = ItterMix(M.d,M.a,M.stick,{},{},{},M.mean_sigma,M.ms_nu);
    for i=1:length(M.phi)
        if M.phi[i]>threshold
            newmix.phi = cat(1,newmix.phi,{M.phi[i]});
            newmix.alpha = cat(1,newmix.alpha,{M.alpha[i]});
            newmix.components = cat(1,newmix.components,{M.components[i]});
        else
            newmix.stick += M.phi[i]
        end
    end
    newmix.phi /= sum(newmix.phi)
    return newmix
end



function train(M::ItterMix,data,nitter,permute=false)
    for i=1:nitter
        update(M,data[:,i],2);
    end
end



# Pulled from GAMod.jl

function train(M::GAMix,data,nitter,permute=false)
    for i=1:nitter
        update(M,data[:,i],2);
    end
end