include ("TR_and_SR/SR.jl")

function SRinf_well (f,a,b,n)

  x(t)=1/t
  g(t)=f(x(t))/t^2

  approx=SR(g,1/b,1/a,n)
  return approx
end
