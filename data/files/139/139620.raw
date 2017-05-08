# Helper functions
function d_subproblem{T}(s::Array{T, 2}, mu_s::T, lambda_s::Array{T, 2},
                         ZtZ::Array{T, 2}, Ztx::Array{T, 2})
  filtLen = size(s, 2);
  dictSize = size(ZtZ, 1);
  # d = ( ZtZ + mu_s.*I ) \ ( Ztx + mu_s.*s - lambda_s )
  A = copy(ZtZ);
  for j=1:dictSize; A[j, j] += mu_s; end
  b = copy(s);
  scale!(b, mu_s);
  b += Ztx;
  b -= lambda_s;
  d = A\b;
  return d::Array{T, 2};
end

function s_subproblem{T}(d::Array{T, 2}, mu_s::T, lambda_s::Array{T, 2})
  # s = d + 1/mu_s.*lambda_s;
  s = copy(lambda_s);
  scale!(s, 1/mu_s);
  s += d;
  normalize!(s);
  return s::Array{T, 2};
end


function fsc_learning_multi{T}(data::LearningData{T}, optParams::LearningOpts{T})
# Alg. parameters:
#   mu_max: 1e5
#   tau: [1.01 1.5] larger means faster convergence but sacrifices primal feasibility,
#        smaller means slower convergence

  const mu_max = 1e5;
  const tau = 1.01;

  const ZtZ       = data.ZtZ;
  const Ztx       = data.Ztx;
  const d         = optParams.Dinit;
        lambda_s  = optParams.lambda_s;
        mu_s::T   = optParams.mu_s;
  const max_iter  = optParams.max_iter;
  const tol       = optParams.tol;
  const DEBUG     = optParams.DEBUG;
        debugData = optParams.debugData;



  filtLen = size(Ztx, 2);
  dictSize = size(ZtZ, 1);

  assert(size(Ztx, 1)==dictSize, "Ztx does not have the correct dimensions.")
  assert(isempty(d) || size(d, 1)==dictSize,
    "Number of filters in Dinit does not match the number of channels in Z.")


  # Initialization
  if isempty(lambda_s);
    lambda_s = zeros(T, dictSize, filtLen);
  end
  if isempty(d);
    d = zeros(T, dictSize, filtLen);
  end
  s = s_subproblem(d, mu_s, lambda_s);



  if DEBUG;
    debugData["d"] = d;
    debugData["s"] = s;
    debugData["lambda_s"] = lambda_s;
    (prev_obj, rerr, spar) = compute_lagrangian(debugData);
  end



  iter = 0;
  converged = false;
  while ~converged;
    iter += 1;

    if max_iter>1; @printf("\b\b\b\b\b%05d", iter); end

    # Solve for d* in the frequency domain
    d = d_subproblem(s, mu_s, lambda_s, ZtZ, Ztx);
    if DEBUG;
      debugData["d"] = d;
      (obj, rerr, spar) = compute_lagrangian(debugData);
      is_mono = (prev_obj>=obj) ? 'O' : 'X';
      @printf("            D: %c obj=%.10f (rerr=%.10f, spar=%.10f)\n", is_mono, obj, rerr, spar);
      prev_obj = obj;
    end


    # Solve for s* in the spatial domain
    s = s_subproblem(d, mu_s, lambda_s);
    if DEBUG;
      debugData["s"] = s;
      (obj, rerr, spar) = compute_lagrangian(debugData);
      is_mono = (prev_obj>=obj) ? 'O' : 'X';
      @printf("            S: %c obj=%.10f (rerr=%.10f, spar=%.10f)\n", is_mono, obj, rerr, spar);
      prev_obj = obj;
    end



    if max_iter==1; return (d, s); end # Don't do unnecessary work

    # Update the Lagrangian multipliers
    for i=1:filtLen*dictSize; lambda_s[i] += mu_s*( d[i]-s[i] ); end
    if DEBUG;
      debugData["lambda_s"] = lambda_s;
      (obj, rerr, spar) = compute_lagrangian(debugData);
      is_mono = (prev_obj>=obj) ? 'O' : 'X';
      @printf("            L: %c obj=%.10f (rerr=%.10f, spar=%.10f)\n", is_mono, obj, rerr, spar);
      prev_obj = obj;
    end

    # Update penalty term
    mu_s = min(tau*mu_s, mu_max);
    if DEBUG;
      debugData["mu_s"] = mu_s;
      (obj, rerr, spar) = compute_lagrangian(debugData);
      is_mono = (prev_obj>=obj) ? 'O' : 'X';
      @printf("            M: %c obj=%.10f (rerr=%.10f, spar=%.10f)\n", is_mono, obj, rerr, spar);
      prev_obj = obj;
    end



    if iter>=max_iter || mean((d-s).^2)<=tol;
      converged = true;
    end
  end

  return (d, s);

end
