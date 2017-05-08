module intervalos
export Intervalo, subset, Cestricto, rad, mid, mig, mag, abs, d, pow, segmentar, caja, inter, plot, npaso1, recorrer, npaso2, npaso3


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

#funciones para el programa de integración
using PyPlot

function caja(X::Intervalo, Y::Intervalo, c::ASCIIString )
    X1=float64(X.inf)
    X2=float64(X.sup)
    Y1=float64(Y.inf)
    Y2=float64(Y.sup)
    
    plot([X1,X2],[Y1,Y1], color= c)
    plot([X1,X2],[Y2,Y2], color= c)
    plot([X1,X1], [Y1,Y2], color = c)
    plot([X2, X2], [Y1,Y2], color = c)
end

function inter(X::Intervalo)
    return [float64(X.inf),float64(X.sup)]
end

function recorrer(f::Function,a)
       g(x)=f(x+a)
end

#función para dar pasos INICIA
############################################3
function npaso1(F::Function, f::Function, Z0::Intervalo, x0::Float64, dt::Float64, N::Int, M::Int, asup::Float64)
    X0=Float64[]
    T=Intervalo[]
    Z=Intervalo[]
    AA=Intervalo[]
    k=-1
    for j in 1:N
        ZZ=Intervalo[]

        if (j ==1)
            push!(X0,x0)
            push!(ZZ,Z0)
            push!(T,Intervalo(0,dt))
            for i in 2:M
                Zi=X0[j] + T[j]*F(ZZ[i-1])
                push!(ZZ,Zi)
            end
            push!(Z,ZZ[M])
            BB=X0[j] + dt*F(Z[j])
            push!(AA,BB)
        end

        if (j==2)
            push!(X0,float64(AA[j-1].sup))
            push!(ZZ,AA[j-1])
            push!(T,Intervalo((j-1)*dt,j*dt))
            for i in 2:M
                Zi=X0[j]+ T[j]*F(ZZ[i-1])
                push!(ZZ,Zi)
            end
            push!(Z,ZZ[M])
            BB=X0[j]+dt*F(Z[j])
            push!(AA,BB)

            ZZ=Intervalo[]
            push!(X0,float64(AA[j-1].inf))
            push!(ZZ,AA[j-1])
            for i in 2:M
                Zi=X0[j+1]+ T[j]*F(ZZ[i-1])
                push!(ZZ,Zi)
            end
            push!(Z,ZZ[M])
            BB=X0[j+1] + dt*F(Z[j+1])
            push!(AA,BB)
        end

        if (j>2)
            k+=1
            push!(X0,float64(AA[j-1+k].sup))
            push!(ZZ, Intervalo(AA[j-1+k].sup,AA[j+k].inf))
            push!(T,Intervalo((j-1)*dt,j*dt))
            for i in 2:M
                Zi= X0[j+1+k] + T[j]*F(ZZ[i-1])
                push!(ZZ,Zi)
            end
            push!(Z,ZZ[M])
            BB=X0[j+1+k]+dt*F(ZZ[M])
            push!(AA,BB)

            ZZ=Intervalo[]
            push!(X0,float64(AA[j+k].inf))
            push!(ZZ, Intervalo(AA[j-1+k].sup,AA[j+k].inf))
            for i in 2:M
                Zi=X0[j+2+k]+T[j]*F(ZZ[i-1])
                push!(ZZ,Zi)
            end
            push!(Z,ZZ[M])
            BB=X0[j+2+k]+dt*F(ZZ[M])
            push!(AA,BB)
        end
    end

    ainf=0
    #asup=float64(T[N].sup)
    a = (ainf:0.0125:asup)
    b = Float64[]
    for i in 1:length(a)
        push!(b,f(a[i]))
    end

    #GRÁFICA FUNCIÓN
    plot (a,b)


    k=-1
    for i in 1:N
        if (i==1)
            plot(inter(T[i]), [X0[i],float64(AA[i].sup)], "red")
            plot(inter(T[i]),[X0[i],float64(AA[i].inf)], "green")
        else
        k+=1
            plot(inter(T[i]), [X0[i+k],float64(AA[i+k].sup)], "red")
            plot(inter(T[i]),[X0[i+1+k],float64(AA[i+1+k].inf)], "green")
        end
    end
    
end # function
#FUNCIÓN PARA DAR PASO TERMINA
#######################################

#FUNCION PASO DOS INICIO

function npaso2(F::Function, f::Function, Z0::Intervalo, x0::Float64, dt::Float64, N::Int, M::Int, asup::Float64)

X0=Float64[]
T=Intervalo[]
Z=Intervalo[]
AA=Intervalo[]
k=-1
TT=Intervalo(0,dt)

#N=10
#M=8

for j in 1:N
    ZZ=Intervalo[]
    
    if (j ==1)
        push!(X0,x0)
        push!(ZZ,Z0)
        push!(T,Intervalo(0,dt))
        for i in 2:M
                Zi=X0[j] + TT*recorrer(F,0)((ZZ[i-1]))
            push!(ZZ,Zi)
        end
        push!(Z,ZZ[M])
        BB=X0[j] + dt*recorrer(F,0)((Z[j]))
        push!(AA,BB)
    end
    
    if (j==2)
        push!(X0,float64(AA[j-1].sup))
        push!(ZZ,AA[j-1])
        push!(T,Intervalo((j-1)*dt,j*dt))
        for i in 2:M
            Zi=X0[j]+ TT*recorrer(F,(j-1)*dt)(ZZ[i-1])
            push!(ZZ,Zi)
        end
        push!(Z,ZZ[M])
        BB=X0[j]+dt*recorrer(F,(j-1)*dt)(Z[j])
        push!(AA,BB)
        
        ZZ=Intervalo[]
        push!(X0,float64(AA[j-1].inf))
        push!(ZZ,AA[j-1])
        for i in 2:M
            Zi=X0[j+1]+ TT*recorrer(F,(j-1)*dt)(ZZ[i-1])
            push!(ZZ,Zi)
        end
        push!(Z,ZZ[M])
        BB=X0[j+1] + dt*recorrer(F,(j-1)*dt)(Z[j+1])
        push!(AA,BB)
    end
    
    if (j>2)
        k+=1
        push!(X0,float64(AA[j-1+k].sup))
        push!(ZZ, Intervalo(AA[j-1+k].sup,AA[j+k].inf))
        push!(T,Intervalo((j-1)*dt,j*dt))
        for i in 2:M
            Zi= X0[j+1+k] + TT*recorrer(F,(j-1)*dt)(ZZ[i-1])
            push!(ZZ,Zi)
        end
        push!(Z,ZZ[M])
        BB=X0[j+1+k]+dt*recorrer(F,(j-1)*dt)(ZZ[M])
        push!(AA,BB)
        
        ZZ=Intervalo[]
        push!(X0,float64(AA[j+k].inf))
        push!(ZZ, Intervalo(AA[j-1+k].sup,AA[j+k].inf))
        for i in 2:M
            Zi=X0[j+2+k]+TT*recorrer(F,(j-1)*dt)(ZZ[i-1])
            push!(ZZ,Zi)
        end
        push!(Z,ZZ[M])
        BB=X0[j+2+k]+dt*recorrer(F,(j-1)*dt)(ZZ[M])
        push!(AA,BB)
    end
end
    
    ainf=0
#asup=7
a = (ainf:0.0125:asup)
b = Float64[]
for i in 1:length(a)
    push!(b,f(a[i]))
end

#GRÁFICA FUNCIÓN
plot (a,b)


k=-1
for i in 1:N
    if (i==1)
       plot(inter(T[i]), [X0[i],float64(AA[i].sup)], "red")
        plot(inter(T[i]),[X0[i],float64(AA[i].inf)], "green")
    else
    k+=1
        plot(inter(T[i]), [X0[i+k],float64(AA[i+k].sup)], "red")
        plot(inter(T[i]),[X0[i+1+k],float64(AA[i+1+k].inf)], "green")
    end
end

end #function
#FUNCION PASO DOS FIN
#######################################3
#FUNCIÓN PASO TRES INICIO

function npaso3(F::Function, f::Function, Z0::Intervalo, x0::Float64, dt::Float64, l::Float64, N::Int, M::Int, asup::Float64)
    X0=Float64[]
    T=Intervalo[]
    Z=Intervalo[]
    AA=Intervalo[]
    k=-1
    for j in 1:N
        ZZ=Intervalo[]

        if (j ==1)
            push!(X0,x0)
            push!(ZZ,Z0)
            push!(T,Intervalo(0,dt))
            for i in 2:M
                Zi=X0[j] + T[j]*F(ZZ[i-1])
                push!(ZZ,Zi)
            end
            push!(Z,ZZ[M])
            BB=X0[j] + dt*F(Z[j])
            push!(AA,BB)
        end

        if (j==2)
            push!(X0,float64(AA[j-1].sup))
            push!(ZZ,AA[j-1])
            push!(T,Intervalo(dt,dt+dt/l))
            for i in 2:M
                Zi=X0[j]+ T[j]*F(ZZ[i-1])
                push!(ZZ,Zi)
            end
            push!(Z,ZZ[M])
            BB=X0[j]+dt*F(Z[j])
            push!(AA,BB)

            ZZ=Intervalo[]
            push!(X0,float64(AA[j-1].inf))
            push!(ZZ,AA[j-1])
            for i in 2:M
                Zi=X0[j+1]+ T[j]*F(ZZ[i-1])
                push!(ZZ,Zi)
            end
            push!(Z,ZZ[M])
            BB=X0[j+1] + dt*F(Z[j+1])
            push!(AA,BB)
        end

        if (j>2)
            k+=1
            push!(X0,float64(AA[j-1+k].sup))
            push!(ZZ, Intervalo(AA[j-1+k].sup,AA[j+k].inf))
            
            dt1=0.0
            for p in 1:j-1
                dt1+= dt/(l^(p-1))
            end
            
            dt2=0.0
            for p in 1:j
                dt2+= dt/(l^(p-1))
            end
            
            push!(T,Intervalo(dt1,dt2))
            for i in 2:M
                Zi= X0[j+1+k] + T[j]*F(ZZ[i-1])
                push!(ZZ,Zi)
            end
            push!(Z,ZZ[M])
            BB=X0[j+1+k]+dt*F(ZZ[M])
            push!(AA,BB)

            ZZ=Intervalo[]
            push!(X0,float64(AA[j+k].inf))
            push!(ZZ, Intervalo(AA[j-1+k].sup,AA[j+k].inf))
            for i in 2:M
                Zi=X0[j+2+k]+T[j]*F(ZZ[i-1])
                push!(ZZ,Zi)
            end
            push!(Z,ZZ[M])
            BB=X0[j+2+k]+dt*F(ZZ[M])
            push!(AA,BB)
        end
    end

    ainf=0
   # asup=float64(T[N].sup)+1
    a = (ainf:0.0125:asup)
    b = Float64[]
    for i in 1:length(a)
        push!(b,f(a[i]))
    end

    #GRÁFICA FUNCIÓN
    plot (a,b)


    k=-1
    for i in 1:N
        if (i==1)
            plot(inter(T[i]), [X0[i],float64(AA[i].sup)], "red")
            plot(inter(T[i]),[X0[i],float64(AA[i].inf)], "green")
        else
        k+=1
            plot(inter(T[i]), [X0[i+k],float64(AA[i+k].sup)], "red")
            plot(inter(T[i]),[X0[i+1+k],float64(AA[i+1+k].inf)], "green")
        end
    end
    
end # function
#FUNCIÓN TRES FIN
######################################3

end #modulo










