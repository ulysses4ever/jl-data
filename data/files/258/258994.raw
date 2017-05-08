using Intervalos
Pkg.add("FactCheck")
using FactCheck

facts ("Pruebas") do
  M=Interval(1.0, 5.0)
  N=Interval(3.0,7.0)
  P=Interval(-1.0, 1.0)
  y=Interval(0.0, 1.25)
  z=sin(y)/cos(y)

  @fact M+N=>Interval(4.0, 12.0)
  @fact N-M=>Interval(2.0, 2.0)
  @fact M*N=>Interval(3.0, 35.0)
  @fact M/N=>Interval(0.1428571428571428, 1.6666666666666667)
  @fact M+1.0=>Interval(2.0, 6.0)
  @fact M*Interval(2.0)=>(3.0,7.0)
  @fact contains(Interval(.1,0.1),0.1)=>true
  @fact P^2=>Interval(0.0, 1.0)
  @fact P^3=>Interval(-1.0, 1.0)
  @fact contains(sin(Interval(-1.5707,1.5770)),0.0)=>true
  @fact contains(cos(Interval(0.0,3.1416)),0.0)=>true
  @fact z.right==tan(y).right=>true
  @fact exp(M) => Interval(exp(M.left),exp(M.right))
  @fact exp(log(y))==y => true


end


