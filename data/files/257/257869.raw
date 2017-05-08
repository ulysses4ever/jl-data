module Intervalos
export Intervalo, round_down, round_up, diametro, big_pi

#########################
function round_down()
    set_rounding(BigFloat, RoundDown)
end

function round_up()
    set_rounding(BigFloat, RoundUp)
end

type Intervalo
    a::Number
    b::Number

# Para que redondee bien los BigFloat necesito agarrar una cadena binaria 
# y hacer que Julia la convierta a BigFloat con el redondeo requerido.
function Intervalo(x,y)
        if x>y
            a=y
            b=x
        else
            a=x
            b=y
        end
			
        round_down()
        c=BigFloat("$a")
        round_up()
        d=BigFloat("$b")

        new(c,d)
    end

#### Para constantes matematicas

function Intervalo(y::MathConst,x::MathConst)
    b=big(x)
    a=big(y)
    Intervalo(a,b)
end

function Intervalo(x::MathConst,y)
    c=big(x)
    Intervalo(big(c),y)
end

function Intervalo(y,x::MathConst)
    c=big(x)
    Intervalo(y,big(c))
end

function Intervalo(x::MathConst)
    c=big(x)
    Intervalo(big(c))
end
#################

function Intervalo(x::Real)
    Intervalo(x,x)
end


end
#########################

##################
### ARITMETICA ###
##################

function +(x::Intervalo, y::Intervalo)
    round_down()
    ra=x.a+y.a
    
    round_up()
    rb=x.b+y.b
    h
    r=Intervalo(ra, rb)
  
    r
end


function -(x::Intervalo, y::Intervalo)
    
    round_down()
    ra=x.a-y.b
    
    round_up()
    rb=x.b-y.a
    
    r=Intervalo(ra, rb)
   
    r
    
end


function *(x::Intervalo, y::Intervalo)   
    round_down()
    ra=min(x.a*y.a, x.a*y.b, x.b*y.a, x.b*y.b)
    
    round_up()
    rb=max(x.a*y.a, x.a*y.b, x.b*y.a, x.b*y.b)
    
    r=Intervalo(ra, rb)

    r 
end


function /(x::Intervalo, y::Intervalo)
    if y.a<0 && y.b>0
        println("El intervalo contiene al cero.")
    else
    
        round_down()
        ra=min(x.a/y.a, x.a/y.b, x.b/y.a, x.b/y.b)

        round_up()
        rb=max(x.a/y.a, x.a/y.b, x.b/y.a, x.b/y.b)

        r=Intervalo(ra, rb)

        r
    end     
end


function ^(x::Intervalo, n::Integer)
    if mod(n,2)!=0
        r=Intervalo(x.a^n, x.b^n)
    else
        if x.a>=0
            r=Intervalo(x.a^n, x.b^n)
        elseif x.b<0
            r=Intervalo(x.b^n, x.a^n)
        else
            r=Intervalo(0, max(x.a^n, x.b^n))
        end
    end
end

function ^(x::Intervalo, a::FloatingPoint)
    r=Intervalo(0,0)
    if mod(a,1)==0
        n=int(a)
        r=x^n
    else
        if x.a<0 || x.b<0
            throw(DomainError())
        else
            r=Intervalo(x.a^a, x.b^a)#ya que x^a es monótonamente creciente
        end
    end
    r
end
         
function +(x::Intervalo,y::Real)
    x+Intervalo(y)
end

function +(x::Real,y::Intervalo)
    Intervalo(x)+y
end

function -(x::Intervalo,y::Real)
    x-Intervalo(y)
end

function -(x::Real,y::Intervalo)
    Intervalo(x)-y
end

function *(x::Intervalo,y::Real)
    x*Intervalo(y)
end

function *(x::Real,y::Intervalo)
    Intervalo(x)*y
end

function /(x::Intervalo,y::Real)
    x/Intervalo(y)
end

function /(x::Real,y::Intervalo)
    Intervalo(x)/y
end

import Base.abs

function abs(x::Intervalo)
    Intervalo(abs(x.a), abs(x.b))
end

function monot(x::Intervalo, f::Function)
    if f(x.a)<f(x.b)
        Intervalo(f(x.a),f(x.b))
    else
        Intervalo(f(x.b),f(x.a))
    end
end   

function Base.show(io::IO, t::Intervalo)
    intval="($(t.a), $(t.b))"
    print(io,intval)
end

import Base.ones
import Base.zeros
function ones(::Type{Intervalo}, n::Integer)
    one=Intervalo[]
    for i=1:n
        one=push!(one,Intervalo(1))
    end
    one
end

function zeros(::Type{Intervalo}, n::Integer)
    zero=Intervalo[]
    for i=1:n
        zero=push!(zero,Intervalo(0))
    end
    zero
end

Base.zero(::Type{Intervalo}) = Intervalo(0)
Base.zero(::Type{Any}) = 0

function diametro(x::Intervalo)
    abs(x.b-x.a)
end

############## SIN/COS ######

function pi_n(x::Intervalo)
    pimenos=floor(x.a*2/pi)
    pimas=ceil(x.b*2/pi)
    Intervalo(pimenos, pimas)
end

import Base.sin

function sin(x::Intervalo)
    sin_a=sign(x.a)*sin(abs(x.a)) ##### sirve o no?
    sin_b=sign(x.b)*sin(abs(x.b))
    n=pi_n(x)
    k=(n-1)/2
    
    if diametro(n)>=4
        Intervalo(-1,1)
     
    elseif diametro(n)==3
        if (mod(n.a,2)!=0 && mod(n.a,2)!=0) || (mod(n.b,2)!=0 && mod(n.b,2)!=0)
            Intervalo(-1, max(sin_a,sin_b))
        else
            Intervalo(min(sin_a,sin_b),1)
        end   
        
    elseif diametro(n)==2
        
        if mod(n.a,2)!=0 #&& mod(k.a,2)!=0
            ##decreciente o creciente##\
            Intervalo(sin_a, sin_b)
        elseif mod(n.a,2)==0 && mod(((n.a-1)/2),2)==0
            Intervalo(-1, max(sin_a,sin_b))
        else
            Intervalo(min(sin_a,sin_b),1)
        end
        
    elseif diametro(n)<=1
        Intervalo(sin_a, sin_b)
    end
    
end

import Base.cos
function cos(x::Intervalo)
    x2=x+big(pi)/2
    sin(x2)
end

end

