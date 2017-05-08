module Intervalos

export Intervalo 

import Base.in
import Base.==
import Base.^

export Intervalo, in, == , redonUP , redonDOWN, ^, Tr, T, Det, adj, inv, N

#DEFINIMOS EL TIPO INTERVALO 
type Intervalo
    inf::Number
    sup::Number
function Intervalo(a, b)
    a, b = a > b ? (b,a) : (a,b) #función que invierte el orden de los límites en caso de que el usuario los escriba al revés 
    #set_rounging(BigFloat, RoundDown)
    inf = BigFloat("$a") #reescribe el límite inferior del intervalo en BigFloat
    #set_rounding(BigFloat, RoundUp)
    sup = BigFloat("$b") #reescribe el límite superior del intervalo en BigFloat
    new(inf, sup) #provee el nuevo intervalo en el orden correcto
end
end

#ESCALARES
#para definir los escalares en un intervalo
function Intervalo(z) 
Intervalo(z,z)
end

#REDONDEO HACIA ARRIBA Y HACIA ABAJO

#se construye la función para redondear hacia arriba 
function redonUp(f::Function,x,y) with_rounding(BigFloat,RoundUp) do 
        f(BigFloat(x),BigFloat(y))
        end 
end

#se construye la función para redondear hacia abajo
function redonDown(f::Function,x,y) with_rounding(BigFloat,RoundDown) do
        f(BigFloat(x),BigFloat(y))
    end
end

function Base.show(io::IO, t::Intervalo)
    repr="($(t.inf), $(t.sup))"
    print(io,repr)
end

#OPERACIONES ENTRE INTERVALOS

# suma
# a' + b' = [a(i) + b(i) , a(s) + b(s) ]
function +(a::Intervalo,b::Intervalo)
    Intervalo(redonDown(+,a.inf,b.inf),redonUp(+,a.sup,b.sup))
end

#resta
# a' - b' = [a(i) -  b(s) , a(s) - b(i)]
function -(a::Intervalo,b::Intervalo)
    Intervalo(redonDown(-,a.inf,b.inf),redonUp(-,a.sup,b.sup))
end

#multiplicación
#a' x b' = [min{a(i)b(i),a(i)b(s),a(s)b(i), a(s)b(s)}, max {a(i)b(i), a(i)b(s), a(s)b(i), a(s)b(s)}]
function *(a::Intervalo,b::Intervalo)
    Intervalo(min(redonDown(*,a.inf,b.inf),redonDown(*,a.inf,b.sup),redonDown(*,a.sup,b.inf),redonDown(*,a.sup,b.sup)),(max(redonUp(*,a.inf,b.inf),redonUp(*,a.inf,b.sup),redonUp(*,a.sup,b.inf),redonUp(*,a.sup,b.sup))))
end

#división
# a' / b' = a' x [1 / b(s), 1 / b(i)], #si 0 ∉ b'
function /(a::Intervalo,b::Intervalo)
    Intervalo(min(redonDown(/,a.inf,b.inf),redonDown(/,a.inf,b.sup),redonDown(/,a.sup,b.inf),redonDown(/,a.sup,b.sup)),(max(redonUp(/,a.inf,b.inf),redonUp(/,a.inf,b.sup),redonUp(/,a.sup,b.inf),redonUp(/,a.sup,b.sup))))
end

#potencia
function ^(v::Intervalo, w::Float64)
    
    if (v.sup > 0 && v.inf > 0)
        return Intervalo(v.inf^w,v.sup^w)
        
        elseif (v.sup < 0 && v.inf < 0)
        return Intervalo(v.sup^w,v.inf^w)
            else    
        return Intervalo(0,max(v.inf^2,v.sup^2))
    end
end 

#OPERACIONES CON UN ENTERO

#calcula la suma entre un número entero y el intervalo
+(a::Intervalo,z::Int64) = Intervalo(a.inf+z,a.sup+z)

#calcula la resta entre un número entero y el intervalo
-(a::Intervalo,z::Int64) = Intervalo(a.inf-z,a.sup-z)

#calcula la multiplicación entre un número entero y el intervalo
*(a::Intervalo,z::Int64) = Intervalo(z*a.inf,z*a.sup)

#calcula la división entre un número entero y el intervalo
/(z::Int64,a::Intervalo) = Intervalo(z/a.inf,z/a.sup)
/(a::Intervalo,z::Int64) = Intervalo(a.inf/z,a.sup/z)

#función potencia para un entero
function ^(v::Intervalo, w::Integer)

    if (v.sup > 0 && v.inf > 0)
        return Intervalo(v.inf^w,v.sup^w)
        elseif (v.sup < 0 && v.inf < 0)
        return Intervalo(v.sup^w,v.inf^w)
    else        
        return Intervalo(0,max(v.inf^2,v.sup^2))

end
end

#función potencia para un real
function ^(v::Intervalo, q::Real) #Definido sólo para intervalos positivos 
    exp(Intervalo(q)*log(v))
end

function ==(a::Intervalo, b::Intervalo) 
    (a.inf == b.inf && a.sup ==b.sup) && return true 
    return false 
end 

#OPERACIONES ENTRE MATRICES

#multiplicación por un entero
function *(A::Array{Intervalo,2}, b::Int64)
    [A[1]*b A[3]*b; A[2]*b A[4]*b]
end

#Traza
function Tr(A::Array{Intervalo,2})
    A[1]+A[4]
end

#Transpuesta
function T(A::Array{Intervalo,2})
    [A[1] A[2]; A[3] A[4]]
end

#Determinante
function Det(A::Array{Intervalo,2})
    (A[1]*A[4])-(A[3]*A[2])
end

#Adjunta
function adj(A::Array{Intervalo,2})
    [A[4] A[2]*-1; A[3]*-1 A[1]]
end

function/(A::Array{Intervalo,2}, a::Intervalo)
    [A[1]/a A[2]/a; A[3]/a A[4]/a]
end

#Inversa
function inv(A::Array{Intervalo,2})
    adj(A)/Det(A)
end

#Norma
#function N(A::Array{Intervalo,2})
#    max(A[1]+A[2], A[3]+A[4])
#end

end
