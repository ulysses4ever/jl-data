function update_k!(F,G,Z,priors,i,p,k,r,eps,prop,shells)
  Labs = shells["pbyk"];
  lind = fill!(shells["k_sub"],0);
  cull = shells["k2_sub"];

  prob = 1/exp(priors["b0"] + priors["b1"]*i);
  #lind = sum(abs(F["Lambda_sub"]) .< eps,1)./p;
  abs!(Labs,F["Lambda"]);
  for j in 1:k
    for l in 1:p
      lind[j] += Labs[l,j] < eps;
    end
    cull[j] = lind[j] >= prop;
  end
  num = countnz(cull);

  if (rand() < prob) & (i >200)
    if i > 20 & num == 0 & all(lind<0.995) & k < p # add column
      k=k+1;
      rand!(Gamma(F["df"]/2,2/F["df"]),F["psijh"][:,k]);
      rand!(Gamma(priors["ad2"],1/priors["bd2"]),F["delta"][k])
      #cumprod!(F["tauh"],F["delta"],1);
      #@into! F["Plam"] = F["psijh"] .* Base.transpose!(shells["kt"],F["tauh"]);
      F["tauh"][k] = prod(F["delta"][1:k]);

      for j in 1:p
        F["Lambda"][j,k] = rand(Normal(0,sqrt(1/F["Plam"][j,k])));
      end
      F["h2"][k] = rand();
      rand!(Normal(),G["U"][k,:]);
      rand!(Normal(0,sqrt(1-F["h2"][k])),F["scores"][k,:]);
      add!(F["scores"][k,:],G["U"][k,:]*Z);
    elseif num > 0 # drop small columns
      k = max(k-num,1);
      F["k"] = k;
      F["Lambda"][:,1:k] = F["Lambda"][:,~cull];
      F["Lambda"][:,(k+1):end] = NaN;
      F["psijh"][:,1:k] = F["Lambda"][:,~cull];
      F["psijh"][:,(k+1):end] = NaN;
      F["scores"][1:k,:] = F["scores"][~cull,:];
      F["scores"][(k+1):end,:] = NaN;
      for red in setdiff(1:(k-1),~cull)
        F["delta"][red+1] *= F["delta"][red];
      end
      F["delta"][1:k] = F["delta"][~cull];
      F["delta"][(k+1):end] = NaN;
      cumprod!(F["tauh"],F["delta"]);
      @into! F["Plam"] = F["psijh"] .* F["tauh"]';
      F["h2"][1:k] = F["h2"][~cull];
      F["h2"][(k+1):end] = NaN;
      G["U"][1:k,:] = G["U"][~cull,:];
      G["U"][(k+1):end,:] = NaN;
    end
  end
end

function sample_delta!(F,Lam2,priors,k,p,shells)
  mat = shells["pbyk_sub"];
  @into! mat = F["psijh_sub"] .* Lam2;
  ad = priors["ad1"] + 0.5*p*k;
  bd = priors["bd1"] + 0.5*(1/F["delta_sub"][1]) * dot(vec(sum(mat,1)),F["tauh_sub"]);
  F["delta"][1] = rand(Gamma(ad,1/bd));
  cumprod!(F["tauh"],F["delta"],1);

  for h in 2:k
    math = sub(mat,:,h:k); tauhh = sub(F["tauh_sub"],h:k);
    ad = priors["ad2"] + 0.5*p*(k-h+1);
    bd = priors["bd2"] + 0.5*(1/F["delta_sub"][h]) * dot(vec(sum(math,1)),tauhh);
    F["delta"][h] = rand(Gamma(ad,1/bd));
    cumprod!(F["tauh"],F["delta"],1);
  end
end

function sample_scores!(F,G,Z,resid,Rps,k,n,shells)
  Lmsg = shells["pbyk_sub"]
  S = shells["kbyk_sub"];
  tmp = shells["kbyr_sub"];

  @into! Lmsg = F["Lambda_sub"] .* Rps;
  tau_e = 1./(1-F["h2_sub"]);
  #S = chol(Lambda' * Lmsg + diagm(tau_e),:U);
  @into! S = F["Lambda_sub"]'*Lmsg;
  add_diag!(S,tau_e);
  cholfact!( S );
  #Meta = S \ (S' \ (Lmsg' * resid + G["U"]*Z .*tau_e));
  @into! tmp = G["U_sub"]*Z;
  @in1! tmp .* tau_e;
  BLAS.gemm!('T','N',1.0,Lmsg,resid,1.0,tmp);
  Meta = S \ (S' \ tmp);

  rand!(Normal(),F["scores_sub"]);
  tmp = S' \ F["scores_sub"];
  #@add!(F["scores"], Meta);
  @into! F["scores_sub"] = tmp .+ Meta;
end

function sample_U!(U,Z,F,Q,S1,S2,k,r,shells)
  tau_e = shells["k_sub"];
  tau_u = shells["k2_sub"];
  b = shells["rbyk_sub"];
  m = shells["rbyk2_sub"];
  d = shells["r"];
  tmp = shells["r2"];
  sctmp = shells["kbyn_sub"];

  tau_e = 1./(1-F["h2_sub"]);
  tau_u = 1./F["h2_sub"];
  #b = Q' * Z * (F["scores"] .* tau_e)';
  @into! sctmp = F["scores_sub"] .* tau_e;
  @into! b = Z * sctmp';
  @into! m = Q' * b;
  for j in 1:k
    if tau_e[j] == 1
      U[j,:] = 0;
    elseif tau_e[j] == Inf
      U[j,:] = scores[j,:];
    else
      #d = S2*tau_u[j] + S1*tau_e[j];
      #@into! d = S1.*tau_e[j];
      #@into! tmp = S2*tau_u[j]
      #add!(d,tmp);

      #U[j,:] = ( Q * (mlam + (rand(Normal(),r) ./ sqrt(d))) )';
      for l in 1:r
        d = S2[l]*tau_u[j] + S1[l]*tau_e[j];
        tmp[l] = rand( Normal(m[l,j]/d, 1/sqrt(d)) );
      end
        U[j,:] = tmp'*Q';
    end
  end
end


function sample_h2!(F,Ur,eta,r,k,n,s,shells)
  vals = 0:(1/s):1;
  log_ps = shells["kbys_sub"];
  std_scores_b = shells["kbyn_sub"];
  std_scores = shells["kbyn2_sub"];
  tmp = shells["n"];
  tmps = shells["st"];

  @into! std_scores_b = F["scores_sub"]*Ur;
  for i in 1:s
    h2 = (i-1)/s;
    if h2 > 0
      #std_scores = 1/sqrt(h2) * ( std_scores_b ./ sqrt(eta + (1-h2)/h2 )' );
      #det = sum(log((eta+(1-h2)/h2)*h2)/2);
      det = 0;
      for j in 1:n
        for l in 1:k
          std_scores[l,j] = (1/sqrt(h2)) * std_scores_b[l,j] / sqrt(eta[j] + (1-h2)/h2);
        end
        det += log(eta[j]*h2 + (1-h2))/2;
      end
    else
      copy!(std_scores,F["scores_sub"]);
      det = 0;
    end
    for j in 1:k
      log_ps[j,i] = sum(logpdf!(tmp,Normal(),std_scores[j,:])) - det;
      if i == 1
        log_ps[j,i] += log(s-1);
      end
    end
  end
  for j in 1:k
    #norm_factor = maximum(log_ps[j,:]) + logsumexp(log_ps[j,:] - maximum(log_ps[j,:]))
    logpsj = sub(log_ps,j,:);
    @into! tmps = logpsj .- maximum(logpsj);
    norm_factor = maximum(logpsj) + logsumexp(tmps);
    #log_ps[j,:] = exp(log_ps[j,:] - norm_factor);
    @into! tmps = logpsj .- norm_factor;
    exp!(tmps);
    #h2[j] = vals[find( rand() > cumsum(log_ps[j,:]) )[1]]
    F["h2"][j] = find( rand(Multinomial(1,vec(tmps))) )[1] / s;
  end

end

function sample_Lambda!(F,Gps,Rps,X,B,Yt,ZAZvec,ZAZval,k,p,shells)
 # resid = shells["Yt"];
 # UtY = shells["nbyp"];
 # FtU = shells["kbyn_sub"];
  FUDj = shells["kbyn2_sub"];
  Llam = shells["kbyk_sub"];
  ZAZvalj = shells["nt"];
  Zlams = shells["kbyp_sub"];

  #@into!
  resid = B*X;
  add!(negate!(resid),Yt);
 # @into!
  UtY = ZAZvec' * resid';
 # @into!
  FtU = F["scores_sub"] * ZAZvec;
  rand!(Normal(),Zlams);
  for j in 1:p
    #FUDj = ( FtU ./ (ZAZval .+ Gps[j]./Rps[j]) ) .* Gps[j];
    @into! ZAZvalj = ZAZval .+ (Gps[j]/Rps[j]);
    @into! FUDj = FtU ./ ZAZvalj;
    @in1! FUDj .* Gps[j];
    #Qlam = FUDj*FtU' + diagm(F["Plam"][j,:]);
    #Llam = chol(Qlam,:L)
    @into! Llam = FUDj*FtU';
    add_diag!(Llam,F["Plam_sub"][j,:]);
    cholfact!(Llam,:L);
    tril!(Llam);

    means = FUDj*UtY[:,j];

    vlam = Llam\means;
    mlam = Llam'\vlam;
    ylam = Llam'\Zlams[:,j];
    add!(ylam,mlam);
    F["Lambda_sub"][j,:] = ylam;
  end
end

function sample_missing!(Yt,muYt,B,X,k,missloc,misssub);
     #muYt = Ytshape;
     @into! muYt = B*X;
     BLAS.gemm!('N','N',1.0,G["d"],Z,1.0,muYt);
     BLAS.gemm!('N','N',1.0,F["Lambda_sub"],F["scores_sub"],1.0,muYt);
     for l in 1:length(missloc)
       j = missloc[l];
       col = misssub[1][l];
       Yt[j] = rand(Normal(muYt[j],1/sqrt(Rps[col])));
     end
end

function sample_BD!(B,G,F,Rps,Yt,QtD,DA_Q,DA_S1,DA_S2,n,b,p,shells)
  means = shells["bnbyp"];
  resid = shells["pbyn"];
  N = n + b;
  mi = Array(Float64,N);
  Rpst = Rps';
  @into! resid = F["Lambda_sub"]*F["scores_sub"];
  add!(negate!(resid),Yt)

  @into! means = QtD*resid';
  @in1! means .* Rpst;
  for i in 1:p
    for j in 1:N
      d = DA_S1[j]*G["ps"][i] + DA_S2[j]*Rps[i];
      mi[j] = means[j,i] ./ d;
      mi[j] = rand( Normal(mi[j],1./sqrt(d)) );
    end
    up = DA_Q*mi;
    B[i,:] = up[1:b];
    G["d"][i,:] = mi[(b+1):N];
  end
end


function sample_precisions!(F,G,Rps,Lam2,resid,k,p,n,r,priors,shells)
  ss = shells["p"];

  for i in 1:p
    for j in 1:k
      F["psijh"][i,j] = rand(Gamma( priors["df"]/2 + 0.5,
                  2 ./ (priors["df"] + Lam2[i,j] .* F["tauh"][j]) ));
    end
  end

  #update noise precision
  vnorm!(ss,resid,2,2);
  pow!(ss,2);
  a = priors["as"] + 0.5*n;
  for j in 1:p
    b = 1./(priors["bs"] + 0.5*ss[j]^2);
    Rps[j] = rand(Gamma(a,b));
  end

  #update genetic effect precision
  vnorm!(ss,G["d"],2,2);
  pow!(ss,2);
  for j in 1:p
    G["ps"][j] = rand(Gamma(priors["as"] + 0.5*r,
                            1./(priors["bs"] + 0.5*ss[j]^2)));
  end
end
