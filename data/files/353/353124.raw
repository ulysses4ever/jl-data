function BSFG_sampler(X,Y,A,Z,burn,thin,iter,eps,priors)

  #get dimensions
  r=size(Z,1);  #biological replicates
  b=size(X,1);  #
  n,p=size(Y);
  k = priors["k_init"];
  if isempty(priors["k_init"])
    priors["k_max"] = k;
  end
  kmax = priors["k_max"];

  data_norm!(Y,X);
  Yt = Y';

  #create containers and starting points for all posteriors
  F,G,B,Rps,P = initialize(n,p,r,b,k,priors);

  #precalculate covariance quantities for fast inversion
  ZAZvec,ZAZval,DA_Q,DA_S1,DA_S2,QtD,ZA_Q,ZA_S1,ZA_S2 =
    precalc(X,Z,A,priors["B_Sinv"])

  #find missing data points
  missloc = isnan(Y);
  misssub = ind2sub(missloc)
  missing = any(missloc);
  missloc = find(missloc);

  #initialize gibbs chain
  saveiter = (burnin+1):thin:iter;
  nsave = length(saveiter);
  niter = maximum(saveiter);

  #preallocate some containers
  shells = preallocate(n,p,r,priors["h2div"],kmax);
  krop!(F,G,shells,k);
  Lam2 = Array(Float64,(p,kmax));
  Lam2_sub = sub(Lab2,:,1:k);

  for i in 1:niter

    #impute missing phenotypes
    if missing
      sample_missing!(Yt,shells["Yt"],B,X,k,missloc,misssub);
    end

    #sample Lambda
    sample_Lambda!(F,G["ps"],Rps,X,B,Yt,ZAZvec,shells);
    @into! Lam2 = F["Lambda"].^2

    #sample B and D
    sample_BD!(B,G,F,Rps,Yt,QtD,DA_S1,DA_S2,n,b,p,shells);

    #sample heritabilities of factors
    sample_h2!(F,ZAZvec,ZAZval,r,k,priors["h2div"]);

    #sample genetic factors
    sample_U!(G["U"],Z,F,ZA_Q,ZA_S1,ZA_S2,k,r,shells);

    resid = shells["pbyn"];
    @into! resid = B*X;
    gemm!('N','N',1.0,G["d"],Z,1.0,resid);
    add!(negate!(resid),Yt);
    #sample factor scores
    sample_scores!(F,G,resid,Rps,k,n,shells);

    gemm!('N','N',-1.0,F["Lambda"],F["scores"],1.0,resid);
    #update precisions
    sample_precisions!(F,G,Lam2_sub,resid,k,p,n,r);

    #update factor-specific shinkage
    sample_delta!(F,Lam2_sub,priors,k);

    #update total precision
    @into! F["Plam"] = F["psijh"] .* F["tauh"]';

    #update number of factors
    update_k!(F,G,Z,priors,p,k,r,eps,1.0);
    if k != F["k"]
      k = F["k"];
      krop!(F,G,shells,k);
    end

    #store samples
    nsamp = findin(saveiter,i);
    if ~isempty(nsamp)
      save_posterior!(P,F,G,R,nsamp);
    end

  end
  return P,priors
end
