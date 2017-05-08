function data_norm!(Y,X,p,b)
  for j in 1:p
    Y[:,j] = ( Y[:,j] - mean(Y[~isnan(Y[:,j]),j]) )./sqrt( var(Y[~isnan(Y[:,j]),j]) );
  end
  for j in 1:b
    if std(X[j,:])==0
      continue
    end
    X[j,:] -= mean(X[j,:]);
    X[j,:] /= std(X[j,:]);
  end
end

function initialize(n,p,r,b,k,nsave,priors)
  Rps = rand(Gamma(priors[:as],1/priors[:bs]),p);
  kmax = priors[:k_max];
  #genetic effects. This structure holds information about latent genetic
  #effects. U is latent genetic effects on factor traits. d is genetic
  #effects on residuals of the factor traits. Plus prior hyperparameters for
  #G effect precisions
  G = Dict{Symbol,Union{Array{Float64,1},Array{Float64,2},
                        ArrayViews.StridedView{Float64,2,1,Array{Float64,2}}}}();
  G[:ps] = rand(Gamma(priors[:as],1/priors[:bs]),p);
  G[:U] = fill(NaN,(kmax,r));
  G[:d] = Array(Float64,(p,r));
  for j in 1:p
    G[:d][j,:] = rand(Normal(0, 1/sqrt(G[:ps][j]) ),r);
  end

  B = rand(Normal(),(p,b));

  F = Dict{Symbol,Union{Array{Float64,1},Array{Float64,2},
                        ArrayViews.ContiguousView{Float64,2,Array{Float64,2}},
                        ArrayViews.ContiguousView{Float64,1,Array{Float64,1}},
                        ArrayViews.StridedView{Float64,2,1,Array{Float64,2}}}}();
  F[:psijh] = fill(NaN,(p,kmax));
  F[:psijh][:,1:k] = rand(Gamma(priors[:df]/2,2/priors[:df]),(p,k));    #individual loadings precisions
  F[:delta] = fill(NaN,kmax);
  F[:delta][1] = rand(Gamma(priors[:ad1]+10,1/priors[:bd1]));
  rand!(Gamma(priors[:ad2],1/priors[:bd2]),sub(F[:delta],2:k));  #components of tauh
  F[:tauh] = cumprod(F[:delta]);        #extra shrinkage of each loading column
  F[:Plam] = F[:psijh] .* F[:tauh]';   #total precision of each loading
  F[:Lambda] = fill(NaN,(p,kmax));
  rand!(Normal(),sub(F[:Lambda],:,1:kmax));
  @in1! F[:Lambda] ./ sqrt(F[:Plam]);   #factor loadings
  F[:h2] = fill(NaN,kmax);
  F[:h2][1:k] = rand(k);                   #factor heritability
  for j in 1:k
    rand!(Normal(0, sqrt(F[:h2][j]) ),sub(G[:U],j,:));
  end
  F[:scores] = G[:U]*Z;
  for j in 1:k
    F[:scores][j,:] += rand(Normal(0,1-F[:h2][j]),(1,n)); #initialize factor scores
  end

  #Initialize posteior samples
  P = Dict{Symbol,Union{Array{Float64,2},Array{Float64,3}}}();
  P[:Lambda] = Array(Float64,(p,kmax,nsave));
  P[:Gps] = Array(Float64,(p,nsave));
  P[:Rps] = Array(Float64,(p,nsave));
  P[:B] = Array(Float64,(p,b,nsave));
  P[:U] = Array(Float64,(kmax,r,nsave));
  P[:delta] = Array(Float64,(kmax,nsave));
  P[:h2] = Array(Float64,(kmax,nsave));

  return F,G,B,Rps,P

end

function precalc(X,Z,A,B_Sinv)
  #precalculate some matrices
  #invert the random effect covariance matrices
  Ainv = inv(A);
  ZAZ=Z'*A*Z;
  ZAZvec,ZAZval = svd(ZAZ);
  ZAZval = ZAZval';

  #fixed effects + random effects 1
  #diagonalize mixed model equations for fast inversion:
  #inv(a*blkdiag(fixed_effects.cov,Ainv) + b*[X; Z_1][X; Z_1]') = Q*diag(1./(a.*s1+b.*s2))*Q'
  Design = vcat(X,Z);
  Dcov = Design*Design';
  priorPs = full(blkdiag(sparse(B_Sinv),sparse(Ainv)));
  foo,foo,q,S1,S2 = mxcall(:gsvd,5,covfact(priorPs),covfact(Dcov));
  DA_Q = inv(q)';
  DA_S1 = diag( S1'S1 );
  DA_S2 = diag( S2'S2 );
  QtD = DA_Q' * Design;

  #G effect variances of factor traits
  #diagonalizing a*Z_1*Z_1' + b*Ainv for fast inversion
  #diagonalize mixed model equations for fast inversion:
  #inv(a*Z_1*Z_1' + b*Ainv) = Q*diag(1./(a.*s1+b.*s2))*Q'
  #similar to fixed effects + random effects 1 above, but no fixed effects.

  ZZt = Z*Z';
  foo,foo,q,S1,S2 = mxcall(:gsvd,5,covfact(ZZt),covfact(Ainv));
  ZA_Q = inv(q)';
  ZA_S1 = diag( S1'S1 );
  ZA_S2 = diag( S2'S2 );

  return ZAZvec,ZAZval,DA_Q,DA_S1,DA_S2,QtD,ZA_Q,ZA_S1,ZA_S2
end

function krop!(F,G,k)
  G[:U_sub] = view(G[:U],1:k,:);

  F[:psijh_sub] = view(F[:psijh],:,1:k);
  F[:delta_sub] = view(F[:delta],1:k);
  F[:tauh_sub] = view(F[:tauh],1:k);
  F[:Plam_sub] = view(F[:Plam],:,1:k);
  F[:Lambda_sub] = view(F[:Lambda],:,1:k);
  F[:h2_sub] = view(F[:h2],1:k);
  F[:scores_sub] = view(F[:scores],1:k,:);
end

function covfact(A,tol=1e-10)
  vec,val = svd(A);
  keep = abs(val).>tol;
  T = diagm(sqrt(val[keep]))*vec[:,keep]';
  return T
end
