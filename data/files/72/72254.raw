include("Individual.jl")
const TOURNAMENT_SIZE = 7

type Population
  population::Array{Individual}
  size::Int
  dim::Int

  function Population(size::Int, dim::Int)
    this = new()
    this.size = size
    this.dim = dim
    this.population = Array(Individual,size)
    for i = 1:size
      this.population[i] = Individual(dim)
    end
    return this
  end
end

function select(pop::Population)
  minIndiv::Individual = pop.population[rand(1:pop.dim)]
  for i = 1:(TOURNAMENT_SIZE - 1)
    tempIndiv = pop.population[rand(1:pop.dim)]
    if minIndiv.fitness > tempIndiv.fitness
      minIndiv = tempIndiv
    end
  end
  return minIndiv
end

function evolve(pop::Population, gen::Int)
  for i = 1:gen
    for indiv in pop.population
      xover!(indiv, select(pop))
      mutate!(indiv)
      updateFitness!(indiv)
    end
  end
end

function minItem(pop::Population)
  minIndiv::Individual = pop.population[1]
  for i = 2:pop.size
    if minIndiv.fitness > pop.population[i].fitness
      minIndiv = pop.population[i]
    end
  end
  return minIndiv
end

