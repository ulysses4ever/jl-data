module Derivadas

import Base.exp
import Base.log
import Base.sqrt
import Base.sin
import Base.cos
import Base.tan

export Derivada

## Crea el tipo derivada

type Derivada
    fun #::Float64
    dif #::Float64
    ddif #::Float64
end

using Intervalos

function Derivada(X::Intervalo)
	return Derivada(X,Intervalo(1,1),Intervalo(0,0))
end

function ==(a::Derivada, b::Derivada)
	if (a.fun == b.fun) & (a.dif == b.dif) & (a.ddif == b.ddif)
		return true
	else
		return false
	end
end

### Suma ###################################################################

## Suma de Derivadas

function +(a::Derivada, b::Derivada)
    return Derivada( a.fun + b.fun, a.dif + b.dif, a.ddif + b.ddif )
end

## Suma mas constante

function +(c::Real, x::Derivada)
    return Derivada(c + x.fun, x.dif, x.ddif )
end

## Constante mas Derivada

function +(x::Derivada, c::Real)
    return Derivada(c + x.fun, x.dif, x.ddif)
end


### Resta ##################################################################

## Resta de Derivadas

function -(a::Derivada, b::Derivada)
    return Derivada( a.fun - b.fun, a.dif - b.dif, a.ddif - b.ddif )
end

# Resta menos constante

function -(c::Real, x::Derivada)
    return Derivada(c - x.fun, -x.dif, -x.ddif)
end

## Derivada menos constante

function -(x::Derivada, c::Real)
    return Derivada(x.fun - c, x.dif, x.ddif)
end

# Derivada negativa (por menos uno)

function -(x::Derivada)
	return (-1)*x
end


### Producto ###############################################################

## Producto de Derivadas

function *(a::Derivada, b::Derivada)
    return Derivada( a.fun * b.fun, a.fun*b.dif + b.fun*a.dif, a.ddif*b.fun + 2*a.dif*b.dif + a.fun*b.ddif )
end

## Producto por constante

function *(c::Real, x::Derivada)
	return Derivada(c*x.fun, c*x.dif, c*x.ddif)
end

## Constante por producto

function *(x::Derivada, c::Real)
	return Derivada(c*x.fun, c*x.dif, c*x.diff)
end

### Division ##############################################################

## Division de Derivadas

function /(a::Derivada, b::Derivada)
    return Derivada( a.fun/b.fun, (a.dif*b.fun - a.fun*b.dif)/b.fun^2, (a.ddif*b.fun - b.ddif*a.fun)/b.fun^2 - 2*(a.dif*b.fun - b.dif*a.fun)*b.dif/b.fun^3 )
end

## Constante entre derivada

function /(c::Real, x::Derivada)
	return Derivada(c/x.fun, -(c*x.dif)/x.fun^2, -c/x.fun^2*(x.ddif - 2*x.dif^2/x.fun))
end

## Derivada entre constante

function /(x::Derivada, c::Real)
	return Derivada(x.fun/c, x.dif/c, x.ddif/c)
end

### Potencia ##############################################################

## Potencia entera de Derivadas

function ^(a::Derivada, p::Integer)
    return Derivada(a.fun^p, p*a.fun^(p-1)*a.dif, p*a.fun^(p-2)*(a.dif^2*(p-1) + a.fun*a.ddif))
end

## Potencia real de Derivadas 

function ^(a::Derivada, p::Real)
    return Derivada(a.fun^p, p*a.fun^(p-1)*a.dif, p*a.fun^(p-2)*(a.dif^2*(p-1) + a.fun*a.ddif))
end


#############################
### Funciones elementales ###
#############################

## exponencial

function exp(x::Derivada)
    return Derivada(exp(x.fun), x.dif*exp(x.fun), x.ddif*exp(x.fun) + (x.dif)^2*exp(x.fun))
end


## logaritmo

function log(x::Derivada)
    return Derivada(log(x.fun), x.dif/x.fun, (x.fun*x.ddif - x.dif^2)/x.fun^2)
end

## Raiz cuadrada

function sqrt(x::Derivada)
	return Derivada(sqrt(x.fun), x.dif/(2*sqrt(x.fun)), x.ddif/(2*sqrt(x.fun)) - x.dif^2/(4*x.fun^(3/2)))
end


## seno

function sin(a::Derivada)
    return Derivada(sin(a.fun), a.dif*cos(a.fun), a.ddif*cos(a.fun) - a.dif^2*sin(a.fun))
end


## coseno

function cos(a::Derivada)
    return Derivada(cos(a.fun), -a.dif*sin(a.fun), -a.ddif*sin(a.fun) - a.dif^2*cos(a.fun))
end


## tangente

function tan(a::Derivada)
    return Derivada(tan(a.fun), a.dif*sec(a.fun)^2, a.ddif*sec(a.fun)^2 + 2*a.dif^2*tan(a.fun)*sec(a.fun)^2)
end


end
