# Set up each simulation.

immutable Sim
    u_0::Float64
    theta::Vector{Float64}
    alpha::Vector{Float64}
    beta::Vector{Float64}
    s::Matrix{Float64}
    w::Array{Float64, 3}
    b::Array{Float64, 4}
end


function set_up_sim( mp::Array, bp::Array, param::Parameters )

  # store some values in sim dictionary
  u_0 = mp[1]
  theta = mp[2:3]
  alpha = bp[1:2]
  beta = bp[3:4]

  # creeate arrays to store results from simulation function
  s = 999 * ones(param.D, param.T)
  w = zeros(param.D, param.T+1, param.I)
  b = zeros(param.D, param.T, param.I, 3)

  # Randomly generate initial w
  for d = 1 : param.D
    for i = 1 : param.I
      w[d, 1, i] = rand(0:0.01:param.w_max)
    end
  end


  # return output
  return Sim(u_0, theta, alpha, beta, s, w, b)

end

