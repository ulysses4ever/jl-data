module Intervalos



export Intervalo, +,-,*,/, ==, ∈, ⊂, ^

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

##########################
##########################
######## DIVISION ########
##########################
##########################

function /(x::Intervalo, y::Intervalo)#la division se define en terminos de la multiplicacion
    Intervalo(x.a,x.b)*Intervalo(1/y.a, 1/y.b)
    
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

#function mig(x::Intervalo)
#		if ∈(0.0, x) == true
#			return 0
#		else return min(abs(x.lo), abs(x.hi))
#		end
#	end
#
#	mag(x::Intervalo) = max(abs(x.a), abs(x.b))
#

#function ^(x::Intervalo, n::Integer)
#		if n > 0 && n % 2 == 1
#			return Intervalo(x.a^n, x.b^n)
#		elseif n > 0 && n % 2 == 0
#			return Interval((mig(x))^n, (mag(x))^n)
#		elseif n == 0
#			return Intervalo(1, 1)
##		elseif n < 0 && n ∈ (0, x) == false
#			return Intervalo(1/x.a, 1/x.b)^(-n)
#		# elseif return println("Error")
#		end
#	end
#function ^(x::Intervalo, y::Real)
 #   d= min(x.a^a, x2^a)
  #  u=max(x1^a, x2^a)

#Intervalo(d,u)
   
#end

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



##########################
##########################
##### PERTENENCIA ########
######## DE UN ###########
######### PUNTO###########
##########################
##########################


function ∈(c::Real,x::Intervalo)
   if x.a<=c&&c<=x.b
        true
   else
        false
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


####estaría muy bonito arreglar esto para que aparezca chido, buscar en particulas de ejemplos
#import Base.show
#show(IO,Intervalo)
#show(io, x::Intervalo) = print(io, " [$x.a, $x.b])")

end###end del modulo





