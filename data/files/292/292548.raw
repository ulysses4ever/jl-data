@debug function BSFG_sampler(X,Y,A,Z,burn,thin,iter,eps,priors)

  #get dimensions
  r=size(Z,1);  #biological replicates
  b=size(X,1);  #
  n,p=size(Y);
  k = priors["k_init"];
  if isempty(priors["k_max"])
    priors["k_max"] = p;
  end
  kmax = priors["k_max"];

  data_norm!(Y,X,p,b);
  Yt = Y';

  #initialize gibbs chain
  saveiter = (burn+1):thin:iter;
  nsave = length(saveiter);
  niter = maximum(saveiter);

  #create containers and starting points for all posteriors
  F,G,B,Rps,P = initialize(n,p,r,b,k,nsave,priors);

  #precalculate covariance quantities for fast inversion
  ZAZvec,ZAZval,DA_Q,DA_S1,DA_S2,QtD,ZA_Q,ZA_S1,ZA_S2 = precalc(X,Z,A,priors["B_Sinv"]);

  #find missing data points
  missloc = isnan(Y);
  missing = any(missloc);
  missloc = find(missloc);
  misssub = ind2sub((n,p),missloc);

  #preallocate some containers
  shells = preallocate(n,p,r,priors["h2div"],b,kmax);
  krop!(F,G,shells,k);
  Lam2 = Array(Float64,(p,kmax));
  Lam2_sub = sub(Lam2,:,1:k);
  resid = shells["pbyn"];

  for i in 1:niter

    #impute missing phenotypes
    if missing
      sample_missing!(Yt,shells["Yt"],B,X,k,missloc,misssub);
    end

    #sample Lambda
    sample_Lambda!(F,G["ps"],Rps,X,B,Yt,ZAZvec,ZAZval,k,p,shells);
    copy!(Lam2_sub,F["Lambda_sub"]);
    pow!(Lam2,2);

    #sample B and D
    sample_BD!(B,G,F,Rps,Yt,QtD,DA_Q,DA_S1,DA_S2,n,b,p,shells);

    #sample heritabilities of factors
    sample_h2!(F,ZAZvec,ZAZval,r,k,n,priors["h2div"],shells);

    #sample genetic factors
    sample_U!(G["U"],Z,F,ZA_Q,ZA_S1,ZA_S2,k,r,shells);

    @into! resid = B*X;
    BLAS.gemm!('N','N',1.0,G["d"],Z,1.0,resid);
    add!(negate!(resid),Yt);
    #sample factor scores
    sample_scores!(F,G,Z,resid,Rps,k,n,shells);

    BLAS.gemm!('N','N',-1.0,F["Lambda_sub"],F["scores_sub"],1.0,resid);
    #update precisions
    sample_precisions!(F,G,Rps,Lam2_sub,resid,k,p,n,r,priors,shells);

    #update factor-specific shinkage
    sample_delta!(F,Lam2_sub,priors,k,p,shells);

    #update total precision
    @into! F["Plam"] = F["psijh"] .* Base.transpose!(shells["kt"],F["tauh"]);

    #update number of factors
    update_k!(F,G,Z,priors,i,p,k,r,eps,1.0,shells);
    if k != F["k"]
      k = F["k"];
      krop!(F,G,shells,k);
    end

    #store samples
    nsamp = findin(saveiter,i);
    if ~isempty(nsamp)
      store_posterior!(P,F,G,Rps,B,nsamp);
    end

  end
  return P,priors
end
