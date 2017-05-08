function BSFG_sampler(X,Y,Z,A,burn,sp,thin,eps,priors,maxk)

  r=size(Z,1);
  b=size(X,1);
  n,p=size(Y);

  Y_full=Y;
  for j in 1:p
    Y[:,j] = ( Y[:,j] - mean(Y[~isnan(Y[:,j]),j]) )./sqrt( var(Y[~isnan(Y[:,j]),j]) );
  end
  missloc = isnan(Y);
  missing = any(missloc);

  k = priors["k_init"]
  R = Dict{ASCIIString,Any}
  R["Y"]=Y;
  R["ps"]=rand(Beta(priors["as"],1/priors["bs"]),p);

  #genetic effects. This structure holds information about latent genetic
  #effects. U is latent genetic effects on factor traits. d is genetic
  #effects on residuals of the factor traits. Plus prior hyperparameters for
  #G effect precisions
  G = Dict{ASCIIString,Any}
  G["ps"] = rand(Gamma(prior["as"],1/prior["bs"]),p);
  G["U"] = repmat(NaN,(kmax,r));
  G["d"] = Array(Float64,(p,r));
  for j in 1:k
    rand!(Normal(0, sqrt(F["h2"][j]) ),G["U"][j,:]);
  end
  for j in 1:p
    G["d"][j,:] = rand(Normal(0, 1/sqrt(G["ps"][j]) ),r);
  end

  B_Sigma = zeros(b,b);
  B_mu = zeros(p,b);
  B = rand(Normal(),(p,b));

  F["k"]=priors["k_init"];
  F["psijh"] = repmat(NaN,(p,kmax));
  F["psijh"][:,1:k] = rand(Gamma(df/2,2/df),(p,k));    #individual loadings precisions
  F["delta"] = repmat([NaN],kmax);
  F["delta"][1] = rand(Gamma(priors["ad1"]+10,1/priors["bd1"]));
  rand!(Gamma(priors["ad2"],1/priors["bd2"]),F["delta"][2:k]);  #components of tauh
  F["tauh"] = cumprod(F["delta"]);        #extra shrinkage of each loading column
  F["Plam"] = F["psijh"] .* F["tauh"]';   #total precision of each loading
  F["Lambda"] = repmat(NaN,(p,kmax));
  rand!(Normal(),F["Lambda"][:,1:kmax]);
  @in1! F["Lambda"] ./ sqrt(F["Plam"]);   #factor loadings
  F["h2"] = repmat([NaN],kmax);
  rand!(F["h2"][1:k]);                   #factor heritability
  #F["num"]= 0;
  #F["no_f"]= zeros(sp);
  #F["nofout"] = prior["k"]*ones(nrun,1);
  F["scores"] = G["U"]*Z
  for j in 1:k
    F["scores"][j,:] += rand(Normal(0,1-F["h2"][j]),n); #initialize factor scores
  end

  #precalculate some matrices
  #invert the random effect covariance matrices
  Ainv = inv(A);
  ZAZ=Z'*A*Z;
  ZAZvec,tmp = svd(ZAZ);
  ZAZval = diag(tmp);

  #fixed effects + random effects 1
  #diagonalize mixed model equations for fast inversion:
  #inv(a*blkdiag(fixed_effects.cov,Ainv) + b*[X; Z_1][X; Z_1]') = Q*diag(1./(a.*s1+b.*s2))*Q'

  Design = vcat(X,Z);
  Dcov = Design*Design';
  svdout = svdfact( chol(full(blkdiag(sparse(B_Sigma),sparse(Ainv)))), chol(Dcov) );
  DA_Q = inv( (svdout.R0 * svdout.Q')' )';
  DA_S1 = diagm( svdout.D1'*svdout.D1 );
  DA_S2 = diagm( svdout.D2'*svdout.D2 );
  QtD = svd_Q' * Design;

  #G effect variances of factor traits
  #diagonalizing a*Z_1*Z_1' + b*Ainv for fast inversion
  #diagonalize mixed model equations for fast inversion:
  #inv(a*Z_1*Z_1' + b*Ainv) = Q*diag(1./(a.*s1+b.*s2))*Q'
  #similar to fixed effects + random effects 1 above, but no fixed effects.

  ZZt = Z*Z';
  svdout = svdfact( chol(ZZt), chol(Ainv) );
  ZA_Q = inv( (svdout.R0 * svdout.Q')' )';
  ZA_S1 = diagm( svdout.D1'*svdout.D1 );
  ZA_S2 = diagm( svdout.D2'*svdout.D2 );

  for i in 1:nrun
    #impute missing phenotypes
    if missing
      muY = transpose(B*X + G["d"]*Z + F["Lambda"]*F["Scores"]);
      for j in 1:p
        Y[missloc[:,j],j] = muY[missloc[:,j],j] + rand(Normal(0,1/R["ps"]));
      end
    end

    #sample Lambda
        FtU = F["scores"] * ZAZvec;
    UtY = ZAZvec' * (Y'-B*X)';
    sample_Lambda!(F,G["ps"],R["ps"])
    @into! Lam2 = F["Lambda"].^2

    #sample B and D
    resid = Y - F["Lambda"]*F["scores"];
    N = G["n"] + b;

    means = ( QtD*(Y' - F["Lambda"]*F["scores"])' ) .* R["ps"]';
    samp = Array(Float64,(N,p));
    raw = rand(Normal(),(N,p));
    for j in 1:p
      d = DA_S1*G["ps"][j] + DA_S2*R["ps"][j];
      mlam = means[:,j] ./ d;
      samp[:,j] = DA_Q*(mlam + raw[:,j] ./ sqrt(d));
    end
    B = samp[1:b,:]';
    G["d"] = samp[(b+1):(G["n"]+b),:]';

    #sample heritabilities of factors
    sample_h2!(F["h2"],F["scores"],ZAZvec,ZAZval,r,F["k"],priors["h2div"]);

    #sample genetic factors
    sample_U!(G["U"],Z,F["scores"],F["h2"],ZA_Q,ZA_S1,ZA_S2,F["k"],r);

    #sample factor scores
    @into! Ytil = (Y'-B*X-G["d"]*Z)
    sample_scores!(F["scores"],Ytil,G["U"],F["Lambda"],R["ps"],F["h2"],F["k"],n);

    #update factor precision
    rand!(Gamma( priors["df"]/2 + 0.5,
                2 ./ (priors["df"] + Lam2 .* F["tauh"]') ),
          F["psijh"]);

    #update noise precision
    add!(Ytil,-F["Lambda"]*F["scores"]);
    vnorm!(rss,Ytil,2,2);
    for j in 1:p
      R["ps"][j] = rand(Gamma( priors["as"] + 0.5*n,
                              1./(priors["bs"] + 0.5*rss[j]^2)));
    end

    #update genetic effect precision
    vnorm!(dss,G["d"],2,2);
    for j in 1:p
      G["ps"][j] = rand(Gamma(priors["as"] + 0.5*r,
                              1./(priors["bs"] + 0.5*dss[j]^2)));
    end

    #update delta
    sample_delta!(F["delta"],F["tau"],F["psijh"],Lam2,priors,F["k"])

    #update total precision
    @into! F["Plam"] = F["psijh"] .* F["tauh"]';

    #update number of factors

  end
end
