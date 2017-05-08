module Derivadas
export FD

type FD
    f
    d
end


function FD(c)
    FD(c,0.0)
end

################# Aritmética ####################

# Sumas

function +(x::FD,y::FD)
    FD(x.f+y.f,x.d+y.d)
end

function +(x::Real,y::FD) # esto es lo del inciso iv de éste ejercicio
    FD(x+y.f,y.d)
end

function +(x::FD,y::Real) # esto es lo del inciso iv de éste ejercicio
    FD(x.f+y,x.d)
end

#Restas
function -(x::FD,y::FD)
    FD(x.f-y.f,x.d-y.d)
end

function -(x::Real,y::FD) # esto es lo del inciso iv de éste ejercicio
    FD(x-y.f,-y.d)
end

function -(x::FD,y::Real) # esto es lo del inciso iv de éste ejercicio
    FD(x.f-y,x.d)
end

#Multiplicaciones
function *(x::FD,y::FD)
    FD(x.f*y.f, x.f*y.d+y.f*x.d)
end

function *(x::Real,y::FD)
    FD(x*y.f, x*y.d)
end

function *(x::FD,y::Real)
    FD(x.f*y, x.d*y)
end

#Divisiones
function /(x::FD,y::Real)
    FD(x.f/y, x.d/y)
end

function /(x::FD,y::FD)
    FD(x.f/y.f, (y.f*x.d-x.f*y.d)/y.f^2)
end

#Potencia
function ^(x::FD,a::Integer)
    FD(x.f^a,a*x.f^(a-1)*x.d)
end

function ^(x::FD,a::FloatingPoint)
    FD(x.f^a,a*x.f^(a-1)*x.d)
end


end
