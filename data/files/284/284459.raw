module Derivadas

import Base.exp
import Base.log
import Base.sin
import Base.cos
import Base.tan

export Derivada

## Crea el tipo derivada

type Derivada
    fun::Float64
    dif::Float64
    ddif::Float64
end


## Suma de Derivadas

function +(a::Derivada, b::Derivada)
    return Derivada( a.fun + b.fun, a.dif + b.dif, a.ddif + b.ddif )
end

## Resta de Derivadas

function -(a::Derivada, b::Derivada)
    return Derivada( a.fun - b.fun, a.dif - b.dif, a.ddif - b.ddif )
end


## Producto de Derivadas

function *(a::Derivada, b::Derivada)
    return Derivada( a.fun * b.fun, a.fun*b.dif + b.fun*a.dif, a.ddif*b.fun + 2*a.dif*b.dif + a.fun*b.ddif )
end

## Producto por constante

function *(c, x::Derivada)
	return Derivada(c*x.fun, c*x.dif, c*x.ddif)
end

## Constante por producto

function *(x::Derivada, c)
	return c*x
end

## Division de Derivadas

function /(a::Derivada, b::Derivada)
    return Derivada( a.fun/b.fun, 
    (a.dif*b.fun - a.fun*b.dif)/b.fun^2, 
    (a.ddif*b.fun - b.ddif*a.fun)/b.fun^2 - 2*(a.dif*b.fun - b.dif*a.fun)*b.dif/b.fun^3)
end

## Constante entre derivada

function /(c, x::Derivada)
	return Derivada(c/x.fun, -(c*x.dif)/x.fun^2, -c/x.fun^2*(x.ddif - 2*x.dif^2/x.fun))
end

## Derivada entre constante

function /(x::Derivada, c)
	return x*(1/c)
end

## Potencia de Derivadas

function ^(a::Derivada, p::Float64)
    return Derivada(a.fun^p, p*a.fun^(p-1)*a.dif, p*(p-1)*a.fun^(p-2)*a.diff)
end


## Suma mas constante

function +(c, x::Derivada)
    return Derivada(c + x.fun, x.dif, x.ddif )
end


function +(x::Derivada, c)
    return Derivada(c + x.fun, x.dif, x.ddif)
end

# Resta menos constante

function -(c, x::Derivada)
    return Derivada(c - x.fun, x.dif)
end


function -(x::Derivada, c)
    return Derivada(x.fun - c, x.dif)
end



## Producto por constante

function *(a, b::Derivada)
    return Derivada(a*b.fun, a*b.dif)
end

function *(b::Derivada, a)
    return Derivada(a*b.fun, a*b.dif)
end

#############################
### Funciones elementales ###
#############################

## exponencial

function exp(x::Derivada)
    return Derivada(exp(x.fun), exp(x.fun))
end


## logaritmo

function log(x::Derivada)
    return Derivada(log(x.fun), 1/x.fun)
end


## seno

function sin(a::Derivada)
    return Derivada(sin(a.fun), cos(a.fun), -sin(a.fun))
end


## coseno

function cos(a::Derivada)
    return Derivada(cos(a.fun), -sin(a.fun), -cos(a.fun))
end


## tangente

function tan(a::Derivada)
    return Derivada(tan(a.fun), sec(a.fun)^2)
end


end
