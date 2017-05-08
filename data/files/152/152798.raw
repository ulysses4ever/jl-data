include("SR1.jl")

function bisection(f, l,u; iters = 1000, tol = 1E-5)
  for i = 1:iters
    midpoint = (l+u)/2
    v = f(midpoint)
    if (abs(v) < tol)
      break
    end
    if (sign(v) == sign(f(l)))
      l = midpoint
    else
      u = midpoint
    end
  end
  return (l+u)/2
end

#solves
#argmin_p <g,p> + (1/2)p^T(M)*p s.t. ||p|| <= delta
function trustRegionSubproblem(qn_state :: FullRankApproximation,g,delta, verbose)
  M = getMatrix(qn_state)
  if (delta <= 0.0)
    error("Need a positive trust-radius!")
  end
  (e,evs) = eig(M)

  l_min = minimum(e)
  L_part = -evs'*g
  L_part_norms = L_part.^2
  #need to find gamma s.t. following are true:
  # (B + gamma)p^* = -g
  # gamma*(delta - ||p||) = 0
  # B + gamma is p.s.d
  p(gamma) = sqrt(sum(L_part_norms./((e.+gamma).^2)) )

  #first, check if hess is psd and gamma = 0 works...
  if (l_min >= 0.0 && p(0.0) <= delta)
    verbose("LMTR :: Hessian PSD and trust region inactive.")
    return evs*( diagm(1.0./e))*L_part
  end

  #Otherwise, do bisection search to find gamma
  #for gamma > abs(l_min), this is monotone decreasing function -> bisection works...

  #upper bound:
  ub = sqrt(sum(L_part_norms))/delta - min(l_min,0.0)
  #bisection search to find gamma....
  gamma = bisection(gamma -> p(gamma) - delta,abs(min(0.0,l_min)),ub)

  d = evs*( diagm(1.0./(e.+gamma) )*L_part)
  return d
end

#solves
# argmin_p <g,p> + (1/2)p^T(lambda*I + L*diagm(D)*L')*p s.t. ||p|| <= delta
function trustRegionSubproblem(lm_state :: LowRankApproximation,g,delta, verbose)
  #lambda, L, D,delta
  (lambda,L,D) = getDecomposition(lm_state)
  (d,k) = size(L)
  assert(length(g) == d)
  if (k >= d)
    error("Not designed to work for full rank approximations!")
  end
  if (delta <= 0.0)
    error("Need a postive trust-region radius!")
  end

  if (size(L,2) > 0)
    K = L'*L;
    (e_k,u_k) = eig(Symmetric(K,'u'))
    #NOTE THAT THIS MAY FAIL IF USING SINGLE-PRECISION FLOATS
    nonzero_inds = e_k.>1E-8
    if (length(nonzero_inds) .!= size(K,1))
      verbose("Clipping eigenvalues of K: $e_k")
    end
    e_k = e_k[nonzero_inds]
    u_k = u_k[:,nonzero_inds]

    K_sqrt = u_k*diagm(sqrt(e_k))*u_k'
    K_inv_sqrt = u_k*diagm(1.0./sqrt(e_k))*u_k'
    (e,u) = eig(Symmetric(K_sqrt*diagm(D)*K_sqrt,'u'))

    nonzero_inds = abs(e).>1E-8
    if (length(nonzero_inds) .!= size(K,1))
      verbose("Clipping eigenvalues: $e")
    end
    e = e[nonzero_inds] + lambda
    u = u[:,nonzero_inds]
    evs = L*(K_inv_sqrt*u)
    #e holds the eigenvalues of L*D*L'
    l_min = min(lambda, minimum(e))
  else
    e = [1.0]
    evs = zeros(d,1)
    l_min = lambda
  end

  L_part = -evs'*g
  null_part = -g + evs*(evs'*g) #sign error...
  L_part_norms = L_part.^2
  null_part_norm = dot(null_part,null_part)
  #-(B + gamma*I)^-1(g) = evs*(diagm(1.0/(e + gamma)))*L_part + (1.0/(lambda + gamma))*null_part

  #need to find gamma s.t. following are true:
  # (B + gamma)p^* = -g
  # gamma*(delta - ||p||) = 0
  # B + gamma is p.s.d
  p(gamma) = sqrt(sum(L_part_norms./((e.+gamma).^2))+ null_part_norm./((lambda + gamma).^2))

  #first, check if hess is psd and gamma = 0 works...
  if (l_min >= 0.0 && p(0.0) <= delta)
    verbose("Trust region inactive and hessian PSD.")
    return evs*(diagm(1.0./e)*L_part) + (1.0/lambda)*null_part
  end

  verbose("Minimum eigenvalue: $l_min")
  #Otherwise, do bisection search to find gamma
  #for gamma > abs(min(l_min,0.0)), this is monotone decreasing function -> bisection works...

  #upper bound:
  ub = sqrt(sum(L_part_norms)+null_part_norm)/delta - min(l_min,0.0)
  #bisection search to find gamma....
  gamma = bisection(gamma -> p(gamma) - delta,abs(min(0.0,l_min)),ub)

  d = evs*( diagm(1.0./(e + gamma))*L_part) + (1.0/(lambda + gamma))*null_part
  obj_val = dot(g,d) +0.5*dot(d,lambda*d + L*(diagm(D)*(L'*d)))
  if (obj_val > 0.0)
    error("Did not achieve reduction!")
  end
  return d
end

function newtonTrustRegionMethod(f_g_h,start, delta, eta; d_max :: Float64 = Inf, max_iters :: Int64 = 10)
  x = start
  (f_val,g,H) = f_g_h(x)
  for k = 1:max_iters
    (f_val,g,H) = f_g_h(x)
    println("$k : $delta, $f_val")
    #get new search point
    delta_x = trustRegionSubproblem(g, H, delta)
    (f_new,g_new,H_new) = f_g_h(x + delta_x)
    #compute reduction in function v.s. model
    rho = -(f_val - f_new)/(dot(delta_x,g) + (0.5)*dot(delta_x, H*delta_x))
    if rho < 1/4
      println("unsuccessful TR step!")
      delta = delta*(0.25)
    else
      if rho > 0.75 && abs(norm(delta_x)-delta)<1E-4
        println("TR active, good step!")
        delta = delta*2
      end
    end
    if rho > eta
      x = x + delta_x
    end
  end

end


####
# This function combines the quasi-newton method SR1 with a basic trust region method.
# The implementation is inefficient.
# Based on torch implementation of LBFGS
function lmtr(opfunc!, x_init, maxIter, lm_state :: HessianApproximation;
  delta :: Float64 = 1.0,
  eta :: Float64 = 1E-5,
  verbose_output :: Bool = true,
  callback :: Function = (x,iter) -> return)

  local x = copy(x_init)
  local g = zeros(x)
  local f_val = opfunc!(x,g)
  local f_hist = {f_val}
  local d = length(g)

  local g_proposal = copy(g)
  local f_proposal = zero(f_val)

  function verbose(s)
    if verbose_output
      println("LMTR :: ",s)
    end
  end

  for nIter = 1:maxIter
    verbose("$nIter : obj_val=$f_val  radius = $delta")
    #get new search direction
    delta_this_round = delta
    #verbose("delta = $delta_this_round, Hdiag = $(lm_state.Hdiag)")
    @time delta_x = trustRegionSubproblem(lm_state, g,delta_this_round,verbose)
    new_x  = x + delta_x
    f_proposal = opfunc!(new_x,g_proposal)
    if norm(g_proposal) < 1E-8
      break;
    end

    #compute reduction in function v.s. model
    rho = -(f_val - f_proposal)/(dot(delta_x,g) +
      applyQF(lm_state, delta_x, delta_x))#(0.5)*dot(delta_x, Hdiag * delta_x + L*diagm(D)*(L'*delta_x)))
    #verbose("rho = $rho")
    if (f_val - f_proposal) < 0.0 #rho < 0.1
      #verbose("unsuccessful TR step!")
      delta *= 0.5
    else
      if rho > 0.75
        #verbose("increasing radius!")
        #if norm(delta_x)>0.8*delta_this_round
          delta *= 2
        #end
      end
    end
    #-- update memory
    #-- we should factor this out...
    delta_g = g_proposal - g
    @time lm_state = update(delta_x,delta_g,lm_state)

    #-- initial guess for step size
    # * learningRate # check this later...
    if rho > eta
      x = x + delta_x
      f_val = f_proposal
      temp = g
      g = g_proposal
      g_proposal = temp
    else
      verbose("rejecting step!")
    end
    append!(f_hist,{f_val})
    callback(x,nIter)
  end
  return (x,f_hist)
end
