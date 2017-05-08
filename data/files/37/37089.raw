include("natural_spline.jl")

f(x)=1/(1+x*x);
s=natural_spline(f,-5,5,100);

plot1(f,s,[-5,5])
plot(x->s(x),-5,5)
plot(x->f(x),-5,5)
