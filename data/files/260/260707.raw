module Derivadasa

import Base.exp
import Base.log
import Base.cos
import Base.sin

export fdev, +,-,*,/, ^, exp, log, sin, cos, tan,==

type fdev
    f
    d
end

function (c)
    fdev(c,0.0)
end




function +(a::fdev, b::fdev) #suma de dos intervalos
fdev(a.f+b.f,a.d+b.d)
end

function +(a::fdev, b::Real) #suma de un intervalo y  una constante
    fdev(a.f+b,a.d)
end

function +(b::Real, a::fdev) #suma de una constante y un intervalo
fdev(a.f+b,a.d)
end


function -(a::fdev, b::fdev) #suma de dos intervalos
    fdev(a.f-b.f,a.d-b.d)
end

function -(a::fdev, b::Real) #suma de un intervalo y  una constante
fdev(a.f-b,a.d)
end

function -(b::Real, a::fdev)
fdev(a.f-b,a.d)
end

function *(a::fdev, b::fdev) #multiplicaciones
    fdev(a.f*b.f, a.f*b.d+a.d*b.f)
end

function *(a::fdev, b::Real) #suma de un intervalo y  una constante
    fdev(a.f*b,a.d*b)
end

function *(b::Real, a::fdev)
fdev(a.f*b,a.d*b)
end

function /(a::fdev, b::fdev)  #division
    fdev(a.f/b.f, (a.f*b.d-b.f*a.d)/b.d^2 )
end

function /(a::fdev, b::Real) #suma de un intervalo y  una constante
    fdev(a.f/b,a.d/b)
end

function /(b::Real, a::fdev)
fdev(a.f/b,a.d/b)
end

function ^(a::fdev, c::Integer)
    fdev(a.f^c, (c)*a.f^(c-1)*a.d)
end

function exp(a::fdev)
  fdev(exp(a.f), exp(a.f)*a.d)
end

function log(a::fdev)
    fdev(log(a.f), 1/(a.f)*a.d)
end

function cos(a::fdev)
    fdev(cos(a.f), -sen(a.f)*a.d)
end

function sin(a::fdev)
    fdev(sen(a.f), cos(a.f)*a.d)

end


function tan(a::fdev)
    fdev(tan(a.f), sec^2(a.f)*a.d)

end

function ==(x::fdev, y::fdev)
if x.d==y.d && x.f==y.f
return true
else
return false

end
end

end  #end del module
