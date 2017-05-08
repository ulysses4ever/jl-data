module Complejos

export IntC, +,-,*,/,^,conjg, norm

type IntC
R
I
end



+(a::IntC, b::IntC)=IntC(a.R+b.R, a.I+b.I)


-(a::IntC, b::IntC)=IntC(a.R-b.R, a.I-b.I)


*(a::IntC, b::IntC)=IntC(a.R*b.R-a.I*b.I, a.I*b.R+a.R*b.I)


conjg(a::IntC)=IntC(a.R, a.I*-1)

norm(a::IntC)=a.R^2+a.I^2

#la exponencial imaginaria

expi(t)=IntC(cos(t), sen(t))

/(z::IntC,d)=IntC(z.R/d,z.I /d)


function  /(a::IntC, b::IntC)
a*conjg(b)/norm(b)
end


end


