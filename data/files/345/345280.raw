module Pruebas

using FactCheck, Intervalos, Derivadas, Krawczyk, Compat

facts("Pruebas de Intervalos.jl") do
	context("Conjunto vacio isempty") do
		@fact isempty(Intervalo(NaN,NaN)) => true
	end
	context("Igualdad de Intervalos") do
		@fact Intervalo(-1,1) == Intervalo(-1,1) => true
		@fact Intervalo(0,2) == Intervalo(-1,1) => false
		@fact Intervalo(-Inf,Inf) == Intervalo(-Inf,Inf) => true
		@fact Intervalo(NaN,NaN) == Intervalo(NaN,NaN) => true
		@fact Intervalo(NaN,NaN) == Intervalo(-Inf,Inf) => false
		@fact Intervalo(0.1,0.2) == Intervalo(0,1) => false
	end
	context("Contencion de Intervalos") do
		@fact 0 in Intervalo(0,0) => true
		@fact 0.1 in Intervalo(0.1,0.1) => true
	# Contención de un Intervalo en otro Intervalo
		@fact Intervalo(-Inf,Inf) in Intervalo(-Inf,Inf) => true
		@fact Intervalo(-1,1) in Intervalo(-Inf,Inf) => true
		@fact Intervalo(-Inf,Inf) in Intervalo(-1,1) => false
		@fact isempty(Intervalo(NaN,NaN)) => true		
		@fact Intervalo(NaN,NaN) in Intervalo(NaN,NaN) => true
		@fact Intervalo(NaN,NaN) in Intervalo(0,1) => true
		@fact Intervalo(-1,1) in Intervalo(0,1) => false
		@fact Intervalo(-1,1) in Intervalo(-1,1) => true
		@fact Intervalo(-1,1) in Intervalo(-10,10) => true
		@fact Intervalo(0.1,0.1) in Intervalo(0.1,0.1) => true
		@fact Intervalo(NaN,NaN) in Intervalo(0.1,0.1) => true
	end
# union
	context("Union e interseccion")	do
		@fact union(Intervalo(-Inf,Inf),Intervalo(-Inf,Inf)) => Intervalo(-Inf,Inf)
		@fact union(Intervalo(-Inf,Inf),Intervalo(NaN,NaN)) => Intervalo(-Inf,Inf)
		@fact union(Intervalo(NaN,NaN),Intervalo(NaN,NaN)) => Intervalo(NaN,NaN)
		@fact union(Intervalo(-1,1), Intervalo(-Inf,Inf)) => Intervalo(-Inf,Inf)
		@fact union(Intervalo(-1,1), Intervalo(NaN,NaN)) => Intervalo(-1,1)
		@fact intersect(Intervalo(-Inf,Inf),Intervalo(-Inf,Inf)) => Intervalo(-Inf,Inf)
		@fact intersect(Intervalo(-Inf,Inf),Intervalo(NaN,NaN)) => Intervalo(NaN,NaN)
		@fact intersect(Intervalo(NaN,NaN),Intervalo(NaN,NaN)) => Intervalo(NaN,NaN)
		@fact intersect(Intervalo(0,2),Intervalo(-Inf,Inf)) => Intervalo(0,2)
		@fact intersect(Intervalo(0,2),Intervalo(NaN,NaN)) => Intervalo(NaN,NaN)
	end
	context("mid, abs, long y rad") do
		@fact mid(Intervalo(1,1)) => 1
		@fact mid(Intervalo(0,0)) => 0
		@fact mid(Intervalo(0,2)) => 1
		@fact abs(Intervalo(1,1)) => 1
		@fact abs(Intervalo(0,1)) => 1
		@fact abs(Intervalo(-1,1)) => 1
		@fact abs(Intervalo(-10,1)) => 10
		@fact long(Intervalo(1,1)) => 0
		@fact long(Intervalo(-1,1)) => 2
		@fact long(Intervalo(-2,-1)) => 1
		@fact rad(Intervalo(1,1)) => 0
		@fact rad(Intervalo(-1,1)) => 1
		@fact rad(Intervalo(0,0)) => 0
	end
end

facts("Pruebas de Derivadas.jl") do
	context("Funciones elementales") do
		cte(x::Derivada) = Derivada(1,0,0)
		@fact cte(Derivada(1,1,0)) => Derivada(1,0,0)
		@fact cte(Derivada(1,1,0)).dif => 0
		@fact cte(Derivada(1,1,0)).ddif => 0
		id(x::Derivada) = x
		@fact id(Derivada(1,1,0)) => Derivada(1,1,0)
		@fact id(Derivada(1,1,0)).dif => 1
		@fact id(Derivada(1,1,0)).ddif => 0
		polim(x::Derivada) = x^3
		@fact polim(Derivada(0.1,1,0)) => Derivada(0.1^3, 3*0.1^2, 3*2*0.1^1)
		polpa(x::Derivada) = x^2
		@fact polpa(Derivada(0.1,1,0)) => Derivada(0.1^2, 2*0.1^1, 2)
	end
	context("Senos y cosenos") do
		@fact sin(Derivada(0,1,0)).fun => cos(Derivada(0,1,0)).dif
		@fact sin(Derivada(0,1,0)).dif => cos(Derivada(0,1,0)).fun
		@fact sin(Derivada(0,1,0)).ddif => -sin(Derivada(0,1,0)).fun
		@fact sin(Derivada(pi,1,0)).fun => roughly(0)
		@fact sin(Derivada(0,1,0)).fun => roughly(0)
		@fact cos(Derivada(pi,1,0)).fun => -1
		@fact cos(Derivada(0,1,0)).fun => 1
	end
	context("Funciones no tan elementales") do
		@fact sqrt(Derivada(1,1,0)) => Derivada(1,0.5,-0.25)
		@fact sqrt(Derivada(1,1,0)) => Derivada(1,1,0)^(1/2)
		@fact log(Derivada(1,1,0)).dif => 1/Derivada(1,1,0).fun
		@fact exp(Derivada(1,1,0)) => exp(Derivada(1,1,0))
		@fact Derivada(1,1,0)^3 => Derivada(1,1,0)^3.0
		@fact Derivada(1,1,0)^1.5 => Derivada(1,1,0)^(3/2)
	end
end

facts("Derivadas e Intervalos juntos") do
	X = Intervalo(-1,3)
	@fact typeof(Derivada(X)) => Derivada
	@fact Derivada(X) => Derivada(X,Intervalo(1,1),Intervalo(0,0))
	@fact typeof(Derivada(X).fun) => Intervalo
	@fact typeof(Derivada(X).dif) => Intervalo
	@fact typeof(Derivada(X).ddif) => Intervalo
	@fact 2 == Intervalo(2,2) => false
	Y = Intervalo(2,2)
	@fact Derivada(mid(Y),mid(Intervalo(1,1)), mid(Intervalo(0,0))) => Derivada(2,1,0)
end

# El modulo de Krawczyk es escencialemten Intervalos y derivadas juntos. Se prueba esto en el notebook del proyecto final.

end

