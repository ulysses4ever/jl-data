function BSFG_sampler(X,Y,Z,A,burn,sp,thin,b0,b1,h2_div,eps,priors)

  r=size(Z,1);
  b=size(X,1);

  n,p=size(Y);
  Y_full=Y;
  for j in 1:p
    Y[:,j] = ( Y[:,j] - mean(Y[~isnan(Y[:,j]),j]) )./sqrt( var(Y[~isnan(Y[:,j]),j]) );
  end

  resid = Dict{ASCIIString,Any}
  resid["as"] = priors["as"];
  resid["bs"]=priors["bs"];
  resid["Y"]=Y;
  resid["p"]=p;
  resid["ps"]=rand(Beta(resid["as"],1/resid["bs"]),p);

  factors["r"]=n;
  factors["n"]=n;
  factors["p"]=p;
  factors["k"]=priors["k_init"];
  factors["psijh"] = rand(Gamma(df/2,2/df),(p,k));    #individual loadings precisions
  factors["delta"] = vcat( rand(Gamma(priors["ad1"]+10,1/priors["bd1"])),
                          rand(Gamma(priors["ad2"],1/priors["bd2"]),(priors["k_init"]-1,1)) );  #components of tauh
  factors["tauh"] = cumprod(factors.delta);                       #extra shrinkage of each loading column
  factors["Plam"] = bsxfun(@times,factors.psijh,factors.tauh');   #total precision of each loading
  factors["Lambda"] = zeros(p,k) + randn(p,k).*reshape(sqrt(1./factors.Plam),p,k);   #factor loadings
  factors["h2"] = rand(k,1);                                             #factor heritability
  factors["h2_div"] = h2_div;                                #discretizations of heritability
  factors["num"]=0;
  factors.["no_f"]=zeros(sp);
  factors["nofout"] = prior["k"]*ones(nrun,1);

  #genetic effects. This structure holds information about latent genetic
  #effects. U is latent genetic effects on factor traits. d is genetic
  #effects on residuals of the factor traits. Plus prior hyperparameters for
  #genetic effect precisions
  genetic = Dict{ASCIIString,Any}
  genetic["n"]=r;
  genetic["ps"] = rand(Gamma(prior["as"],1/prior["bs"]),p);
  genetic["U"] = Array(Float64,(r,k));
  genetic["d"] = Array(Float64,(r,p));
  for j in 1:k
    genetic["U"][:,j] = rand(Normal(),r) .* sqrt(factors["h2"][j]);
  end
  for j in 1:p
    genetic["d"][:,j] = rand(Normal(),r) ./ sqrt(genetic["ps"][j]);
  end

  B_Sigma = zeros(b,b);
  B_mu = zeros(b,p);
  B = rand(Normal(),(b,p));

  #precalculate some matrices
  #invert the random effect covariance matrices
  Ainv = inv(A);
  ZAZ=Z'*A*Z;
  ZAZvec,tmp = svd(ZAZ);
  ZAZval = diag(tmp);

  Design = vcat(X,Z);
  Dcov = Design*Design';
  svdout = svdfact( chol(full(blkdiag(sparse(B_Sigma),sparse(Ainv)))), chol(Dcov) );
  svd_Q = inv( (svdout.R0 * svdout.Q')' )';
  svd_S1 = diagm( svdout.D1'*svdout.D1 );
  svd_S1 = diagm( svdout.D2'*svdout.D2 );
  Qt_Design = svd_Q' * Design;


end

function svdfact_alt(A)
  guh = svdfact(A)
  return guh.U * diagm(sqrt(guh.S))
end