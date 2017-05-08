module derivadas

import Base.exp
import Base.log
import Base.cos
import Base.sin

export inter, +,-,*,/, ^, exp, log, sin, cos, tan
type inter
    f
    d
end

function inter(c)
    inter(c,0.0)
end

function +(a::inter, b::inter) #suma de dos intervalos
    inter(a.f+b.f,a.d+b.d)
end

function +(a::inter, b::Real) #suma de un intervalo y  una constante
    inter(a.f+b,a.d)
end

function +(b::Real, a::inter) #suma de una constante y un intervalo
  inter(a.f+b,a.d)
end


function -(a::inter, b::inter) #suma de dos intervalos
    inter(a.f-b.f,a.d-b.d)
end

function -(a::inter, b::Real) #suma de un intervalo y  una constante
    inter(a.f-b,a.d)
end

function -(b::Real, a::inter)
inter(a.f-b,a.d)
end

function *(a::inter, b::inter) #multiplicaciones
    inter(a.f*b.f, a.f*b.d+a.d*b.f)
end

function *(a::inter, b::Real) #suma de un intervalo y  una constante
    inter(a.f*b,a.d*b)
end

function *(b::Real, a::inter)
inter(a.f*b,a.d*b)
end

function /(a::inter, b::inter)  #division
    inter(a.f/b.f, (a.f*b.d-b.f*a.d)/b.d^2 )
end

function /(a::inter, b::Real) #suma de un intervalo y  una constante
    inter(a.f/b,a.d/b)
end

function /(b::Real, a::inter)
inter(a.f/b,a.d/b)
end

function ^(a::inter, c::Integer)
    inter(a.f^c, (c)*a.f^(c-1)*a.d)
end

function exp(a::inter)
inter(exp(a.f), exp(a.f)*a.d)
end

function log(a::inter)
    inter(log(a.f), 1/(a.f)*a.d)
end

function cos(a::inter)
    inter(cos(a.f), -sen(a.f)*a.d)
end

function sin(a::inter)
    inter(sen(a.f), cos(a.f)*a.d)

end


function tan(a::inter)
    inter(tan(a.f), sec^2(a.f)*a.d)

end

end