
export countDead, removeEmptyGeneration

function countDead(population::People)
    
    for i in 1:length(population.generations)
        if population.generations[i].age > deathAge
            population.generations[i].males = 0
            population.generations[i].females = 0
            population.generations[i].size = 0
        else
            number_of_deaths = countGenerationDeaths(population.generations[i])
            distributeDeath(population.generations[i], number_of_deaths)
        end
    end

end

function distributeDeath(generation::Generation, total::Int64)
    
    number_of_females = convert(Int64, round(0.5*total))
    
    generation.size -= total
    
    if generation.size < 0
        generation.size = 0
    end
    
    generation.females -= number_of_females
    
    if generation.females < 0 
        generation.females = 0
    end
    
    generation.males -= (total - number_of_females)
    
    if generation.males < 0
        generation.males = 0
    end
    
end

function countGenerationDeaths(generation::Generation)
    deaths = 0
    
    if generation.size*chanceOfDeath < 0.5
        for i in 1:generation.size
            if rand() < chanceOfDeath
                deaths += 1
            end
        end
    else
        deaths = chanceOfDeath*generation.size
        deaths = convert(Int64,round(deaths))
    end
    
    return deaths
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
