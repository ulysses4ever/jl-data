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

n = 10
T = 1000
p = 20
range = 0:n
plot(x = range, y = map(m -> mcl_prob_dumb(m,n-m,0.9,0.1,T,2,3,p), range), Geom.point, Geom.smooth)

n = 100
T = 40
p = 20
range = 0:n
plot(x = range, y = map(m -> mcl_prob_dumb(m,n-m,0.9,0.1,T,2,3,p), range), Geom.point, Geom.line)

n = 1000
T = 40
p = 20
range = 0:n
plot(x = range, y = map(m -> mcl_prob_dumb(m,n-m,0.9,0.1,T,2,3,100), range), ‘‘4Geom.point, Geom.line)
