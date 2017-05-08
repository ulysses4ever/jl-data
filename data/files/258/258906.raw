module intervalos
export Intervalo, subset, Cestricto, rad, mid, mig, mag, abs, d, pow, segmentar


type Intervalo
	inf::Real
    	sup::Real
    function Intervalo(inf,sup)
        set_rounding(BigFloat,RoundDown)
        x=BigFloat("$(inf)")
        set_rounding(BigFloat,RoundUp)
        y=BigFloat("$(sup)")
        set_rounding(BigFloat,RoundNearest)
        if inf>sup 
            new(y,x)
        else
            new(x,y)
        end
    end
end

Intervalo(x::Real) = Intervalo(x,x)


Intervalo() = false

# Aritmética

function +(A::Intervalo,B::Intervalo)
	set_rounding(BigFloat,RoundDown)
    x= A.inf+B.inf
    set_rounding(BigFloat,RoundUp)
    y=A.sup+B.sup
    set_rounding(BigFloat,RoundNearest)
    Intervalo(x,y)
end

+(x::Intervalo, y::Real) = x + Intervalo(y)

+(x::Real, y::Intervalo) = Intervalo(x) + y

function -(A::Intervalo,B::Intervalo)
	set_rounding(BigFloat,RoundDown)
    x= A.inf-B.sup
    set_rounding(BigFloat,RoundUp)
    y=A.sup-B.inf
    set_rounding(BigFloat,RoundNearest)
    Intervalo(x,y)
end

-(x::Intervalo, y::Real) = x - Intervalo(y)

-(x::Real, y::Intervalo) = Intervalo(x) - y

function *(A::Intervalo,B::Intervalo)
	set_rounding(BigFloat,RoundDown)
    x=min(A.inf*B.inf,A.inf*B.sup,A.sup*B.inf,A.sup*B.sup)
    set_rounding(BigFloat,RoundUp)
    y=max(A.inf*B.inf,A.inf*B.sup,A.sup*B.inf,A.sup*B.sup)
    set_rounding(BigFloat,RoundNearest)
    Intervalo(x,y)
end

*(x::Intervalo, y::Real) = x*Intervalo(y)

*(x::Real, y::Intervalo) = Intervalo(x)*y

# FUNCION ZERO PARA MULTIPLICAR MATRICES
import Base.zero
function zero(I::Intervalo)
	return Intervalo(0) 
end

zero(::Type{Intervalo}) = Intervalo(0)
zero(::Type{Any}) = Intervalo(0)

# Booleano

function ==(A::Intervalo,B::Intervalo)
	if A.inf==B.inf && A.sup==B.sup
       true
    else
       false
    end
end

import Base.in

function in(x::Real,A::Intervalo)
	set_rounding(BigFloat,RoundUp)
    x1=BigFloat("$x")
    set_rounding(BigFloat,RoundDown)
    x2=BigFloat("$x")
    set_rounding(BigFloat,RoundNearest)
    if A.inf<=x1 && x2<=A.sup
       true
    else
       false
    end
end

# División extendida

function /(A::Intervalo, B::Intervalo)
	if 0 in B == false
       return A*Intervalo(1/(B.sup),1/(B.inf))
    end
    if (0 in A && 0 in B)
       return Intervalo(-Inf, Inf)
    end
    if (A.sup < 0 && B.inf < B.sup == 0)
       return Intervalo(A.sup/B.inf, Inf)
    end
    if (A.sup < 0 && B.inf < 0 < B.sup)
       return Intervalo(A.sup/B.inf, A.sup/B.sup)
    end
    if (A.sup < 0 && 0 == B.inf < B.sup)
       return Intervalo(-Inf, A.sup/B.sup)
    end
    if (0< A.inf && B.inf < B.sup==0)
       return Intervalo(-Inf, A.inf/B.inf)
    end
    if (0 < A.inf && B.inf < 0 < B.sup)
       return Intervalo(A.inf/B.sup, A.inf/B.inf)
    end
    if (0 < A.inf && 0 == B.inf < B.sup)
       return Intervalo(A.inf/B.sup, Inf)
    end
    if ( 0 in A == false && B == Intervalo(0,0))
       return Intervalo()
    end
end

/(A::Intervalo, r::Number) = A/Intervalo(r,r)
/(r::Number, A::Intervalo) = Intervalo(r,r)/A

#Operaciones de conjuntos  

function ⊆(A::Intervalo, B::Intervalo)
	if ((B.inf<= A.inf) && (A.sup<=B.sup))
       true
    else
       false
    end
end

function subset(A::Intervalo, B::Intervalo)
	if ((A ⊆ B) && ((A==B) == false)) 
	    true
	else
		false
    end
end



function Cestricto(A::Intervalo, B::Intervalo)
	if ((B.inf<A.inf) && (A.sup<B.sup))
       true
    else
       false
    end
end


function ∩(A::Intervalo, B::Intervalo)
	if (A.sup < B.inf || B.sup < A.inf)
		return Intervalo()
	else
		return Intervalo(max(A.inf,B.inf),min(A.sup,B.sup))
	end
end

rad(A::Intervalo) = 0.5*(A.sup - A.inf)

mid(A::Intervalo) = 0.5*(A.sup + A.inf)

# Segmentación de intervalos

function segmentar(A::Intervalo,n::Int)
	Iseg=Intervalo[]
    b = (A.sup-A.inf)/(n)
    for i in 1:n-1
	set_rounding(BigFloat,RoundDown)
	A1=A.inf + b*(i-1)
	set_rounding(BigFloat,RoundUp)
	A2=A.inf+b*i
	set_rounding(BigFloat,RoundNearest)
       push!(Iseg,Intervalo(A1,A2))
    end
	set_rounding(BigFloat,RoundDown)
	A1=A.inf+b*(n-1)
	set_rounding(BigFloat,RoundUp)
	A2=A.sup
	set_rounding(BigFloat,RoundNearest)
    push!(Iseg,Intervalo(A1,A2))
    return Iseg
end

# Propiedades del intervalo 

function mig(A::Intervalo)
	if (0 in A)
		return 0
	else
		return min((A.inf),abs(A.sup))
	end
end

mag(A::Intervalo) = max(abs(A.inf), abs(A.sup))

import Base.abs

function abs(A::Intervalo)
	return Intervalo(mig(A),mag(A))
end

function d(A::Intervalo,B::Intervalo)
	return max(abs(A.inf-B.inf),abs(A.sup-B.sup))
end

#Potencia

function ^(A::Intervalo, n::Int)
	if (n>0 && (mod(n,2)==1))
		return Intervalo(A.inf^n, A.sup^n)
	end
	
	if (n>0 && (mod(n,2)==0))
		return Intervalo(mig(A)^n, mag(A)^n)
	end

	if n==0
		return Intervalo(1,1)
	end

	if (n<0 && (0 in A == false))
		m=-n
		if (mod(m,2)==1)
			return Intervalo(1/(A.sup^m),1/(A.inf^m))
		end

		if (mod(m,2)==0) 
			return Intervalo((mig(Intervalo(1/A.sup,1/A.inf)))^m,(mag(Intervalo(1/A.sup,1/A.inf)))^m)
		end
	end

	if (n<0 && (0 in A))
		return error("No definido")
	end
end

pow(A::Intervalo,n::Int) = ^(A::Intervalo,n::Int)

# Exponencial 
import Base.exp

function exp(A::Intervalo)
set_rounding(BigFloat, RoundDown)
A1=exp(A.inf)
set_rounding(BigFloat, RoundUp)
A2= exp(A.sup)
Intervalo(A1,A2)
end

# Logaritmo
import Base.log

function log(A::Intervalo)
	if 0<= A.inf
		return Intervalo(log(A.inf),log(A.sup))
	else
	return error("Log no está definido para intervalos negativos")
	end
end

#Raiz cuadrada
import Base.sqrt

function sqrt(A::Intervalo)
  set_rounding(BigFloat, RoundDown)
  A1=sqrt(A.inf)
  set_rounding(BigFloat,RoundUp)
  A2=sqrt(A.sup)
  set_rounding(BigFloat,RoundNearest)
	if 0 <= A.inf
		return Intervalo(A1,A2)
	else
		return error("sqrt está definida para intervalos negativos")
	end
end

function ^(A::Intervalo, r::Float64)
	if A.inf<= 0
		return error("potencia no definida para intervalos negativos")
	else
		exp(r*log(A))
	end
end


#seno
function Smas(A::Intervalo)
	k1=int(floor((A.inf-π/2)/(2π)))
    k2=int(ceil((A.sup-π/2)/(2π)))
    S1=Float64[]
    for i in k1:k2
	    push!(S1,2π*i+π/2)
    end
    return S1
end

function Smenos(A::Intervalo)
	k1=int(floor((A.inf+π/2)/(2π)))
    k2=int(ceil((A.sup+π/2)/(2π)))
    S1=Float64[]
    for i in k1:k2
         push!(S1,2π*i-π/2)
    end
    return S1
end

function ∩(A::Intervalo, b::Array{Float64,1})
	k=0
    for i in 1:length(b)
	    if (b[i] in A)
		    k+=1
        end
    end
    return k
end

import Base.sin

function sin(A::Intervalo)
    if ((A ∩ Smenos(A)>0) && (A ∩ Smas(A) >0))
        return Intervalo(-1,1)
    end
    
    if ((A ∩ Smenos(A) >0) && (A ∩ Smas(A) ==0))
        set_rounding(BigFloat, RoundUp)
        A2=max(sin(A.inf),sin(A.sup))
        set_rounding(BigFloat, RoundNearest)
        return Intervalo(-1,A2)
    end
    
    if ((A ∩ Smenos(A) == 0) && (A ∩ Smas(A)>0))
        set_rounding(BigFloat, RoundDown)
        A1=min(sin(A.inf),sin(A.sup))
        set_rounding(BigFloat, RoundNearest)
        return Intervalo(A1,1)
    end 
    
    if ((A ∩ Smenos(A) == 0) && (A ∩ Smas(A)==0))
        set_rounding(BigFloat, RoundDown)
        A1=min(sin(A.inf),sin(A.sup))
        set_rounding(BigFloat, RoundUp)
        A2=max(sin(A.inf),sin(A.sup))
        set_rounding(BigFloat, RoundNearest)
        return Intervalo(A1,A2)
    end
end

#coseno

import Base.cos
cos(A::Intervalo)=sin(A+π/2)

#tangente

import Base.tan
tan(A::Intervalo)=sin(A)/(cos(A))


end #modulo










