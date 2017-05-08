#################################################
#  This module contains RK4step , Eulerstep and
#  Heunstep function
#  Author: wangjiechao
#  Date: 2016.1.13
#  Version: 1.0
#################################################

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
