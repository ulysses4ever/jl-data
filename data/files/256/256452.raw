
module Derivatives

import Base.==, Base.contains, Base.^, Base.exp, Base.log, Base.sin, Base.cos, Base.tan

export Derive,makex, +,-,*,/, ==,^





type Derive
    
    f::Float64
    d::Float64
    
    
    Derive(f,d) = new(f,d)
    Derive(f) = new(f,0)
end

#Redefino las operaciones aritméticas siguiendo las convenciones de arriba


function +(v::Derive,w::Derive)
    
    y=Derive(0,0)
    
    y.f = (v.f+w.f)
    y.d = (v.d+w.d)
    
    y
end

function +(v::Real,w::Derive)
    
    y=Derive(0,0)
    
    y.f = (w.f+v)
    y.d = (w.d+v)
    
    y
end

function +(v::Derive,w::Int)
    
    y=Derive(0,0)
    
    y.f = (v.f+w)
    y.d = (v.d+w)
    
    y
end

function +(v::Derive,w::Real)
    
    y=Derive(0,0)
    
    y.f = (v.f+w)
    y.d = (v.d+w)
    
    y
end

function -(v::Derive,w::Derive)
    
    y=Derive(0,0)
    
    y.f = (v.f-w.f)
    y.d = (v.d-w.d)
    
    y
end

function -(v::Real,w::Derive)
    
    y=Derive(0,0)
    
    y.f = (v-w.f)
    y.d = (w.d)
    
    y
end

function -(v::Derive,w::Real)
    
    y=Derive(0,0)
    
    y.f = (v.f-w)
    y.d = (v.d)
    
    y
end

function *(v::Derive,w::Derive)
    
    y=Derive(0,0)
    
    y.f = (v.f*w.f)
    y.d = (v.d*w.f+v.f+w.d)
    
    y
end

function *(c::Real,v::Derive)
    y=Derive(0,0)
    
    y.f = v.f*c
    y.d = v.d*c
    
    y
end


function /(v::Derive,w::Derive)
    
    y=Derive(0,0)
    
    y.f = (v.f/w.f)
    y.d = (v.d*w.f-w.d*v.f)/(w.f)^2
    
    y
end

function ^(v::Derive,c::Real)
    
    y=Derive(0,0)
    
    y.f = v.f^c
    y.d = c*(v.f^(c-1.0))*v.d
    
    y
end

function ^(v::Derive,c::Real)
    
    y=Derive(0,0)
    
    y.f = v.f^c
    y.d = c*(v.f^(c-1.0))*v.d
    
    y
end  

function makex(x)
    
    y = Derive(x,1)
end

#Ahora redefino las funciones trigonométricas etc para que funciones con mi nuevo tipo

function Base.sin(v::Derive)
    
    y=Derive(0,0)
    
    y.f = sin(v.f)
    y.d = -cos(v.f)*v.d
    
    y
end

function Base.cos(v::Derive)
    
    y=Derive(0,0)
    
    y.f = cos(v.f)
    y.d = sin(v.f)*v.d
    
    y
end

function Base.tan(v::Derive)
     
    y=Derive(0,0)
    
    y.f = tan(v.f)
    v.d = v.d*sec(v.f)^2
    
    y
end   

function Base.exp(v::Derive)
    
    y=Derive(0,0)
    
    y.f = exp(v.f)
    v.d = v.d*exp(v.f)
    
    y
end

function Base.log(v::Derive)
     
    y=Derive(0,0)
    
    y.f = log(v.f)
    v.d = v.d/(v.f)
    
    y
end  

end 
