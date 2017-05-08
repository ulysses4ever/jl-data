function get_predictor(op, c)
  function pred(x)
    if op(x,c)
      1.0
    else
      -1.0
    end
  end
  pred
end

function get_err(pred, D)
  ret = 0.0
  for d in keys(D)
    x,y = d
    if pred(x) != y
      ret += D[d]
    end
  end
  ret
end

function give_best_pred(all_preds, D)
  best_pred, best_err = None, Inf
  for pred in all_preds
    err = get_err(pred, D)
    if err < best_err
      best_pred = pred
      best_err = err
    end
  end
  best_pred
end

function gen_data()
  D = Dict{(Float64, Float64), Float64}()
  for i in 1:200
    pt = rand() * 6 - 2.0
    if (1.0 < pt < 1.5) | (2.0 < pt < 2.5)
      D[(pt, 1.0)] = 1.0
    else
      D[(pt, -1.0)] = 1.0
    end
  end
  D
end

function gen_preds()
  preds = Function[]
  for c in linspace(-2.0, 4.0, 500)
    push!(preds, get_predictor(<, c))
    push!(preds, get_predictor(>, c))
  end
  preds
end

function get_errm(pred, D)
  Tweight = 0.0
  Eweight = 0.0
  for d in keys(D)
    x, y = d
    if pred(x) != y
      Eweight += D[d]
    end
    Tweight += D[d]
  end
  Eweight / Tweight
end

function change_weight!(pred, errm, D)
  for d in keys(D)
    x, y = d
    if pred(x) != y
      D[d] = D[d] * ((1 - errm) / errm)
    end
  end
end

D = gen_data()
P = gen_preds()

function learn_asmbl(P, D, n)
  preds = Function[]
  errms = Float64[]
  for i in 1:n
    p = give_best_pred(P, D)
    errm = get_errm(p, D)
    change_weight!(p, errm, D)
    push!(preds, p)
    push!(errms, errm)
  end
  function asmbl_pred(x)
    ret = 0.0
    for i in 1:length(preds)
      ret += preds[i](x) * log((1-errms[i])/errms[i])
    end
    if ret > 0.0
      1.0
    else
      -1.0
    end
  end
  asmbl_pred
end

outfun = learn_asmbl(preds, D, 11)

using Gadfly

plot(x->outfun(x), -2.0, 4.0)

