# Update value of w.

function update_w(d::Int64, t::Int64, i::Int64, sim::Sim,
                  param::Parameters, dist::Dist, data::Data)

  # extract parameters
  w_max = param.w_max
  signal = data.signals[i]

  # calculate distribution of o (depends on i)
  Prob_o_i = vec(dist_o_i( signal, dist ))

  # calculate net
  net_ = calc_net( d, t, i, sim, param )

  # avoid 0 * -Inf error

  net_adjusted_ = zeros(Prob_o_i)
  for i in length(Prob_o_i)
      if Prob_o_i[i] == 0
          net_adjusted_[i] = net_[i] + 1e-12
      end
  end

  # Julia adjustments: change to vectors
  # Why? Prob_o_i * net_adjusted_ yields Array{Float64, 2}, which is not
  # compatible with the scalar comparison below.

  # calculate updated w
  w_new = exp(dot(Prob_o_i, log(net_adjusted_)))
  #w_new = exp(Prob_o_i * log(net_adjusted_))

  # w_new cannot exceed w_max
  # Julia issue: w_new is an Array{Float64,2}, not a Float64.
  # Solution: change Prob_outcome_i and net_adjusted_ to vectors and use
  # dot() to multiply the vectors. Better solution available?
  if w_new - w_max > 1e-8
    w_new = w_max
  end


  # return output
  return w_new

end
