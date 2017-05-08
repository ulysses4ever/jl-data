include("SR1.jl")


function SFNSubproblem(g, lambda, L, D, verbose)
  (d,k) = size(L)
  assert(length(g) == d)
  if (k >= d)
    error("Not designed to work for full rank approximations!")
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
    (e,u) = eig(Symmetric(K_inv_sqrt*K*diagm(D)*K*K_inv_sqrt,'u'))

    nonzero_inds = abs(e).>1E-8
    if (length(nonzero_inds) .!= size(K,1))
      verbose("Clipping eigenvalues: $e")
    end
    e = e[nonzero_inds] + lambda
    u = u[:,nonzero_inds]
    evs = L*K_inv_sqrt*u
    #e holds the eigenvalues of L*D*L'
    l_min = min(lambda, minimum(e))
  else
    e = [1.0]
    evs = zeros(d,1)
    l_min = lambda
  end

  L_part = -evs'*g
  null_part = -g + evs*(evs'*g)
  return evs*(diagm(1.0./abs(e)))*L_part + (1.0/abs(lambda))*null_part
end

####
# This function combines the quasi-newton method SR1 with Bengio's SFN.
# The implementation is inefficient.
# Based on torch implementation of LBFGS
function sfn(opfunc!, x_init, maxIter;
  eta :: Float64 = 1E-5,
  verbose_output :: Bool = true,
  callback :: Function = (x,iter) -> return,
  m :: Int64 = 10)

  local x = copy(x_init)
  local g = zeros(x)
  local f_val = opfunc!(x,g)
  local f_hist = {f_val}
  local d = length(g)
  lm_state = SR1State(d,m)

  local g_proposal = copy(g)
  local f_proposal = zero(f_val)

  function verbose(s)
    if verbose_output
      println("SFN :: ",s)
    end
  end

  for nIter = 1:maxIter
    verbose("$nIter : obj_val=$f_val")
    #get new search direction
    verbose("Hdiag = $(lm_state.Hdiag)")
    (h_d,lm_L,lm_D) = getDecomposition(lm_state)
    delta_x = SFNSubproblem(g, h_d, lm_L,lm_D,verbose)
    new_x  = x + delta_x
    f_proposal = opfunc!(new_x,g_proposal)
    if norm(g_proposal) < 1E-8
      break;
    end
    #-- update memory
    #-- we should factor this out...
    delta_g = g_proposal - g
    lm_state = update(delta_x,delta_g,lm_state)

    #add a line search here...
    x = x + delta_x
    f_val = f_proposal
    temp = g
    g = g_proposal
    g_proposal = temp

    append!(f_hist,{f_val})
    callback(x,nIter)
  end
  return (x,f_hist)
end
