### SR1
immutable SR1State
  old_dirs :: Vector{Vector{Float64}}
  old_stps :: Vector{Vector{Float64}}
  Hdiag :: Float64
  L :: Matrix{Float64}
  D :: Vector{Float64}
  m :: Int64
end

SR1State(d :: Int64, m :: Int64) = SR1State(Array(Vector{Float64},0),Array(Vector{Float64},0),1.0,
 zeros(d,0),zeros(0),m)

function applyQF(state :: SR1State, x :: Vector{Float64}, v:: Vector{Float64})
  return (0.5)*dot(x, state.Hdiag * v + state.L*diagm(state.D)*(state.L'*v))
end

function getDecomposition(state:: SR1State)
  return (state.Hdiag,state.L,state.D)
end


function update(delta_x, delta_g, state :: SR1State)
  local y = delta_g #g_proposal - g
  local s = delta_x
  local ys = dot(y,s)
  local Bs = state.Hdiag*s + state.L*(diagm(state.D)*(state.L'*s))
  local LHS = abs(ys - dot(s,Bs))
  local RHS = norm(y - Bs)*norm(s)
  if  LHS > 1E-8*RHS #this always happens.
    #verbose("ys=$ys")
    #-- updating memory
    old_dirs = state.old_dirs
    old_stps = state.old_stps
    if length(state.old_dirs) == state.m
      #-- shift history by one (limited-memory!)
      local prev_old_dirs = state.old_dirs
      local prev_old_stps = state.old_stps
      old_dirs = Array(Vector{Float64},0)
      old_stps = Array(Vector{Float64},0)
      for i = 2:state.m
        append!(old_dirs, {prev_old_dirs[i]})
        append!(old_stps, {prev_old_stps[i]})
      end
    end

    #-- store new direction/step
    append!(old_dirs,{s})
    append!(old_stps,{y})

    #-- update scale of initial Hessian approximation
    #abs(ys/dot(y,y))#
    #actually, this seems to kill performance... why?
    println("L-BFGS D = $(ys/dot(y,y)), BB D = $(dot(s,s)/ys)")
    Hdiag = (dot(s,s)/ys)#1.0##(ys/dot(y,y))#1.0
    #update L, D
    local k = length(old_dirs)
    L = zeros(length(delta_x),length(old_dirs))
    D = zeros(length(old_dirs))
    #iterate over memory
    for i = 1:k
      #compute B_{i-1} * s_{i-1}
      l_i = old_stps[i] - (Hdiag*old_dirs[i] + L*(diagm(D)*(L'*old_dirs[i])))
      rho_i = dot(l_i, old_dirs[i])
      D[i] = 1.0/rho_i
      L[:,i] = l_i
    end
    return SR1State(old_dirs, old_stps, Hdiag, L,D,state.m)
  else
    verbose("Not updating memory! $LHS < $RHS")
    return state
  end
end
