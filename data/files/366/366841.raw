using Images
using Gadfly
include("mcl.jl")

function format(A)
#  m = maximum(A)
#  B = 1 - (A / m)
  B = 1-A
  return B
end

a = 7
b = 3
n = a+b

e = 2
p = 100

G = mcl_sample_dumb(a,b,0.9,0.1)
range = 2:0.1:10
plot(x = range, y = map(x -> mcl_card(mcl(G,e,x,p)), range))

range = 0:10
plot(x = range, y = map(m -> mcl_prob_dumb(m,10-m,0.9,0.1,1000,2,3,100), range), Geom.point, Geom.smooth)
