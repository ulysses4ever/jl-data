
include("params.jl")


using Parameters

function countDead(population::People)
    
    for i in 1:length(population.generations)
        if population.generations[i].age > deathAge
            population.generations[i].males = 0
            population.generations[i].females = 0
            population.generations[i].size = 0
        end
    end
    

end

function removeEmptyGeneration(population::People)
    new_generations = Array(Generation,1)
    
    alive_generations = 0
    for i in 1:length(population.generations)
        if population.generations[i].size > 0
            alive_generations += 1
        end
    end
    new_generations = Array(Generation, alive_generations)
    
    added = 0
    for i in 1:length(population.generations)
        if population.generations[i].size > 0
            added += 1
            new_generations[added] = population.generations[i]
        end
    end
    
    population.generations = new_generations
    
end 

