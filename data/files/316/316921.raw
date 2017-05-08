# For a given i, determine distribution of o.

function dist_o_i( signal::Float64, dist::Dist )

  o_vec = dist.prob_o[1,:]

  # create simple distribution
  Prob_o_i = zeros(1, length(o_vec))
  for idx = 1:length(o_vec)
    if o_vec[idx] == (signal - 1) || o_vec[idx] == (signal + 1)
      Prob_o_i[idx] = 0.3
    elseif o_vec[idx] == (signal)
      Prob_o_i[idx] = 0.4
    end
  end

  # verify this is a proper distribution
  if abs(sum(Prob_o_i) - 1) > 1e-8
    @printf "Error: Distribution Prob_o_i does not sum to 1. \n"
  end


  # return output
  return Prob_o_i

end
