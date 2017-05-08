function fsc_fastmulti{T}(X::Array{T, 2}, dictSize::Int, optParams::FSCOpts{T})
# Input:
#   X: H*WxN column of image patches
#
# Alg. parameters:
#   mu_max: 1e5
#   tau: [1.01 1.5] larger means faster convergence but sacrifices primal feasibility,
#        smaller means slower convergence

  const mu_max = 1e5;
  const tau = 1.01;

  const Dinit    = optParams.Dinit;
  const beta::T  = optParams.beta;
        mu_s::T  = optParams.mu_s;
        mu_t::T  = optParams.mu_t;
  const max_iter = optParams.max_iter;
  const tol      = optParams.tol;
  const FIXED_D  = optParams.FIXED_D;
  const DEBUG    = optParams.DEBUG;



  (filtLen, numPatches) = size(X);
  assert(!FIXED_D || !isempty(Dinit), "Dinit must be provided when FIXED_D is enabled.");
  assert(isempty(Dinit) || size(X, 1)==size(Dinit, 1), "Number of rows in Dinit and X do not match.");
  assert(isempty(Dinit) || size(Dinit, 2)==dictSize, "Dinit does not have the correct number of columns.");



  # Initialization
  if !FIXED_D;
    if isempty(Dinit);
      Dinit = reshape(mod([convert(T, 1):filtLen*dictSize], 13), (filtLen, dictSize));
    end
    d = Dinit';
    s = copy(d);
    normalize!(s);
    lambda_s = zeros(T, dictSize, filtLen);
  else;
    d = Dinit';
    s = d;
  end

  x = X;
  z = zeros(T, dictSize, numPatches);
  t = zeros(T, dictSize, numPatches);
  lambda_t = zeros(T, dictSize, numPatches);



  @printf("iter=00000");
  if DEBUG;
    debugData = {"x"=>X,
                 "d"=>d, "s"=>s,
                 "lambda_s"=>lambda_s,
                 "mu_s"=>mu_s,
                 "z"=>z, "t"=>t,
                 "lambda_t"=>lambda_t,
                 "mu_t"=>mu_t,
                 "beta"=>beta}
    (prev_obj,rerr,spar) = compute_lagrangian(debugData);
    @printf(": obj=%.10f (rerr=%.10f, spar=%.10f)\n", prev_obj, rerr, spar);
  end



  iter = 0;
  converged = false;
  if !FIXED_D;
    learnData = LearningData(zeros(T, dictSize, filtLen), zeros(T, dictSize, dictSize));
    learnParams = LearningOpts(T); learnParams.max_iter = 1; learnParams.tol = tol;
    if DEBUG;
      learnParams.DEBUG = DEBUG;
      learnParams.debugData = debugData;
    end
  end
  codeData = FastCodingData(zeros(T, dictSize, numPatches), zeros(T, dictSize, dictSize));
  codeParams = FastCodingOpts(T); codeParams.beta = beta; codeParams.max_iter = 1; codeParams.tol = tol;
  if DEBUG;
    codeParams.DEBUG = DEBUG;
    codeParams.debugData = debugData;
  end
  while ~converged;
    iter += 1;

    @printf("\b\b\b\b\b\b\b\b\b\biter=%05d", iter);
    if DEBUG;
      debugData["z"] = z; debugData["t"] = t;
      debugData["lambda_t"] = lambda_t;
      debugData["mu_t"] = mu_t;
      debugData["d"] = d; debugData["s"] = s;
      debugData["lambda_s"] = lambda_s;
      debugData["mu_s"] = mu_s;
      (prev_obj,rerr,spar) = compute_lagrangian(debugData);
      @printf(": obj=%.10f (rerr=%.10f, spar=%.10f)\n", prev_obj, rerr, spar);
    end

    #
    # CODING
    #
    Dt = d;
    codeData.DtD = Dt*Dt';
    codeData.Dtx = Dt*x;
    codeParams.z = z;
    codeParams.t = t;
    codeParams.lambda_t = lambda_t;
    codeParams.mu_t = mu_t;
    (z, t) = fsc_coding_fastmulti(codeData, codeParams);



    #
    # LEARNING
    #
    if !FIXED_D;
      fill!(learnData.ZtZ, 0);
      fill!(learnData.Ztx, 0);
      for j=1:numPatches;
        learnData.ZtZ += z[:, j]*z[:, j]';
        learnData.Ztx += z[:, j]*x[:, j]';
      end
      learnParams.Dinit = d;
      learnParams.s = s;
      learnParams.mu_s = mu_s;
      learnParams.lambda_s = lambda_s;
      (d, s) = fsc_learning_multi(learnData, learnParams);
    end




    # Update the Lagrangian multiplier
    for i=1:dictSize*numPatches; lambda_t[i] += mu_t*(z[i]-t[i]); end
    if !FIXED_D;
      for i=1:dictSize*filtLen; lambda_s[i] += mu_s*(d[i]-s[i]); end
    end
#    debugData["lambda_t"] = lambda_t;
#    debugData["lambda_s"] = lambda_s;
#    (obj,rerr,spar) = compute_lagrangian(debugData);
#    is_mono = (prev_obj>=obj) ? 'O' : 'X';
#    @printf("          L: %c obj=%.10f (rerr=%.10f, spar=%.10f)\n", is_mono, obj, rerr, spar);
#    prev_obj = obj;

    # Update penalty term
    mu_t = min(tau*mu_t, mu_max);
    mu_s = min(tau*mu_s, mu_max);
#    debugData["mu_t"] = mu_t;
#    debugData["mu_s"] = mu_s;
#    (obj,rerr,spar) = compute_lagrangian(debugData);
#    is_mono = (prev_obj>=obj) ? 'O' : 'X';
#    @printf("          M: %c obj=%.10f (rerr=%.10f, spar=%.10f)\n", is_mono, obj, rerr, spar);
#    prev_obj = obj;



    learnConverged = FIXED_D || mean((d-s).^2)<=tol;
    codeConverged = true;
    for j=1:numPatches;
      if mu_t>0 && mean((z[:, j]-t[:, j]).^2)>tol;
        codeConverged = false;
        break
      end
    end
    if iter>=max_iter || (learnConverged && codeConverged);
      converged = true;
    end
  end
  return (s', z, t);
end
