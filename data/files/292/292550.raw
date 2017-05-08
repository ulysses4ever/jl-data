function BSFG_sampler(X,Y,A,Z,burn,thin,iter,priors)

  #get dimensions
  r=size(Z,1);  #biological replicates
  b=size(X,1);  #
  n,p=size(Y);
  k = priors[:k_init];
  if priors[:k_max] <= 0
    priors[:k_max] = p;
  end
  kmax = priors[:k_max];

  data_norm!(Y,X,p,b);
  Yt = Y';

  #initialize gibbs chain
  saveiter = (burn+1):thin:iter;
  nsave = length(saveiter);
  niter = maximum(saveiter);

  #create containers and starting points for all posteriors
  F,G,B,Rps,P = initialize(n,p,r,b,k,nsave,priors);

  #precalculate covariance quantities for fast inversion
  ZAZvec,ZAZval,DA_Q,DA_S1,DA_S2,QtD,ZA_Q,ZA_S1,ZA_S2 = precalc(X,Z,A,priors[:B_Sinv]);

  #find missing data points
  missloc = isnan(Y);
  missing = any(missloc);
  missloc = find(missloc);
  misssub = ind2sub((n,p),missloc);

  #preallocate some containers
  krop!(F,G,k);
  Lam2 = Array(Float64,(p,kmax));
  resid = Array(Float64,(p,n));

  tic();
  for i in 1:niter
    #impute missing phenotypes
    if missing
      sample_missing!(Yt,F[:Lambda_sub],F[:scores_sub],B,X,k,missloc,misssub);
    end

    #sample Lambda
    sample_Lambda!(F[:Lambda_sub],F[:scores_sub],F[:Plam_sub],G[:ps],Rps,X,B,Yt,ZAZvec,ZAZval,k,p,n);
    Lam2_sub = view(Lam2,:,1:k);
    @into! Lam2_sub = F[:Lambda_sub].*F[:Lambda_sub];
    #sample B and D
    sample_BD!(B,G[:d],G[:ps],F[:Lambda_sub],F[:scores_sub],Rps,Yt,QtD,DA_Q,DA_S1,DA_S2,n,b,p);

    #sample heritabilities of factors
    sample_h2!(F[:h2],F[:scores_sub],ZAZvec,ZAZval,r,k,n,priors[:h2div]);

    #sample genetic factors
    sample_U!(G[:U_sub],F[:h2_sub],F[:scores_sub],Z,ZA_Q,ZA_S1,ZA_S2,k,r);

    @into! resid = B*X;
    BLAS.gemm!('N','N',1.0,G[:d],Z,1.0,resid);
    NumericExtensions.add!(NumericExtensions.negate!(resid),Yt);
    #sample factor scores
    sample_scores!(F[:scores_sub],F[:Lambda_sub],F[:h2_sub],G[:U_sub],Z,resid,Rps,k,r,n);
    BLAS.gemm!('N','N',-1.0,F[:Lambda_sub],F[:scores_sub],1.0,resid);

    #update precisions
    sample_precisions!(F[:psijh_sub],G[:ps],Rps,F[:tauh_sub],G[:d],
                       Lam2_sub,resid,k,p,n,r,priors[:df],priors[:as],priors[:bs]);

    #update factor-specific shinkage
    sample_delta!(F[:delta_sub],F[:tauh_sub],F[:psijh_sub],Lam2_sub,
                  k,p,priors[:ad1],priors[:bd1],priors[:ad2],priors[:bd2]);

    #update total precision
    broadcast!(*,F[:Plam_sub],F[:psijh_sub],F[:tauh_sub]');

    #update number of factors
    k = update_k!(F,G,Z,priors,i,p,k,r,n);

    #store samples
    nsamp = findin(saveiter,i);
    if ~isempty(nsamp)
      P[:Lambda][:,:,nsamp] = F[:Lambda];
      P[:U][:,:,nsamp] = G[:U];
      P[:delta][:,nsamp] = F[:delta];
      P[:h2][:,nsamp] = F[:h2];
      P[:Gps][:,nsamp] = G[:ps];
      P[:Rps][:,nsamp] = Rps;
      P[:B][:,:,nsamp] = B;
      print(i,"/",niter,"; ");
      print(k," factors\r")
    end

  end
  print("\n")
  toc();
  return P,priors
end
