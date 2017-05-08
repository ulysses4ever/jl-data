module intervalos
export Intervalo, subset, Cestricto, rad, mid, mig, mag, abs, d, pow


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


Intervalo() = println("Intervalo vacío")


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



end 










