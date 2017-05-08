function data_norm!(Y,X)
  for j in 1:p
    Y[:,j] = ( Y[:,j] - mean(Y[~isnan(Y[:,j]),j]) )./sqrt( var(Y[~isnan(Y[:,j]),j]) );
  end
  @in1! X .- mean(X,2)
  @in1! X ./ std(X,2);
end

function preallocate(n,p,r,s,kmax)
  shells = Dict{ASCIIString,Array};
  shells["Y"] = Array(Float64,(n,p));
  shells["Yt"] = Array(Float64,(p,n));
  shells["pbyk"] = Array(Float64,(p,kmax));
  shells["kbyp"] = Array(Float64,(kmax,p));
  shells["nbyp"] = Array(Float64,(n,p));
  shells["kbyn"] = Array(Float64,(kmax,n));
  shells["kbyn2"] = Array(Float64,(kmax,n));
  shells["bnbyp"] = Array(Float64,(b+n,p));
  shells["rbyk"] = Array(Float64,(r,kmax));
  shells["kbyk"] = Array(Float64,(kmax,kmax));
  shells["r"] = Array(Float64,r);
  shells["r2"] = Array(Float64,r);
  shells["p"] = Array(Float64,p);
  shells["k"] = Array(Float64,k);
  shells["k2"] = Array(Float64,k);
  shells["s"] = Array(Float64,s);

  return shells
end

function initialize(n,p,r,b,k,priors)

  Rps = rand(Beta(priors["as"],1/priors["bs"]),p);
  kmax = priors["kmax"];
  #genetic effects. This structure holds information about latent genetic
  #effects. U is latent genetic effects on factor traits. d is genetic
  #effects on residuals of the factor traits. Plus prior hyperparameters for
  #G effect precisions
  G = Dict{ASCIIString,Any}
  G["ps"] = rand(Gamma(prior["as"],1/prior["bs"]),p);
  G["U"] = fill(NaN,(kmax,r));
  G["d"] = Array(Float64,(p,r));
  for j in 1:k
    rand!(Normal(0, sqrt(F["h2"][j]) ),G["U"][j,:]);
  end
  for j in 1:p
    G["d"][j,:] = rand(Normal(0, 1/sqrt(G["ps"][j]) ),r);
  end

  B = rand(Normal(),(p,b));

  F["k"]=priors["k_init"];
  F["psijh"] = fill(NaN,(p,kmax));
  F["psijh"][:,1:k] = rand(Gamma(df/2,2/df),(p,k));    #individual loadings precisions
  F["delta"] = fill(NaN,kmax);
  F["delta"][1] = rand(Gamma(priors["ad1"]+10,1/priors["bd1"]));
  rand!(Gamma(priors["ad2"],1/priors["bd2"]),F["delta"][2:k]);  #components of tauh
  F["tauh"] = cumprod(F["delta"]);        #extra shrinkage of each loading column
  F["Plam"] = F["psijh"] .* F["tauh"]';   #total precision of each loading
  F["Lambda"] = fill(NaN,(p,kmax));
  rand!(Normal(),F["Lambda"][:,1:kmax]);
  @in1! F["Lambda"] ./ sqrt(F["Plam"]);   #factor loadings
  F["h2"] = fill(NaN,kmax);
  rand!(F["h2"][1:k]);                   #factor heritability
  F["scores"] = G["U"]*Z
  for j in 1:k
    F["scores"][j,:] += rand(Normal(0,1-F["h2"][j]),n); #initialize factor scores
  end

  #Initialize posteior samples
  P = Dict{ASCIIString,Any};
  P["Lambda"] = Array(Float64,(p,kmax,nsave));
  P["Gps"] = Array(Float64,(p,nsave));
  P["Rps"] = Array(Float64,(p,nsave));
  P["B"] = Array(Float64,(p,b,nsave));
  P["U"] = Array(Float64,(kmax,r,nsave));
  P["delta"] = Array(Float64,(kmax,nsave));
  P["h2"] = Array(Float64,(kmax,nsave));

  return F,G,B,Rps,P

end

function precalc(X,Z,A,B_Sinv)
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
  svdout = svdfact( chol(full(blkdiag(sparse(B_Sinv),sparse(Ainv)))), chol(Dcov) );
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

  return ZAZvec,ZAZval,DA_Q,DA_S1,DA_S2,QtD,ZA_Q,ZA_S1,ZA_S2
end

function krop!(F,G,shells,k)
  G["U_sub"] = sub(G["U"],1:k,r);

  F["psijh_sub"] = sub(F["psijh"],:,1:k);
  F["delta_sub"] = sub(F["delta"],1:k);
  F["tauh_sub"] = sub(F["tauh"],1:k);
  F["Plam_sub"] = sub(F["Plam"],:,1:k);
  F["Lambda_sub"] = sub(F["Lambda"],:,1:k);
  F["h2_sub"] = sub(F["h2"],1:k);
  F["scores_sub"] = sub(F["scores"],1:k,:);

  shells["pbyk_sub"] = sub(shells["pbyk"],:,1:k);
  shells["kbyp_sub"] = sub(shells["kbyp"],1:k,:);
  shells["kbyn_sub"] = sub(shells["kbyn"],1:k,:);
  shells["kbyn2_sub"] = sub(shells["kbyn2"],1:k,:);
  shells["rbyk_sub"] = sub(shells["rbyk"],:,1:k);
  shells["rbyk2_sub"] = sub(shells["rbyk2"],:,1:k);
  shells["kbyk_sub"] = sub(shells["kbyk"],1:k,1:k);
  shells["k"] = sub(shells["k"],1:k);
  shells["k2"] = sub(shells["k2"],1:k);
end
