using Intervalos
Pkg.add("FactCheck")
using FactCheck

facts ("Pruebas") do
  M=Interval(1.0, 5.0)
  N=Interval(3.0,7.0)
  P=Interval(-1.0, 1.0)

  @fact M+N=>Interval(4.0, 12.0)
  @fact N-M=>Interval(2.0, 2.0)
  @fact M*N=>Interval(3.0, 35.0)
  @fact M/N=>Interval(0.1428571428571428, 1.6666666666666667)
  @fact M+1.0=>Interval(2.0, 6.0)
  @fact M*Interval(2.0)=>(3.0,7.0)
  @fact contains(Interval(.1,0.1),0.1)=>true
  @fact P^2=>Interval(0.0, 1.0)
  @fact P^3=>Interval(-1.0, 1.0)

end


