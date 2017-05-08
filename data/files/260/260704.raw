using Intervalosa

using FactCheck


facts("definición correcta de intervalos, prop elementales") do

@fact (0.1 ∈ [0.1, 0.2])=>true
@fact (0.1 ∈ Intervalo(0, 0.2)) => true
@fact Intervalo(0,-1)=>Intervalo(-1, 0)
@fact (0 ∈ UnionI(Intervalo(-9, -1), Intervalo(1,Inf)))=> false
@fact (Intervalo(-1,1) ⊂ Intervalo(-2,2)) =>true
@fact (Intervalo(-1,1) ⊂ Intervalo(0,10)) =>false
@fact (Intervalo(-10,10) ⊂ Intervalo(-2,2)) =>false
@fact norm(Intervalo(9,0))=>9

x=Intervalo(0,10) 
y=Intervalo(-1,2)
@fact (Intrsc(y, x)==Intrsc(x,y))=>true

end


facts("sumas, restas, multiplicaciones, divisiones") do

@fact Intervalo(-9, 1)+Intervalo(6,10)=>Intervalo(-3, 11)
@fact Intervalo(0)+Intervalo(1,0)=>Intervalo(1,0) #suma
@fact Intervalo(0)-Intervalo(1,0)=>Intervalo(-1,0)   #resta
@fact Intervalo(1)*-1-(-2*Intervalo(2,0))=> Intervalo(-1,3)
@fact 3*Intervalo(1,0)=>Intervalo(3,0)
@fact Intervalo(1,1)/Intervalo(-1,Inf)=>UnionI(Intervalo(-Inf,-1),Intervalo(0,Inf))
@fact Intervalo(-1,1)^2=> Intervalo(0,1)
@fact Intervalo(-1,1)*Intervalo(-1,1)=> Intervalo(-1,1)

end

facts("funciones elementales")do
###para funciones monótonas ^, exp
@fact log(10, Intervalo(1,10))=>Intervalo(0,1)
@fact Intervalo(0,4)^0.5=>Intervalo(0, 2)

@fact exp(Intervalo(0.2, 0.4))=>Intervalo(RDOWN(exp,0.2), RUP(exp,0.4))

###checar cosas de raices
end


