using Carretera
using FactCheck

facts("Probamos las funciones auxiliares Pos") do

  C = Carretera1D(20).carretera

  Cambiar_Vehiculo!(C[5], 5, 5, 2, 0, 1)
  Cambiar_Vehiculo!(C[11], 5, 11, 2, 0, 2)
  Cambiar_Vehiculo!(C[18], 5, 18, 2, 0, 3)
  Cambiar_Vehiculo!(C[15], -1, 15, -2, 0, 0)

  @fact Pos_izq(C) --> 18
  @fact Pos_izq(C[1:17]) --> 11
  @fact Pos_izq(C[1:10]) --> 5
  @fact Pos_izq(C[1:4]) --> 0

  @fact Pos_izq9(C) --> 18
  @fact Pos_izq9(C[1:17]) --> 11
  @fact Pos_izq9(C[1:10]) --> 8

  @fact Pos_der(C) --> 5
  @fact Pos_der(C[6:20]) --> 11
  @fact Pos_der(C[12:20]) --> 18
  @fact Pos_der(C[19:20]) --> 20

  @fact Pos_siguiente(C) --> 20
  @fact Pos_siguiente(C[1:18]) --> 17
end

facts("Probamos las funciones auxiliares Vehiculo") do

  C = Carretera1D(20).carretera

  Cambiar_Vehiculo!(C[5], 5, 5, 2, 0, 1)
  Cambiar_Vehiculo!(C[11], 5, 11, 2, 0, 2)
  Cambiar_Vehiculo!(C[18], 5, 18, 2, 0, 3)
  Cambiar_Vehiculo!(C[15], -1, 15, -2, 0, 0)

  @fact Vehiculo_Adelante(12, C, 20) --> 15
  @fact Vehiculo_Adelante(19, C, 20) --> 20

  @fact Vehiculo_Atras(11, C, 20) --> 20
  @fact Vehiculo_Atras(18, C, 20) --> 11
end

#fact("Probamos las funciones básicas") do

 #  C = Carretera1D(20).carretera

