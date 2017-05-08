# Set up each simulation.

function set_up_sim( mp::Array, bp::Array, param::Dict )

  # initialize dictionary for this simulation
  sim = Dict()

  # store some values in sim dictionary
  sim["u_0"] = mp[1]
  sim["theta"] = mp[2:3]
  sim["alpha"] = bp[1:2]
  sim["beta"] = bp[3:4]

  # creeate arrays to store results from simulation function
  sim["s"] = 999 * ones(param["D"], param["T"])
  sim["w"] = zeros(param["D"], param["T"]+1, param["I"])
  sim["b"] = zeros(param["D"], param["T"], param["I"], 3)

  # Randomly generate initial w
  for d = 1 : param["D"]
    for i = 1 : param["I"]
      sim["w"][d, 1, i] = rand(0:0.01:param["w_max"])
    end
  end


  # return output
  return sim

end

