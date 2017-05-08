function update_k!(F,G,Z,priors,i,p,k,r,n)
  lind = zeros(k);
  cull = fill(false,k);
  oldk = k;

  prob = 1/exp(priors[:b0] + priors[:b1]*i);
  #lind = sum(abs(F[:Lambda_sub]) .< eps,1)./p;

  if (rand() < prob) & (i > priors[:kfreeze])

    Labs = abs(F[:Lambda_sub]);
    for j in 1:k
      for l in 1:p
        lind[j] += Labs[l,j] < priors[:eps];
      end
      lind[j] = lind[j] / p;
      cull[j] = lind[j] >= priors[:prop];
    end
    num = countnz(cull);

    if num == 0 & all(lind .< 0.995) & k < p # add column
      k=k+1;
      F[:psijh][:,k] = rand(Gamma(priors[:df]/2,2/priors[:df]),p);
      F[:delta][k] = rand(Gamma(priors[:ad2],1/priors[:bd2]));
      #cumprod!(F[:tauh],F[:delta],1);
      #@into! F["Plam"] = F[:psijh] .* Base.transpose!(shells["kt"],F[:tauh]);
      F[:tauh][k] = prod(F[:delta][1:k]);
      F[:Plam][:,k] = F[:psijh][:,k].*F[:tauh][k];
      for j in 1:p F[:Lambda][j,k] = rand(Normal(0,sqrt(1/F[:Plam][j,k]))); end
      F[:h2][k] = rand();
      for j in 1:r G[:U][k,j] = rand(Normal()); end
      for j in 1:n F[:scores][k,j] = rand(Normal(0,sqrt(1-F[:h2][k]))); end
      #NumericExtensions.add!(F[:scores][k,:],G[:U][k,:]*Z);
      BLAS.gemm!('N','N',1.0,G[:U][k,:],Z,1.0,view(F[:scores],k,:));
    elseif num > 0 # drop small columns
      keep = find(!cull);
      k = max(k-num,1);
      F[:Lambda][:,1:k] = F[:Lambda][:,keep];
      F[:Lambda][:,(k+1):end] = NaN;
      F[:psijh][:,1:k] = F[:psijh][:,keep];
      F[:psijh][:,(k+1):end] = NaN;
      F[:scores][1:k,:] = F[:scores][keep,:];
      F[:scores][(k+1):end,:] = NaN;
      for red in setdiff(1:(k-1),keep)
        F[:delta][red+1] *= F[:delta][red];
      end
      F[:delta][1:k] = F[:delta][keep];
      F[:delta][(k+1):end] = NaN;
      cumprod!(F[:tauh],F[:delta]);
      broadcast!(*,F[:Plam],F[:psijh],F[:tauh]');
      F[:h2][1:k] = F[:h2][keep];
      F[:h2][(k+1):end] = NaN;
      G[:U][1:k,:] = G[:U][keep,:];
      G[:U][(k+1):end,:] = NaN;
    end
    krop!(F,G,k);
  end

  return k
end

function sample_delta!(delta,tauh,psijh,Lam2,k,p,ad1,bd1,ad2,bd2)
  mat = psijh .* Lam2;
  ad = ad1 + 0.5*p*k;
  bd = bd1 + 0.5*(1/delta[1]) * dot(vec(sum(mat,1)),tauh);
  delta[1] = rand(Gamma(ad,1/bd));
  cumprod!(tauh,delta,1);

  for h in 2:k
    math = view(mat,:,h:k); tauhh = view(tauh,h:k);
    ad = ad2 + 0.5*p*(k-h+1);
    bd = bd2 + 0.5*(1/delta[h]) * dot(vec(sum(math,1)),tauhh);
    delta[h] = rand(Gamma(ad,1/bd));
    cumprod!(tauh,delta,1);
  end
end

function sample_scores!(scores,Lambda,h2,U,Z,resid,Rps,k,r,n)

  Lmsg = Lambda .* Rps;
  tau_e = 1./(1-h2);
  #S = chol(Lambda' * Lmsg + diagm(tau_e),:L);
  S = Lambda'*Lmsg;
  NumericExtensions.add_diag!(S,tau_e);
  cholfact!(S,:L);
  tril!(S);

  #Meta = S \ (S' \ (Lmsg' * resid + G[:U]*Z .*tau_e));
  tmp = U*Z;
  @in1! tmp .* tau_e;
  BLAS.gemm!('T','N',1.0,Lmsg,resid,1.0,tmp);
  foo = S \ tmp;
  Meta = S' \ foo;

  rand!(Normal(),scores);
  tmp = S' \ scores;
  @into! scores = tmp .+ Meta;

end

function sample_U!(U,h2,scores,Z,Q,S1,S2,k,r)
  tmp = Array(Float64,r);
  Ut = Array(Float64,r,k);
  tau_e = 1./(1.-h2);
  tau_u = 1./h2;
  #b = Q' * Z * (F[:scores] .* tau_e)';
  b = Z * (scores.*tau_e)';
  m = Q' * b;
  for j in 1:k
    if tau_e[j] == 1
      Ut[:,j] = 0;
    elseif tau_e[j] == Inf
      Ut[:,j] = scores[j,:];
    else
      #d = S2*tau_u[j] + S1*tau_e[j];
      #@into! d = S1.*tau_e[j];
      #@into! tmp = S2*tau_u[j]
      #add!(d,tmp);

      #U[j,:] = ( Q * (mlam + (rand(Normal(),r) ./ sqrt(d))) )';
      for l in 1:r
        @inbounds d = S2[l]*tau_u[j] + S1[l]*tau_e[j];
        tmp[l] = (m[l,j]/d) + randn()/sqrt(d);
      end
      Ut[:,j] = Q*tmp;
    end
  end
  transpose!(U,Ut)
end

function sample_h2!(h2,scores,Ur,eta,r,k,n,s)
  log_ps = zeros((s,k));
  std_scores_b = Array(Float64,(n,k));
  psj = Array(Float64,s);

  @into! std_scores_b = Ur'*scores';
  for i in 1:s
    h2i = (i-1)/s;
    #std_scores = 1/sqrt(h2) * ( std_scores_b ./ sqrt(eta + (1-h2)/h2 )' );
    #det = sum(log((eta+(1-h2)/h2)*h2)/2);
    for l in 1:k
      for j in 1:n
        if i > 1
          @inbounds  std_score = (1/sqrt(h2i)) * std_scores_b[j,l] / sqrt(eta[j] + (1-h2i)/h2i);
        else
          std_score = scores[l,j];
        end
        log_ps[i,l] -= (std_score^2)/2;
      end
    end

    det = 0.0 :: Float64;
    if i > 1
      for j = 1:n
        det += log(eta[j]*h2i + (1-h2i))/2;
      end
    end
    log_ps[i,:] -= det;

    if i == 1
      log_ps[i,:] += log(s-1);
    end
  end
  for j in 1:k
    #norm_factor = maximum(log_ps[j,:]) + logsumexp(log_ps[j,:] - maximum(log_ps[j,:]))
    logpsj = view(log_ps,:,j);
    norm_factor = NumericExtensions.logsumexp(logpsj) :: Float64;
    #tmps = exp(logpsj .- norm_factor);
    @into! psj = logpsj .- norm_factor;
    NumericExtensions.exp!(psj);
    h2[j] = (findfirst( rand(Multinomial(1,psj)) )-1) / s;
  end
end

function sample_Lambda!(Lambda,scores,Plam,Gps,Rps,X,B,Yt,ZAZvec,ZAZval,k,p,n)

  function Lambda_core!(Lambda,Plam,FtU,UtY,ZAZval,Gps,Rps,k,p,n)
    FUDj = Array(Float64,(k,n));
    Llam = Array(Float64,(k,k));
      for j in 1:p
      #FUDj = ( FtU ./ (ZAZval .+ Gps[j]./Rps[j]) ) .* Gps[j];
      #ZAZvalj = ZAZval + (Gps[j]/Rps[j]);
      #FUDj = FtU ./ ZAZvalj;
      #FUDj .* Gps[j];
      for m in 1:n
        for l in 1:k
          FUDj[l,m] = Gps[j] * (FtU[l,m] / (ZAZval[m] + Gps[j]/Rps[j]));
        end
      end

      #Llam = FUDj*FtU' + diagm(vec(Plam[j,:]));
      @into! Llam = FUDj*FtU';
      for l in 1:k Llam[l,l] += Plam[j,l]; end
      #add_diag!(Llam,Plam[j,:]);
      cholfact!(Llam,:L);
      tril!(Llam);

      means = FUDj*UtY[:,j];
      vlam = Llam\means;
      mlam = Llam'\vlam;
      ylam = Llam'\rand(Normal(),k);
      #add!(ylam,mlam);
      Lambda[j,:] = ylam+mlam;
    end
  end
  resid = Yt - B*X;
  #add!(negate!(resid),Yt);
  UtY = ZAZvec' * resid';
  FtU = scores * ZAZvec;
#  rand!(Normal(),Zlams);
  Lambda_core!(Lambda,Plam,FtU,UtY,ZAZval,Gps,Rps,k,p,n);

end


function sample_missing!(Yt,Lambda,scores,B,X,k,missloc,misssub);
     #muYt = Ytshape;
     muYt = B*X;
     BLAS.gemm!('N','N',1.0,G[:d],Z,1.0,muYt);
     BLAS.gemm!('N','N',1.0,Lambda,scores,1.0,muYt);
     for l in 1:length(missloc)
       j = missloc[l];
       col = misssub[1][l];
       Yt[j] = rand(Normal(muYt[j],1/sqrt(Rps[col])));
     end
end

function sample_BD!(B,Gd,Gps,Lambda,scores,Rps,Yt,QtD,DA_Q,DA_S1,DA_S2,n,b,p)
  N = n + b;
  mi = Array(Float64,N);
  up = Array(Float64,N);
  resid = Yt - Lambda*scores;
  #resid = F[:Lambda_sub]*F["scores_sub"];
  #add!(negate!(resid),Yt)
  means = QtD*resid';
  @in1! means .* transpose(Rps);
  for i in 1:p
    for j in 1:N
      d = DA_S1[j]*Gps[i] + DA_S2[j]*Rps[i];
      mi[j] = means[j,i] ./ d;
      #mi[j] = rand( Normal(mi[j],1./sqrt(d)) );
      mi[j] = mi[j] + randn()/sqrt(d);
    end
    @into! up = DA_Q*mi;
    B[i,:] = up[1:b];
    Gd[i,:] = up[(b+1):N];
  end
end


function sample_precisions!(psijh,Gps,Rps,tauh,d,Lam2,resid,k,p,n,r,df,as,bs)

  a = df/2 + 0.5;
  for i in 1:p
    for j in 1:k
      b = 2 ./ (df + Lam2[i,j] .* tauh[j])
      psijh[i,j] = rand(Gamma(a,b));
    end
  end

  #update noise precision
  a = as + 0.5*n;
  for j in 1:p
    ss = sumabs2(resid[j,:]);
    b = 1./(bs + 0.5*ss);
    Rps[j] = rand(Gamma(a,b));
  end

  #update genetic effect precision
  #vnorm!(ss,G["d"],2,2);
  #pow!(ss,2);
  a = as + 0.5*r;
  for j in 1:p
    ss = sumabs2(d[j,:]);
    b = 1./(bs + 0.5*ss)
    Gps[j] = rand(Gamma(a,b));
  end
end
