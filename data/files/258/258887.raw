using FactCheck
using intervalos
facts("Ultima funciones") do
A = Intervalo(2,1);
B = Intervalo(1,2.0);
x = 4;
y=0;
f(x)=x;
@fact inter(A) => [A.inf, A.sup]
@fact inter(A+B) => [A.inf+B.inf, A.sup+B.sup]
@fact recorrer(f,2)(x) => 6
@fact recorrer(f,2)(y) => 2
end

