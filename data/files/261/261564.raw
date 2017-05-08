function update_derivs_pos!(state::Vector{Float64}, derivs::Vector{Float64} )
 # Input: state = [x,y,vx,vy], a vector of two 2-d positions and velocities for a test particle
 # Output: The derivatives of the position are updated in the preallocated array derivs.
  @assert length(state) == 4
  @assert length(derivs) == 4
  v_x = state[3]
  v_y = state[4]
  derivs[1] = v_x
  derivs[2] = v_y
  return derivs;
end

state = [0.,1.,1.,0.];
derivs = [0.,0.,0.,0.];
Profile.clear()
for i = 1:100000000;update_derivs_pos!(state, derivs);end
@profile {for i = 1:100000000;update_derivs_pos!(state, derivs);end}
Profile.print()
