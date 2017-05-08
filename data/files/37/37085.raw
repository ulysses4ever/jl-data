include("ADforward.jl")
function RK4step(f::Function,x,h)
k1=f(x);
k2=f(x+0.5*h*k1);
k3=f(x+0.5*h*k2);
k4=f(x+h*k3);
return (h/6.0)*(k1+2.0*k2+2.0*k3+k4);
end

function Eulerstep(f::Function ,x,h)
    k1=f(x);
    return h*k1;
end

function Heunstep(f::Function ,x,h)
    k1=f(x);
    k2=f(x+h*k1);
    return (h/2.0)*(k1+k2);
end

function RK4(f::Function,x0,T,N::Integer)
h=T/N;
F(x)=x+RK4step(f,x,h);
DF=ADforward(F);
    return DF(x0);
    xi=x0;
    df=1;
  for i=1:N
        dF=DF(xi);
        return dF;
        xi=F(xi);
        df=dF*df;
  end
    return df
end
