module Intervalos

export Intervalo, +,-,*,/, ==, ∈, ⊂, ^, UnionI, RUP, RDOWN ,exp, eva

type Intervalo
    a::BigFloat
    b::BigFloat

function Intervalo(x,y)
if y<x
a=y
b=x
else 
a=x
b=y
end
new(a,b)
end
end




type UnionI
p::Intervalo
s::Intervalo
end



function round!(i::Intervalo)
    set_rounding(BigFloat, RoundDown)
    i.a=BigFloat(i.a)
    set_rounding(BigFloat, RoundUp)
    i.b=BigFloat(i.b)
    i
end

#una constante o intervalo constante
function Intervalo(c)
    Intervalo(c,c)
end

###para realizar los redondeos de manera mas limpia

###funciones de un solo argumento, como exp, *, cos

function RUP(g::Function, x)  #redondeo hacia arriba
set_rounding(BigFloat, RoundUp)
g(x)
end


function RDOWN(g::Function, x) ##redonde hacia abajo
set_rounding(BigFloat, RoundDown)
g(x)
end

#para funciones que requieren dos argumentos como ^, log
function RUP(g::Function, x, y)  #redondeo hacia arriba
set_rounding(BigFloat, RoundUp)
g(x, y)
end


function RDOWN(g::Function, x, y) ##redonde hacia abajo
set_rounding(BigFloat, RoundDown)
g(x, y)
end
#funciones para usar con intervalos



##########################
##########################
######### SUMA  ##########
##########################
##########################


function +(x::Intervalo, y::Intervalo)
set_rounding(BigFloat, RoundDown)
d=x.a+y.a
set_rounding(BigFloat, RoundUp)
u=x.b+y.b

round!(Intervalo(d, u))
end

function +(x::Intervalo, y::Real)
 Intervalo(y)+x
end

function +(x::Real, y::Intervalo)
 Intervalo(x)+y
end



##########################
##########################
######### RESTA ##########
##########################
##########################

function -(x::Intervalo, y::Intervalo)
set_rounding(BigFloat, RoundDown)
d=x.a-y.a
set_rounding(BigFloat, RoundUp)
u=x.b-y.b
round!(Intervalo(d, u))
end

function -(x::Intervalo, y::Real)
 x-Intervalo(y)
end

function -(x::Real, y::Intervalo)
 Intervalo(x)-y
end



##########################
##########################
##### MULTIPLICACION #####
##########################
##########################


function *(x::Intervalo, y::Intervalo)
set_rounding(BigFloat, RoundDown)
d=min(x.a*y.b,x.b*y.a, x.a*y.a, x.b*y.b)
set_rounding(BigFloat, RoundUp)
u= max(x.a*y.b,x.b*y.a, x.a*y.a, x.b*y.b)
round!(Intervalo(d,u))    
end


function *(x::Intervalo, c::Real)
  Intervalo(c)*x
end




function *(c::Real, x::Intervalo)
   
   round!(Intervalo(c*x.a, c*x.b))
end


function *(x::Intervalo, u::UnionI)
UnionI(x*u.p, x*u.s)
end
##########################
##########################
######## DIVISION ########
##########################
##########################

function /(x::Intervalo, y::Intervalo)#la division se define en terminos de la multiplicacion y depende de si el intervalo divisor contiene al cero
if  ∈(0.0, y) == true
x*UnionI(Intervalo(-Inf,1/y.a ), Intervalo(1/y.b, Inf))
else
    Intervalo(x.a,x.b)*Intervalo(1/y.a, 1/y.b)
    
end
end

function /(x::Intervalo, y::Real)#la division se define en terminos de la multiplicacion
    Intervalo(x.a,x.b)*Intervalo(1/y)
    
end

function /(x::Real, y::Intervalo)#la division se define en terminos de la multiplicacion
   Intervalo(x)*Intervalo(1/y.a, 1/y.b)
    
end


##########################
##########################
####### POTENCIAS ########
##########################
##########################

function mig(x::Intervalo)
		if ∈(0.0, x) == true
			return 0
		else return min(abs(x.a), abs(x.b))
		end
	end

	mag(x::Intervalo) = max(abs(x.a), abs(x.b))

##meter condiciones de redondeo



function ^(x::Intervalo, n::Integer)
    
    if (x.a > 0 && x.b > 0)
        return Intervalo(x.a^n,x.b^n)
        
        elseif (x.b < 0 && x.a < 0)
            return Intervalo(x.b^n,x.a^n)
            else    
            return Intervalo(0,max(x.a^n,x.b^n))
    end
end 

function ^(x::Intervalo, n::Real)   #aqui no se puede utilizar directamente  eva porque la potencia requiere dos argumentos, la base y el exponente, tampoco puedo utilizar RDOWN y RUP por la misma razon
eva(^, x,n)
end

##########################
##########################
######## IGUALDAD ########
##########################
##########################



function ==(x::Intervalo, y::Intervalo)
    if x.a==y.a&&x.b==y.b
        true
    else 
        false
    end
end


function ==(x::UnionI, y::UnionI)
    if (x.s==y.s || x.s==y.p)&&(x.p==y.s || x.p==y.p)
        true
    else 
        false
    end
end

##########################
##########################
##### PERTENENCIA ########
######## DE UN ###########
######### PUNTO###########
##########################
##########################


function ∈(c::Real,x::Intervalo)
   if x.a<=c&&c<=x.b
       return true
   else
        return false
   end

end

function ∈(c::Real,x::UnionI)
   if ∈ (c,x.s) ==true|| ∈(c,x.p)==true
       return true
   else
        return false
   end

end

function ⊂(x::Intervalo, y::Intervalo)
	if y.a<x.a&&x.b<y.b
     	 true
 	elseif y.a==x.a&&x.b==y.b
	true
	else
	false
	end
end 

##########################
##########################
####### funciones ########
####### monotonas ########
##########################
##########################


###lo siguiente es para aplicar con funciones monótonas en general, sin embargo no es muy cómodo a la hora de usar.
function eva(f::Function, I::Intervalo)
e=f(I.a) 
c=f(I.b) # esta primera parte solo la realizo para ver cual es menor y cual es mayor y entonces proceder con el redondeo hacia arriba y hacia abajo como corresponde

if e<c  #ES CRECIENTE

Intervalo(RDOWN(f, I.a), RUP(f, I.b))

elseif c<e  #ES DECRECIENTE
Intervalo(RDOWN(f, I.b), RUP(f, I.a))

else  #IGUAL

Intervalo(RDOWN(f, I.b), RUP(f, I.a))

end

end

# eva para funciones de dos argumentos
function eva(f::Function, I::Intervalo, n)
e=f(I.a, n) 
c=f(I.b, n) # esta primera parte solo la realizo para ver cual es menor y cual es mayor y entonces proceder con el redondeo hacia arriba y hacia abajo como corresponde

if e<c  #ES CRECIENTE

Intervalo(RDOWN(f, I.a, n), RUP(f, I.b, n))

elseif c<e  #ES DECRECIENTE
Intervalo(RDOWN(f, I.b, n), RUP(f, I.a, n))

else  #IGUAL

Intervalo(RDOWN(f, I.b, n), RUP(f, I.a, n))

end

end


exp(x::Intervalo)=eva(exp, x)




####estaría muy bonito arreglar esto para que aparezca chido, buscar en #particulas de ejemplos
#import Base.show
#show(IO,Intervalo)
#show(io, x::Intervalo) = print(io, " [$x.a, $x.b])")

end###end del modulo






