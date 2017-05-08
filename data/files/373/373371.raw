# Run files to perform one simulation.

# include functions
include("set_up.jl")
include("set_up_sim.jl")
include("dist_o_i.jl")
include("calc_net.jl")
include("update_w.jl")

include("simulation.jl")

# set up
# (what is the best way to make these local variables to improve speed?)

v1 = [-3 0.5 0.5]

# run simulation within context of other (omitted) code until termination
# condition is satisfied.
term_condition = false
iter = 0
while !term_condition

  # determine vector v2
  # here, v2 is just hard-coded; in general, v2 changes each iteration
  v2 = [-1.5 0 1.5 0]

  # run simulation a bunch of times
  sim = @time simulation( v1, v2, param, dist, data )

  # omitted: do stuff with simulation output

  # increment iteration
  iter = iter + 1

  # check termination condition
  # here, run just run simulation once to simplify problem
  if iter >= 1
    term_condition = true
  end

end
