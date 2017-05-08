using Intervalos

using FactCheck




facts("definición correcta de intervalos, prop elementales") do
#contencio de un punto en el intervalo definido por el mismo
@fact (Intervalo(0.1).a<=BigFloat("$(0.1)")<=Intervalo(0.1).b)=>true
#intervalos en el orden correcto
@fact Intervalo(0,-1)=>Intervalo(-1e+00, 0e+00)

end


facts("sumas, restas, multiplicaciones, divisiones") do

@fact Intervalo(-9, 1)+Intervalo(6,10)=>Intervalo(-3, 11)
@fact Intervalo(0)+Intervalo(1,0)=>Intervalo(1,0) 
@fact Intervalo(0)-Intervalo(1,0)=>Intervalo(-1,0) 
@fact Intervalo(1)*-1-(-2*Intervalo(2,0))=> Intervalo(-1,3)
@fact 3*Intervalo(1,0)=>Intervalo(3,0)
@fact Intervalo(-1,1)^2=> Intervalo(0,1)
@fact Intervalo(-1,1)*Intervalo(-1,1)=> Intervalo(-1,1)

end

facts("funciones elementales")do
@fact Intervalo(0,4)^0.5=>Intervalo(0, 2)
set_rounding(BigFloat, RoundUp)
a=BigFloat("$(3π/2+0.1)")
x=sin(a)

set_rounding(BigFloat, RoundUp)
b=BigFloat("$(5π/2-0.1)")
y=sin(b)

@fact sin(Intervalo(3π/2+0.1, 5π/2-0.1))=>Intervalo(x, y)
end

#hacer uno similar para coseno

facts("intervalos con complejos") do
a=Intervalo(0,1)
b=Intervalo(1,3)
c=Intervalo(0,2)
d=Intervalo(1,1)
e=Intervalo(1,4)
f=Intervalo(2,4)
g=Intervalo(-1,1)
h=Intervalo(-1,2)
i=Intervalo(-3,-1)


@fact absn(IC(a,a)).a<=0&&absn(IC(a,a)).b>=sqrt(BigFloat("$(2)"))=>true  #QUE LA NORMA SE CALCULE BIEN
@fact IC(a,b)+IC(b,d)=>IC(e,f) #SUMA
@fact IC(a,c)-IC(a,a)=>IC(g,h) #RESTA
@fact Intervalo(0,1)*(cos(π)-im*sin(π))=> IC(Intervalo(0,1)*cos(π), -1*Intervalo(0,1)*sin(π)) #MULTIPLICACION DE INTERVALO POR RAÍZ ENESIMA
@fact conjg(IC(a,b))=> IC(a,i) #COMPLEJO CONJUGADO
@fact absn(conjg(IC(a,b)))=>absn(IC(a,b)) #LA NORMA EL IGUAL PARA EL CONJUGADO


end
