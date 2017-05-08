include("ADforward.jl")
function RK4step(f::Function,x,h)
k1=f(x);
k2=f(x+0.5*h*k1);
k3=f(x+0.5*h*k2);
k4=f(x+h*k3);
return (h/6.0)*(k1+2.0*k2+2.0*k3+k4);
end

function RK4(f::Function,x0,T,N::Integer)

df=1;
h=T/N;
F(x)=x+RK4step(f,x,h);
DF=ADforward(F)；
    x=x0;
    df=1;
  for i=1:N
        x+=RK4step(f,x,h);
        dF=DF(x);
        df=DF*df;
  end
    return df
end
