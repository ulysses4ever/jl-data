
const LENGTH_PENALTY = 5000

const XOVER_CHANCE = 0.8
const INIT_MIN = 3
const INIT_MAX = 6

using EA

type Individual <: AbstractIndividual
  fitness::Float64
  chromosome::Array{AbstractGene,1}
  total_acc
  torque_error
  total_cost
  results
  function Individual()
    this = new()
    init_total = rand(INIT_MIN:INIT_MAX)
    this.chromosome = [Gene() for _ = 1:init_total]
    return this
  end
  #add constructor for case where chromosomeis given
  function Individual(chromosome::Array{AbstractGene,1})
    this = new()
    this.chromosome = chromosome
    this.fitness = 0
    return this
  end
end

function xover(parent1::Individual, parent2::Individual)
  if rand() < XOVER_CHANCE
    len1 = length(parent1.chromosome)
    len2 = length(parent2.chromosome)
    xpoint = rand(1:len1)
    xpoint2 = rand(1:len2)
    total_len = xpoint + 1 + (len2-xpoint2)
    newChromosome = Array(AbstractGene, total_len)
    for i = 1:xpoint
      newChromosome[i] = deepcopy(parent1.chromosome[i])#Will be replaced with copy soon
    end
    count = xpoint
    for j = xpoint2:len2
      count += 1
      newChromosome[count] = deepcopy(parent2.chromosome[j])
    end
    return Individual(newChromosome)
  end
  return deepcopy(parent1)
end

function mutate!(parent::Individual)
  for gene in parent.chromosome
    mutate!(gene)
  end
end


