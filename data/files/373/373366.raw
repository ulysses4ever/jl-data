# Calculate vector called "net"

function calc_net( d::Int64, t::Int64, i::Int64, sim::Dict, param::Dict )

  # name some things
  gamma = param["gamma"]
  o_vec = param["o_vec"]
  numO = length(o_vec)
  w0 = sim["w"][d, 1, i]

  # retrieve some history
  b_hist = reshape(sim["b"][d, 1:t, i, :], t, 3)
  b_hist_col2 = reshape(sim["b"][d, 1:t, i, 2], t, 1)
  b_hist_col2_A = b_hist_col2 .* (b_hist[:,1] .== 65)
  b_hist_col2_B = b_hist_col2 .* (b_hist[:,1] .== 66)

  # -----------------------------------------------------------------------
  # sum some stuff according to some conditions
  b_A_su_ = zeros(numO, 1)
  b_B_su_ = zeros(numO, 1)
  b_A_pu_ = zeros(numO, 1)
  b_B_pu_ = zeros(numO, 1)

  for idx = 1:numO

    o = o_vec[idx]

    # conditions in which something occurs
    cond_A_su = (o .< b_hist[:,3]) & (b_hist[:,1] .== 65)
    cond_B_su = (o .> b_hist[:,3]) & (b_hist[:,1] .== 66)

    # conditions in which something occurs
    cond_A_pu = (o .== b_hist[:,3]) & (b_hist[:,1] .== 65)
    cond_B_pu = (o .== b_hist[:,3]) & (b_hist[:,1] .== 66)

    # sum stuff according to conditions
    b_A_su_[idx] = sum(b_hist_col2 .* cond_A_su)
    b_B_su_[idx] = sum(b_hist_col2 .* cond_B_su)

    # sum stuff according to conditions
    b_A_pu_[idx] = sum(b_hist_col2 .* cond_A_pu)
    b_B_pu_[idx] = sum(b_hist_col2 .* cond_B_pu)

  end # idx
  # -----------------------------------------------------------------------


  # get things in right dimensions for calculation below
  w0_ = repmat([w0], numO, 1)
  total_b_A_ = repmat([sum(b_hist_col2_A)], numO, 1)
  total_b_B_ = repmat([sum(b_hist_col2_B)], numO, 1)

  # calculate net
  net_ = w0_ - total_b_A_ - total_b_B_ + b_A_pu_ + b_B_pu_ +
    (1 + gamma) .* (b_A_su_ + b_B_su_)

  # temporarily impose minimum on values of net_
  net_ = max(net_, 0.1)

  # return output
  return net_

end
