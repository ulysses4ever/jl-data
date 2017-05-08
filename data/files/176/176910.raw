include("/home/evan/Documents/research/3cobblers/simpleboost_v1.jl")

function line1(x::Float64, y::Float64, paramb::Array{Bool}, paramr::Array{Float64})
  a, b, c = paramr
  switch = paramb[1]

  if switch
    sign((a*x + b*y) - c)
  else
    sign(c - (a*x + b*y))
  end
end

function circle1(x::Float64, y::Float64, paramb::Array{Bool}, paramr::Array{Float64})
  xc, yc, r = paramr
  switch = paramb[1]
  if switch
    sign((x-xc)^2+(y-yc)^2 - r^2)
  else
    sign(r^2 - ((x-xc)^2 + (y-yc)^2))
  end
end

function generate_data(n, predictor)
  ret = ((Float64,Float64),Float64)[]
  for i in 1:n
    x = rand()
    y = rand()
    out = ( if predictor(x,y)
              1.0
           else
             -1.0
           end
           )
    push!(ret, ((x,y),out))
  end
  ret
end

predictor1(x,y) = (x<0.3) | (x>0.7)
predictor2(x,y) = ( (x-0.6)^2 + (y-0.6)^2 ) < 0.2^2
predictor3(x,y) = (0.3<x<0.7) & (0.3<y<0.7)
predictor4(x,y) = ( (x-0.2)^2 + (y-0.2)^2 ) < 0.2^2
predictor5(x,y) = predictor2(x,y) | predictor4(x,y)

d = generate_data(200, predictor2)
b1 = train_boosting(circle1, 1, [(0.0, 1.0) for i in 1:3], d, 100)

decision_fun(x,y) = (if beval(b1, x,y)>0.0
                       1.0
                     else
                       -1.0
                     end
                     )

decision_fun(x,y) = beval(b1, x, y)
decision_fun(x,y) = b1.weaks[5](x,y)

decision_fun(0.6, 0.6)
decision_fun(0.2, 0.5)

using Gadfly
plot(z=(x,y) -> decision_fun(x,y),
     x=linspace(0.0,1.0,100), y=linspace(0.0,1.0,100), Geom.contour)

