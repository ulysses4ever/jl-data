using Optim

type Boost
  c :: Float64
  weights::Array{Float64}
  weaks::Array{Function}
end

function init_boost(c::Float64)
  Boost(c, Float64[], Function[])
end

function beval(boost::Boost, x...)
  ret = boost.c
  for i in 1:length(boost.weights)
    ret += boost.weights[i] * boost.weaks[i](x...)
  end
  ret
end

function get_neg_residual(Fcurrent::Function, data)
  ret = typeof(data[1])[]
  for d in data
    x, y = d
    y_pred = Fcurrent(x)
    push!(ret, (x, y - y_pred))
  end
  ret
end

function get_random_params(paramb_n::Int64, paramr_range)
  paramb = Bool[(rand()<0.5) for i in 1:paramb_n]
  paramr = [rand()*(paramr_range[i][2] - paramr_range[i][1])+paramr_range[i][1] for i in 1:length(paramr_range)]
  paramb, paramr
end

# get the error frunction for the weak learner h
function get_h_error_function(f, residual_data)
  function err_fun(paramb::Array{Bool}, paramr::Array{Float64})
    ret = 0.0
    for d in residual_data
      x, y = d
      yy = f(x...,paramb, paramr)
      ret += (y - yy)^2
    end
    ret
  end
  err_fun
end

# get sample h error function
function get_h_sample_error_function(f, residual_data)
  function sample_err_fun(paramb::Array{Bool}, paramr::Array{Float64})
    ret = 0.0
    for d in residual_data
      if rand() < 0.6
        x, y = d
        yy = f(x...,paramb, paramr)
        ret += (y - yy)^2
      end
    end
    ret
  end
  sample_err_fun
end

# get the error function for the weight w
function get_w_error_function(Fcurrent, h, data)
  function err_fun(w)
    ret = 0.0
    for d in data
      x, y = d
      yy = Fcurrent(x) + w[1] * h(x...)
      ret += (y - yy) ^2
    end
    ret
  end
  err_fun
end

function sample_weak_learner(h_err_fun, paramb_n,paramr_range::Array{(Float64,Float64)})
  paramb_best, paramr_best = get_random_params(paramb_n, paramr_range)
  best_err = Inf
  for i in 1:1
    paramb, paramr_init = get_random_params(paramb_n, paramr_range)
    result = optimize(vect->h_err_fun(paramb,vect), paramr_init)
    paramr = result.minimum
    cur_err = result.f_minimum

    if cur_err < best_err
      best_err = cur_err
      paramb_best = paramb
      paramr_best = paramr
    end
  end
  print("best error ", best_err, " ")
  paramb_best, paramr_best
end

function learn_weight(w_err_fun)
  bestw = 0.0
  best_err = Inf
  for i in 1:1
    w_init = rand()
    try
      result = optimize(vect->w_err_fun(vect), [w_init], method = :l_bfgs)
      w = result.minimum[1]
      cur_err = result.f_minimum
      if cur_err < best_err
        bestw = w
      end
    catch
      println("crash weight")
    end
  end
  bestw
end

function train_boosting(f, paramb_n, paramr_range, data, n_boost)
  avg = sum([d[2] for d in data]) / length(data)
  boost = Boost(avg, Float64[], Function[])
  Fcurrent = x->beval(boost, x)
  for i in 1:n_boost
    println("iteration ", i)
    residual_data = get_neg_residual(Fcurrent, data)
    paramb, paramr = sample_weak_learner(get_h_sample_error_function(f, residual_data),paramb_n, paramr_range)
    @show(paramr)
    h = (x...)->f(x..., paramb, paramr)
    w = learn_weight(get_w_error_function(Fcurrent,h,data))
    @show(w)
    push!(boost.weights, w * 0.10)
    push!(boost.weaks, h)
    Fcurrent = (x)->beval(boost, x...)
  end
  boost
end
