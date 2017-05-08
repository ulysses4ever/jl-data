using EA
using ProgressMeter

const T_PERCENT = 0.1 #0.1 os currently in the lead

type Population <: AbstractPopulation
  population::Array{AbstractIndividual}
  size::Int
  elite::AbstractIndividual
  t_size::Int
  hallofFame::Array{AbstractIndividual}
  a
  b
  y
  function Population(size::Int,a,b,y)
    this = new()
    this.a = a
    this.b = b
    this.y = y
    this.hallofFame = Array(AbstractIndividual,0)
    this.size = size
    this.population = [Individual() for _ = 1:size]
    for indiv in this.population
      updateFitness!(indiv,a,b,y)
    end
    this.elite = bestItem(this)
    this.t_size = int(size * T_PERCENT)

    return this
  end
end

function select(pop::Population)
  minIndiv::AbstractIndividual = pop.population[rand(1:pop.size)]
  for i = 1:(pop.t_size - 1)
    tempIndiv = pop.population[rand(1:pop.size)]
    if minIndiv.fitness < tempIndiv.fitness
      minIndiv = tempIndiv
    end
  end
  return minIndiv
end

function longest(pop::Population)
  minIndiv::AbstractIndividual = pop.population[rand(1:pop.size)]
  for i = 1:(pop.t_size - 1)
    tempIndiv = pop.population[rand(1:pop.size)]
    if length(minIndiv.chromosome) < length(tempIndiv.chromosome)
      minIndiv = tempIndiv
    end
  end
  return length(minIndiv.chromosome)
end

function evolve!(pop::Population, gen::Int)
  #p = Progress(gen,1)
  startTime = time()
  proc_count = length(procs())
  for(_ = 1:gen)
    newPop = Array(Individual, 0)
    push!(newPop, deepcopy(pop.elite))
    s = genIndividuals(pop.size -1, pop)
    append!(newPop, s)
    pop.population = newPop
    setElite(pop)
    #next!(p)
    if (_ % 25 == 0)
      push!(pop.hallofFame, pop.elite)
      println()
      println("ACC: ", 1/pop.elite.total_acc)
      println("TORQUE: ", 1/pop.elite.torque_error-1)
      println("COST: ", 1/pop.elite.total_cost)
      println("POINTS")
      for i = 1:length(pop.elite.results.points)
        point = pop.elite.results.points[i][end]
        println(int(point.x), "\t", int(point.y), "\t", int(point.z), "\t", int(pop.elite.results.pointDiffs[i]))
      end
      println("LENGTH:\t", pop.elite.results.length)
      println("CURRENT DURATION\t",  int(time() - startTime),"s")
    end
  end
  return pop.elite, pop.hallofFame
end

function genIndividuals(num, pop)
  out = Array(AbstractIndividual, num)
  for i = 1:num
    indiv::Individual = xover(select(pop), select(pop))
    mutate!(indiv)
    updateFitness!(indiv,pop.a,pop.b,pop.y)
    out[i] = indiv
  end
  return out
end

function bestItem(pop::Population)
  bestIndiv::AbstractIndividual = pop.population[1]
  for i = 2:pop.size
    if bestIndiv.fitness < pop.population[i].fitness
      bestIndiv = pop.population[i]
    end
  end
  return bestIndiv
end

function setElite(pop::Population)
  curElite = bestItem(pop)
  if pop.elite.fitness < curElite.fitness
    pop.elite = deepcopy(curElite)
  end
  pop.elite = deepcopy(bestItem(pop))
end
