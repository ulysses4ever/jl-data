# Helper functions
function z_subproblem!{T}(z::Array{T, 2},
                          t::Array{T, 2}, mu_t::T, lambda_t::Array{T, 2},
                          DtD::Array{T, 2}, Dtx::Array{T, 2})
  dictSize = size(DtD, 1);
  # z = ( DtD + mu_t.*I ) \ ( Dtx + mu_t.*t - lambda_t )
  A = copy(DtD);
  for i=1:dictSize; A[i, i] += mu_t; end
  b = copy(t);
  scale!(b, mu_t);
  b += Dtx;
  b -= lambda_t;
  z[:, :] = A\b;
  return z::Array{T, 2};
end

function t_subproblem!{T}(t::Array{T, 2}, z::Array{T, 2}, mu_t::T, lambda_t::Array{T, 2}, beta::T)
  if mu_t>0;
    # shrink!(t, z+lambda_t/mu_t, beta/mu_t);
    for i=1:length(t);
      t[i] = lambda_t[i]/mu_t + z[i];
    end
    shrink!(t, t, beta/mu_t);
  else;
    fill!(t, 0);
  end
  return t::Array{T, 2};
end


function fsc_coding_fastmulti{T}(data::FastCodingData{T}, optParams::FastCodingOpts{T})
# Alg. parameters:
#   mu_max: 1e5
#   tau: [1.01 1.5] larger means faster convergence but sacrifices primal feasibility,
#        smaller means slower convergence

  const mu_max = 1e5;
  const tau = 1.01;

  const Dtx          = data.Dtx;
  const DtD          = data.DtD;
        z            = optParams.z;
        t            = optParams.t;
        lambda_t     = optParams.lambda_t;
  const beta::T      = optParams.beta;
        mu_t::T      = optParams.mu_t;
  const max_iter     = optParams.max_iter;
  const tol          = optParams.tol;
  const DEBUG        = optParams.DEBUG;
        debugData    = optParams.debugData;



  (filtLen, numImgs) = size(Dtx);
  dictSize = size(DtD, 1);

  assert(size(Dtx, 1)==dictSize, "Dtx does not have the correct dimensions.")
  z = initcheck(z, T, (dictSize, numImgs), "z does not have the correct dimensions.");
  t = initcheck(t, T, (dictSize, numImgs), "t does not have the correct dimensions.");
  lambda_t = initcheck(lambda_t, T, (dictSize, numImgs), "lambda_t does not have the correct dimensions.");



  if DEBUG;
    debugData["z"] = z;
    debugData["t"] = t;
    debugData["lambda_t"] = lambda_t;
    (prev_obj, rerr, spar) = compute_lagrangian(debugData);
  end



  iter = 0;
  converged = false;
  while ~converged;
    iter += 1;

    if max_iter>1; @printf("\b\b\b\b\b%05d", iter); end

    # Solve for z* in the frequency domain
    z_subproblem!(z, t, mu_t, lambda_t, DtD, Dtx);
    if DEBUG;
      debugData["z"] = z;
      (obj, rerr, spar) = compute_lagrangian(debugData);
      is_mono = (prev_obj>=obj) ? 'O' : 'X';
      @printf("            Z: %c obj=%.10f (rerr=%.10f, spar=%.10f)\n", is_mono, obj, rerr, spar);
      prev_obj = obj;
    end


    # Solve for t* in the spatial domain
    t_subproblem!(t, z, mu_t, lambda_t, beta);
    if DEBUG;
      debugData["t"] = t;
      (obj, rerr, spar) = compute_lagrangian(debugData);
      is_mono = (prev_obj>=obj) ? 'O' : 'X';
      @printf("            T: %c obj=%.10f (rerr=%.10f, spar=%.10f)\n", is_mono, obj, rerr, spar);
      prev_obj = obj;
    end


    if max_iter==1; return (z, t); end # Don't do unnecessary work

    # Update the Lagrangian multipliers
    for i=1:filtLen*dictSize; lambda_t[i] += mu_t*( z[i]-t[i] ); end
    if DEBUG;
      debugData["lambda_t"] = lambda_t;
      (obj, rerr, spar) = compute_lagrangian(debugData);
      is_mono = (prev_obj>=obj) ? 'O' : 'X';
      @printf("            L: %c obj=%.10f (rerr=%.10f, spar=%.10f)\n", is_mono, obj, rerr, spar);
      prev_obj = obj;
    end

    # Update penalty term
    mu_t = min(tau*mu_t, mu_max);
    if DEBUG;
      debugData["mu_t"] = mu_t;
      (obj, rerr, spar) = compute_lagrangian(debugData);
      is_mono = (prev_obj>=obj) ? 'O' : 'X';
      @printf("            M: %c obj=%.10f (rerr=%.10f, spar=%.10f)\n", is_mono, obj, rerr, spar);
      prev_obj = obj;
    end



    codesConverged = true;
    for j=1:numImgs;
      if mu_t>0 && mean((z[:, j]-t[:, j]).^2)>tol;
        codesConverged = false;
        break;
      end
    end
    if iter>=max_iter || codesConverged;
      converged = true;
    end
  end

  return (z, t);
end
