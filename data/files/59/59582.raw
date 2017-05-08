using FactCheck
using Intervalos

facts("Prueba: Álgebra lineal con intervalos") do
    A=[Intervalo(0,0.5) Intervalo(1,1.5); Intervalo(2,2.5) Intervalo(3,3.5)]
    B=[Intervalo(4,4.5) Intervalo(5,5.5); Intervalo(6,6.5) Intervalo(7,7.5)]
    C=[Intervalo(2,1) Intervalo(2,1); Intervalo(3,2) Intervalo(3,2)]
    x=2
    
    @fact C => [Intervalo(1,2) Intervalo(1,2); Intervalo(2,3) Intervalo(2,3)]
    @fact A+B => [Intervalo(4,5) Intervalo(6,7); Intervalo(8,9) Intervalo(10,11)] 
    @fact A*B => [Intervalo(6,12) Intervalo(7,14); Intervalo(26,34) Intervalo(31,40)]
    @fact A*2 => [Intervalo(0,1) Intervalo(2,3); Intervalo(4,5) Intervalo(6,7)]
    @fact A^2 => [Intervalo(2,4) Intervalo(3,6); Intervalo(6,10) Intervalo(11,16)]
    @fact Tr(A) => Intervalo(3,4)
    @fact Tr(B) => Intervalo(11,12)
    @fact T(A)  => [Intervalo(0,0.5) Intervalo(2,2.5); Intervalo(1,1.5) Intervalo(3,3.5)]
    @fact Det(A)  => Intervalo(-2,-2)
    @fact adj(A)  => [Intervalo(3,3.5) Intervalo(-2.5,-2); Intervalo(-1.5,-1) Intervalo(0,0.5)]
    @fact inv(A)  => [Intervalo(-1.75,-1.5) Intervalo(0.5,0.75); Intervalo(1,1.25) Intervalo(-0.25,0)]
    @fact A*inv(A) => [Intervalo(0.125,1.875) Intervalo(-0.375,0.375); Intervalo(-1.375,1.375) Intervalo(0.125,1.875)]
end
