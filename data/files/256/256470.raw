module Intervals

export Interval, +,-,*,/

#Ahora quiero implementar redondeo. lo más lógico es redondear el primer número para abajo y el segundo para arriba
type Interval
    
    a::Float64
    b::Float64
    
end
    


function UpSum(x,y)
    with_rounding(Float64,RoundUp) do
        x+y
    end
end

function DownSum(x,y)
    with_rounding(Float64,RoundDown) do
        x+y
    end
end

function UpSubs(x,y)
    with_rounding(Float64,RoundUp) do
        x-y
    end
end

function DownSubs(x,y)
    with_rounding(Float64,RoundDown) do
        x-y
    end
end

function UpProd(x,y)
    with_rounding(Float64,RoundUp) do
        x*y
    end
end

function DownProd(x,y)
    with_rounding(Float64,RoundDown) do
        x*y
    end
end

function UpDiv(x,y)
    with_rounding(Float64,RoundUp) do
        x/y
    end
end

function DownDiv(x,y)
    with_rounding(Float64,RoundDown) do
        x/y
    end
end

function +(x::Interval, y::Interval)
    
    z=Interval(UpSum(x.a,y.a),UpSum(x.b,y.b))
    
end


function -(x::Interval, y::Interval)
    
    z=Interval(UpSubs(x.a,y.a),UpSubs(x.b,y.b))
    
end


#para la multiplicación y la división es un poco más complejo, así que tomo el intervalo más amplio posible, es decir, el m'inimo de las multiplicaciones 
#posibles como a y el máximo como b, y así mismo para la división


function *(x::Interval, y::Interval)
    
    z=Interval(min(DownProd(x.a,y.a),DownProd(x.a,y.b),DownProd(x.b,y.a),DownProd(x.b,y.b)),max(UpProd(x.a,y.a),UpProd(x.a,y.b),UpProd(x.b,y.a),UpProd(x.b,y.b)))
    
end

function /(x::Interval, y::Interval)
    
    
    z=Interval(min(DownDiv(x.a,y.a),DownDiv(x.a,y.b),DownDiv(x.b,y.a),DownDiv(x.b,y.b)),max(UpDiv(x.a,y.a),UpDiv(x.a,y.b),UpDiv(x.b,y.a),UpDiv(x.b,y.b)))
    
end

end
