using Gadfly
function half_cos_decay(θ::Float64)
  if θ < 0.5
    0.25 * cos(θ * 2 * pi) + 0.75
  else
    if 0.5 <= θ < 1.0
      0.25 * cos((θ - 0.5) * 2 * pi) + 0.25
    else
      0.0
    end
  end
end

function closest_dist_with_i(θ::Float64, n::Int64)
  # wrap around θ first
  θ = θ % n
  lower_bnd = floor(θ)
  upper_bnd = ceil(θ)
  lower_dist, lower_idx = abs(lower_bnd-θ), int(lower_bnd)
  upper_dist, upper_idx = abs(upper_bnd-θ), int(upper_bnd)
  if (upper_idx == n) upper_idx = 0 end
  min((lower_dist, lower_idx), (upper_dist, upper_idx))
end

function get_weight_distribution(θ::Float64, n::Int64)
  closest_dist, closet_i = closest_dist_with_i(θ, n)
  [(if i == closet_i
      half_cos_decay(closest_dist)
      #closest_dist
    else
      half_cos_decay(1 - closest_dist)
#       1 - closest_dist
    end
    ) for i in 0:n-1 ]
end

function get_mixed_binop(weights::Array{Float64}, ops::Array{Function})
  total_weights = sum(weights)
  function mixed_binop(x, y)
    ret = 0.0
    for i in 1:length(ops)
      ret = ret + (1 / total_weights * weights[i] * ops[i](x,y))
    end
    ret
  end
  mixed_binop
end

function get_parametrized_binop(ops::Array{Function})
  function parametrized_binop(θ::Float64)
    weights = get_weight_distribution(θ, length(ops))
    mixed_binop = get_mixed_binop(weights, ops)
    mixed_binop
  end
  parametrized_binop
end

# parametrized_binop1 = get_parametrized_binop([+, -, *, /])
# plot(θ->parametrized_binop1(θ)(4.0, -9.0), 0, 4)

# plot(z=(θ,x) -> parametrized_binop1(θ)(x, 2.0),
#      x=linspace(0.0,3.0,100), y=linspace(0.0,3.0,100), Geom.contour)



# # plot(x->half_cos_decay(x), 0, 2.0)

# # plot(x->get_weight_distribution(x,4)[1], 0, 10.0)
# # plot(x->get_weight_distribution(x,4)[2], 0, 10.0)
# # plot(x->get_weight_distribution(x,4)[3], 0, 10.0)
# # plot(x->get_weight_distribution(x,4)[4], 0, 10.0)

