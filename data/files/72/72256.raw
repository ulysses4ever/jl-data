Enter file contents here
const MUT_CHANCE = 0.6
const MUT_RATE = 0.01
const XOVER_CHANCE = 0.5
const INIT_MAX = 10

type Individual
  dim::Int
  fitness::Float32
  chromosome::Array{Float32}

  function Individual(dim::Int)
    this = new()
    this.dim = dim
    this.chromosome = rand(dim) * (INIT_MAX * 2 - INIT_MAX)
    updateFitness!(this)
    return this
  end
end

function updateFitness!(input::Individual)
  total::Float32 = 0
  for i = 1:input.dim
    cur = input.chromosome[i]
    total += cur * cur
  end
  input.fitness = total
  return total
end


function xover!(parent1::Individual, parent2::Individual)
  if rand() > XOVER_CHANCE
    return
  end
  xover::Int = rand(1:parent1.dim)
  for i = xover:parent1.dim
    parent1.chromosome[i] = parent2.chromosome[i]
  end
end

function mutate!(parent::Individual)
  for i = 1:parent.dim
    if rand() < MUT_CHANCE
      parent.chromosome[i] += rand() * MUT_CHANCE * 2 - MUT_CHANCE
    end
  end
end
