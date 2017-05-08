using Intervalos

using FactCheck


facts("primeros facts que voy a realizar") do

@fact 1=>1

@fact 2*2 => 4

@fact Intervalo(0)+Intervalo(1,0)=>Intervalo(1,0)

@fact 3*Intervalo(1,0)=>Intervalo(3,0)

@fact (0.1 ∈ [0.1, 0.2])=>true
@fact (0.1 ∈ Intervalo(0, 0.2)) => true
#que sea capaz de voltear un intervalo si se encuentra al revés

@fact Intervalo(0,-1)=>Intervalo(-1, 0)


#ALGUNAS PROPIEDADES DE LA DIVISIÓN ENTRE INTERVALOS QUE CONTIENEN AL CERO
@fact Intervalo(1,1)/Intervalo(-1,Inf)=>UnionI(Intervalo(-Inf,-1),Intervalo(0,Inf))

##que sea capaz de mostrar que un intervalo se encuentra en otro mas grande

@fact (0 ∈ UnionI(Intervalo(-9, -1), Intervalo(1,Inf)))=> false

@fact (Intervalo(-1,1) ⊂ Intervalo(-2,2)) =>true


@fact (Intervalo(-1,1) ⊂ Intervalo(0,10)) =>false


@fact (Intervalo(-10,10) ⊂ Intervalo(-2,2)) =>false

@fact Intervalo(-1,1)^2=> Intervalo(0,1)
@fact Intervalo(-1,1)*Intervalo(-1,1)=> Intervalo(-1,1)

#@fact eva(cos, Intervalo)
@fact eva(cos, Intervalo(0, π)) => Intervalo(-1,1)
@fact Intervalo(0,4)^0.5=>Intervalo(0, 2)

###checar cosas de raices
end


