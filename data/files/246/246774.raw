@__FILE__
using PyPlot


include("EA.jl")
include("RobotGene.jl")
include("VarLengthIndividual.jl")
include("GAPopulation.jl")


pygui(true)
function testFunction()
  size = 5
  gen = 50
  testPop = Population(size,1000,0,0)
  println(bestItem(testPop).fitness)
  #println("INIT SIZE")
  #println([length(indiv.chromosome) for indiv in testPop.population])
  elite, hof = evolve!(testPop, gen)
  dafit, results = updateFitness!(elite,1000,0,0)
  println("LENLENHOF\t",length(hof))
  #println("FINAL SIZE")
  #println([length(indiv.chromosome) for indiv in testPop.population])
  println("FITNESS\n",bestItem(testPop).fitness,"\n")
  #println("TOTAL TARGETS\n",length(results.points),"\n")
  #println("TOTAL POINTS\n",length(results.points[1]),"\n")
  #println("TOTAL ITEMS\n",length(elite.chromosome),"\n")
  #println("TOTAL DH LINKS\n",length(results.DHList.links),"\n")

  num_toruqe_negatives = 0

  for target in results.torques
    for motor in target
      for torque in motor
        if torque < 0
          num_toruqe_negatives += 1
        end
      end
    end
  end


  println("NUM NEG TORQUE\n",num_toruqe_negatives,"\n")
  #println("ALL TORQUES\n",results.torques,"\n")
  #println(results.points[1])
  #println("POINTS LIST\n",results.points,"\n")
  #println("COMP LIST\n",elite.chromosome,"\n")
  motor_count = 0
  for gene in elite.chromosome
    if gene.comp_type == 2
      motor_count += 1
    end
  end
  println("NUMBER OF MOTORS\n", motor_count)
  println("COST\n", results.cost)
  for i = 1:length(TARGETS)
    xp = [p.x for p in results.points[i]]
    yp = [p.y for p in results.points[i]]
    zp = [p.z for p in results.points[i]]
    plot3D(xp,yp,zp)
    scatter3D(xp,yp,zp)
    scatter3D(TARGETS[i].x, TARGETS[i].y, TARGETS[i].z, color="Red")
  end
  return testPop
end

t1 = time()
x = testFunction()
println("elapsed time was :", time() - t1,"s")
println(length(x.elite.chromosome))
tt = 1
for indiv in x.hallofFame
  println("INDIV ",tt)
  println("FITTNETHH\ ", indiv.results.fitness)
  println("FITTNEss\ ", indiv.fitness)
  tt += 1
  for diff in indiv.results.pointDiffs
    println(diff)
  end
end

println("LONGEST:\t",longest(x))
