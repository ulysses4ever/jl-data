using FactCheck
using intervalos
facts("test") do
I0=Intervalo(0,0);
I1= Intervalo(1,1);
I2= Intervalo(0.1,0.1);
I3=Intervalo(2,1);
I4= Intervalo(1,2);
I5= Intervalo(1.5,1.9);
a=0.1;
b=0;
@fact I3+I4 => Intervalo(2,4)
@fact I3-I4 => Intervalo(-1,1)
@fact I2*I1 => I2
@fact I3*I0 => I0
@fact a in I2 => true
@fact b in I2 => false
@fact I3 => I4
@fact I3^0 => Intervalo(1,1)
@fact subset(I5,I3) => true
end
