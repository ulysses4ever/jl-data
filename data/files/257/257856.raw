module Intervalos
export Intervalo, round_down, round_up

function round_down()
    set_rounding(BigFloat, RoundDown)
end

function round_up()
    set_rounding(BigFloat, RoundUp)
end

type Intervalo
    a::Real
    b::Real

# Para que redondee bien los BigFloat necesito agarrar una cadena binaria 
# y hacer que Julia la convierta a BigFloat con el redondeo requerido.
   function Intervalo(a,b)
        round_down()
        c=BigFloat("$a")
        round_up()
        d=BigFloat("$b")

        new(c,d)
    end
end


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
    if y.a<=0 && y.b>=0
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

function Intervalo(x::Real)
    Intervalo(x,x)
end

end

