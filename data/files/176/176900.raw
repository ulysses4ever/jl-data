include("/home/evan/Documents/research/3cobblers/simpleboost_v1.jl")

function x_coord(a::Float64, b::Float64, c::Float64, d::Float64, paramb::Array{Bool}, paramr::Array{Float64})
  wa,wb,wc,wd,wk, cond = paramr
  if (a < cond)
    return b*wb + c*wc + d*wd + wk
  end
  if (b < cond)
    return a*wa + c*wc + d*wd + wk
  end
  if (c < cond)
    return a*wa + b*wb + d*wd + wk
  end
  if (d < cond)
    return a*wa + b*wb + c*wc + wk
  end
  return a*wa + b*wb + c*wc + d*wd + wk
end

function euclid_dist(pt1, pt2)
  x_diff = pt2[1] - pt1[1]
  y_diff = pt2[2] - pt1[2]
  sqrt(x_diff^2 + y_diff^2)
end

function get_sensor_reading(x,y)
    a = euclid_dist((x,y), (1.0, 1.0))
    b = euclid_dist((x,y), (1.0, 2.0))
    c = euclid_dist((x,y), (2.0, 1.0))
    d = euclid_dist((x,y), (2.0, 2.0))
  a,b,c,d
end

function generate_data(n)
  retx = ((Float64,Float64,Float64,Float64),Float64)[]
  rety = ((Float64,Float64,Float64,Float64),Float64)[]
  for i in 1:n
    x = rand() * 3
    y = rand() * 3
      a,b,c,d = get_sensor_reading(x,y)
      push!(retx, ((a,b,c,d),x))
      push!(rety, ((a,b,c,d),y))
  end
  retx, rety
end

datax, datay = generate_data(200)

boox = train_boosting(x_coord, 0, [(0.0, 1.0) for i in 1:15], datax, 300)
booy = train_boosting(x_coord, 0, [(0.0, 1.0) for i in 1:15], datay, 300)

function get_recover_fun(bx, by)
  function recover(x,y)
    a,b,c,d = get_sensor_reading(x,y)
    predx = beval(bx, a, b, c, d)
    predy = beval(by, a, b, c, d)
    predx, predy
  end
end

recover_fun = get_recover_fun(boox, booy)
recover_fun(0.5, 0.5)
recover_fun(0.0, 0.0)
recover_fun(1.0, 1.0)
recover_fun(0.9, 0.2)

function get_err_map(recover_fun)
  function err_map(x,y)
    predx, predy = recover_fun(x,y)
    sqrt((x-predx)^2 + (y-predy)^2)
  end
end

err_map = get_err_map(recover_fun)

using Gadfly
plot(z=(x,y) -> err_map(x,y),
     x=linspace(0.0,3.0,100), y=linspace(0.0,3.0,100), Geom.contour)

