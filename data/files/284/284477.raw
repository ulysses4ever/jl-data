# !\usr\bin\julia

## terminar la division correctamente
## verificar la union de intervalos

module Intervalos

import Base.in
import Base.intersect
import Base.union
import Base.isempty
import Base.abs
import Base.exp
import Base.log
import Base.sin
import Base.cos


####################################
### Defino el tipo 'Intervalo'   ###
####################################

## Esta instruccion hace que el tipo Intervalo este disponible para importarse en otro modulo

export Intervalo


type Intervalo
   	a
   	b
    function Intervalo(a,b)
        if a > b
            a, b = b, a
        end
    	set_rounding(BigFloat, RoundDown)
			ab = BigFloat("$a")
		set_rounding(BigFloat, RoundUp)
			bb = BigFloat("$b")
		set_rounding(BigFloat,RoundNearest)
		new(ab,bb)
    end
end


function Base.show(io::IO, A::Intervalo)
	if isnan(A.a) || isnan(A.b)
		#@printf(io, "[%0.3f, %0.3f]", A.a, A.b)
		@printf(io, "[empty]")
	else
		@printf(io, "[%f, %f]", A.a, A.b)
		#@printf(io, "[%0.3f, %0.3f]", A.a, A.b)
		#@printf(io, "[empty]")
	end
end




## NOTA
## La instruccion 'using' para modulos hace que las definiciones exportadas en el modulo se puedan utilizar como definiciones
## construidas en el Main y las que no se importaron se puedan utilizar como objetos de MyModule, e.g. MyModule.p funcion en
## vez de p(), y que p no se exporto en el modulo. Pero si yo uso 'import' para añadir este modulo al workspace, entonces todas
## las definiciones seran usadas como objetos del modulo, independientemente de si se exportaron o no en el modulo, es decir, 
## x() no funciona, pero MyModule.x si funciona.


## Para usar un modulo desde un archivo ##
## Primero incluyo el archivo con
## 		include("/home/rocko/Documentos/Posgrado/julia/intervalos.jl")
## Segundo, import el modulo con:
## 		import Intervalos


#########################################################
### Defino operaciones de conjuntos para intervalos   ###
#########################################################

## Defino la operacion 'isempty'

export isempty

function isempty(A::Intervalo)  # Verifica si el intervalo es vacio
	if isnan(A.a) || isnan(A.b)
		return true
	else
		return false
	end
end


## Defino la operacion 'in'

export in

function in(x, A::Intervalo)
	if isempty(A)
		return false
	end
    if A.a <= x <= A.b
        return true
    else
        return false
    end
end


### Subconjunto ###################################

function in(X::Intervalo, A::Intervalo)
	if isempty(X)
		return true
	end
	if (X.a in A) & (X.b in A)
		return true
	else
		return false
	end
end


## Defino la operacion 'intersect'

export intersect

function intersect(A::Intervalo, B::Intervalo)
	if isempty(A) || isempty(B)
		return Intervalo(NaN,NaN)
	end
    if (B.a in A) & ~(B.b in A)
        return Intervalo(B.a, A.b)
    elseif (B.b in A) & ~(B.a in A)
        return Intervalo(A.a, B.b)
    elseif (B.a in A) & (B.b in A)
        return B
    else
        if A.a in B
            return A
        else
            Intervalo(NaN,NaN)
        end
    end
end


## Defino la operacion 'union' de intervalos

export union

function union(A::Intervalo, B::Intervalo)
	if isempty(A)
		return B
	elseif isempty(B)
		return A
	end
    if ~(B.a in A) & (B.b in A)
        return Intervalo(B.a, A.b)
    elseif (B.a in A) & ~(B.b in A)
        return Intervalo(A.a, B.b)
    elseif (B.a in A) & (B.b in A)
        return A
    elseif A.a in B
        return B
    else
        if A.b < B.a
            return [A,B]
        else
            return [B,A]
        end
    end
end
       
       
## Defino el diametro de un intervalo

export long

function long(A::Intervalo)
    return A.b - A.a
end     

## Defino el punto medio de un intervalo

export mid

function mid(A::Intervalo)
    return (A.a + A.b)/2
end

## Defino el valor absoluto de un intervalo

export abs

function abs(X::Intervalo)
	return max(abs(X.a), abs(X.b))
end

export rad

function rad(X::Intervalo)
	return (1/2)*(X.b - X.a)
end



###########################################################
### Defino las operaciones aritmeticas para intervalos  ###
###########################################################


## Suma ###################################################

function +(A::Intervalo, B::Intervalo)
    return Intervalo(A.a + B.a, A.b + B.b)
end

## Suma mas constante

function +(J::Intervalo, c::Real)
	return Intervalo(J.a + c, J.b + c)
end

## Constante mas Intervalo

function +(c::Real, J::Intervalo)
	return Intervalo(J.a + c, J.b + c)
end


## Resta ##################################################

function -(A::Intervalo, B::Intervalo)
    return Intervalo(A.a - B.b, A.b - B.a)
end
 
## Resta menos constante

function -(J::Intervalo, c::Real)
	return Intervalo(J.a - c, J.b - c)
end

## Constante menos Intervalo

function -(c::Real, J::Intervalo)
	return Intervalo(c - J.a, c - J.b)
end


## Producto ###############################################

function *(A::Intervalo, B::Intervalo)
	if ((A.a,A.b) == (0,0)) & ((B.a,B.b) == (-Inf, Inf))   # [0,0] * [-Inf, Inf] == [0,0]
		return Intervalo(0,0)
	elseif (0 <= A.a) & (0 <= B.a)
		return Intervalo(A.a*B.a, A.b*B.b)
	elseif (A.a < 0 < A.b) & (0 <= B.a)
		return Intervalo(A.a*B.b, A.b*B.b)
	elseif (A.b <= 0) & (0 <= B.a)
		return Intervalo(A.a*B.b, A.b*B.a)
	elseif (0 <= A.a) & (B.a < 0 < B.b)
		return Intervalo(A.b*B.a, A.b*B.b)
	elseif (A.b <= 0) & (B.a < 0 < B.b)
		return Intervalo(A.a*B.b, A.a*B.a)
	elseif (0 <= A.a) & (B.b <= 0)
		return Intervalo(A.b*B.a, A.a*B.b)
	elseif (A.a < 0 < A.b) & (B.b <= 0)
		return Intervalo(A.b*B.a, A.a*B.a)
	elseif (A.b <= 0) & (B.b <= 0)
		return Intervalo(A.b*B.b, A.a*B.a)
	elseif (A.a < 0 < A.b) & (B.a < 0 < B.b)
		return Intervalo(min(A.a*B.b, A.b*B.a), max(A.a*B.a, A.b*B.b))
	elseif isempty(A) || isempty(B)
		return Intervalo(NaN, NaN)
	end
end


## Producto por constante

function *(J::Intervalo, c::Real)
	return Intervalo(J.a*c, J.b*c)
end

## Constante por Intervalo

function *(c::Real, J::Intervalo)
	return Intervalo(J.a*c, J.b*c)
end

## Intervalo negativo

function -(A::Intervalo)
	return (-1)*A
end



## Division ###############################################

## Reciproco de un intervalo: 1/[a,b]

function reciproco(A::Intervalo)
	if (A.a == 0) & (0 < A.b)
		return Intervalo(1/A.b, +Inf)
	elseif A.a < 0 < A.b
		return Intervalo(-Inf,Inf)  # El intervalo mas pequeno que contiene el resultado (union de intervalos disjuntos)
	elseif (A.a < 0) & (A.b == 0)
		return Intervalo(-Inf, 1/A.a)
	elseif (A.a == 0) & (A.b == 0)
		return Intervalo(NaN,NaN)  # Teorema 3 de Hickey
	else
		return Intervalo(1/A.b, 1/A.a)
	end
end

## Division de intervalos
# Verificar si es mejor la definicion por casos que da Hickey (en cuando a eficiencia)

function /(X::Intervalo, Y::Intervalo)
	#Teorema 8 (Hickey)
	if ((X.a, X.b) == (0,0)) & ((Y.a, Y.b) == (0,0))
		return Intervalo(NaN, NaN)
	elseif (0 in X) & ((Y.a, Y.b) == (0,0))
		return Intervalo(-Inf,Inf)
	elseif ~(0 in X) & ((Y.a, Y.b) == (0,0))
		return Intervalo(NaN,NaN)
	elseif ((X.a, X.b) == (0,0)) & (0 in Y)
		return Intervalo(-Inf,Inf)
	elseif  ((X.a, X.b) == (0,0)) & ~(0 in Y)
		return Intervalo(0,0)	
	#Teorema 7 de Ratz (Hickey)
	elseif ~(0 in Y)
		return X*reciproco(Y)
	elseif (0 in X) & (0 in Y)
		return Intervalo(-Inf,Inf)
	elseif (X.b < 0) & ((Y.a < 0) & (Y.b == 0))
		return Intervalo(X.b/Y.a, Inf)
	elseif (X.b < 0) & ((Y.a < 0) & (0 < Y.b))
		return Intervalo(-Inf, Inf)
	elseif (X.b < 0) & ((Y.a == 0) & (0 < Y.b))
		return Intervalo(-Inf, X.b/Y.b)
	elseif (0 < X.a) & ((Y.a < 0) & (Y.b == 0))
		return Intervalo(-Inf, X.a/Y.a)
	elseif (0 < X.a) & ((Y.a < 0) & (0 < Y.b))
		return Intervalo(-Inf, Inf)
	elseif (0 < X.a) & ((0 == Y.a) & (0 < Y.b))
		return Intervalo(X.a/Y.b, Inf)
	end
		
end

## Division entre constante

function /(J::Intervalo, c::Real)
	if c == 0
		error("División entre cero")
	else
		return Intervalo(J.a/c, J.b/c)
	end
end

## Constante entre Intervalo

function /(c::Real, J::Intervalo)
	return c*reciproco(J)
end


#########################################
### Defino funciones para intervalos  ###
#########################################


## Potencia

function ^(J::Intervalo, n::Integer)   # Solo para potencias enteras
    if (J.a > 0) || (J.b < 0)
        return Intervalo(min(J.a^n, J.b^n), max(J.a^n, J.b^n))
    else
        return Intervalo(min(0, J.a^n, J.b^n), max(0,J.a^n, J.b^n))
    end
end


function ^(J::Intervalo, p::Real)   # Para potencias reales
    if p == int(p)
        return J^int(p)
    else
        I = intersect(J,Intervalo(0,Inf))
        return Intervalo(I.a^p, I.b^p)
    end
end



## Defino la operacion 'exp(Intervalo)'

function exp(J::Intervalo)
    return Intervalo(exp(J.a), exp(J.b))
end


## Defino la operacion 'log(Intervalo)'

function log(J::Intervalo)
    if J.a < 0 || J.b < 0
        error("Conjunto no contenido en el dominio de la función")
    else
        return Intervalo(log(J.a), log(J.b))
    end
end


###################################################################
### Funciones no monotonas elementales extendidas a intervalos  ###
###################################################################

############
### Seno ###
############

## Define los puntos criticos de la funcion seno

function sin_cp(n)
	a = Int64[]
	for i = 1:length(n)
		if iseven(n[i])
			push!(a,1)
		else
			push!(a,-1)
		end
	end
	return a
end


## Defino la operacion 'sin(Intervalo)'

function sin(J::Intervalo)
	m = int(ceil(J.a/pi - 0.5))
	M = int(ceil(J.b/pi - 0.5))
	a = [sin(J.a), sin(J.b), sin_cp(m:M-1)]
	return Intervalo(minimum(a), maximum(a))
end

##############
### Coseno ###
##############

## Define los puntos criticos de la funcion cos

function cos_cp(n)
	a = Int64[]
	for i = 1:length(n)
		if iseven(n[i])
			push!(a,1)
		else
			push!(a,-1)
		end
	end
	return a
end


## Defino la operacion 'cos(Intervalo)'

function cos(J::Intervalo)
	m = int(ceil(J.a/pi))
	M = int(ceil(J.b/pi))
	a = [cos(J.a), cos(J.b), cos_cp(m:M-1)]
	return Intervalo(minimum(a), maximum(a))
end

end
