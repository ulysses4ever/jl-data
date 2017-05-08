import  Base.sin
import  Base.cos
import  Base
#define a type which stored primitive function and derived function
type Data
    value::Vector{Any}
    derivate::Vector{Any}
end
function ADforward(f::Function)
    g(x)=f(Data(x,1).derivate;#a0=x,b0=1
    ##g(x)=f(Data(x,Int64(ones(length(x))))).derivate;#a0=x,b0=1
end
##operator overloading
##operator *
function *(T1::Data,T2::Data)
  return Data(T1.value.*T2.value,T1.value.*T2.derivate+T1.derivate.*T2.value)
end

function *(x::Any,T1::Data)
  return Data(x.*T1.value,x.*T1.derivate)
end
function *(T1::Data,x::Any)
  return Data(x.*T1.value,x.*T1.derivate)
end
##operator +
function +(T1::Data,T2::Data)
  return Data(T1.value+T2.value,T1.derivate+T2.derivate)
end
function +(x::Any,T1::Data)
  return Data(x.+T1.value,T1.derivate)
end
function +(T1::Data,x::Any)
  return Data(x.+T1.value,T1.derivate)
end
##operator sin()
function sin(T1::Data)
   return Data(sin(T1.value),T1.derivate.*cos(T1.value))
end
##operator cos()
function cos(T1::Data)
   return Data(cos(T1.value),-T1.derivate.*sin(T1.value))
end
