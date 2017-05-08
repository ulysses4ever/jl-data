using Winston
#@everywhere include("travelling_salesman.jl")
require("travelling_salesman.jl")

toOptimize = ["Lille",
            "Paris",
            "Lyon",
            "Marseille",
            "Toulouse",
            "Besançon",
            "Rennes",
            "Limoges",
            "Ajaccio",
            "Caen",
            "Bordeaux",
            "Strasbourg",
            "Orléans",
            "Clermont-Ferrand",
            "Montpellier",
            "Lille"]

#N = 4 

#done for the fun of using pmap nad having a parallelized code
#@everywhere simul(x) = travelling_salesman.simulated_annealing(x,5500,0.85,25000)
#results = [toOptimize for i=1:N]
#while N > 1
#  println("size of results: $(length(results))")
#  results = pmap(simul, results)
#  sorted = sort(results,by= x->travelling_salesman.cost(x))
#  if mod(N/2,2)==0
#    N = N/2
#  elseif N/2==1
#    N = 1
#  else
#    N = N/2+1
#  end
#  results =results[1:N]
#  println(travelling_salesman.cost(results[1]))
#end

results, cout = travelling_salesman.simulated_annealing(toOptimize, 5500,0.85,25000)
println(results)
p = FramedPlot(
        title="Travelling Saleman",
        xlabel="Iteration",
        ylabel="Cost")
setattr(p.frame1, draw_grid=true)
add(p, Curve(1:length(cout), cout,color="blue"))
#savefig("travelling.png")
