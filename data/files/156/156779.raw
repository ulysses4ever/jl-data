include("params.jl")
using Parameters

function countBirths(pop::People)
    number_of_births = 0
    
    for i in 1:length(pop.generations)
        # Check if the generation can breed
        if ableToBreed(pop.generations[i])
            number_of_births += countGenerationBirths(pop.generations[i])
        end
    end
    return number_of_births
end

function createGeneration(total::Int64)

    number_of_females = convert(Int64,round(0.5*total))
    
    return Generation(0,total,total - number_of_females, number_of_females)
end


function ableToBreed(generation::Generation)
    if generation.age >= minBreedingAge && generation.age <= maxBreedingAge
        return true
    end
    return false
end

function countGenerationBirths(generation::Generation)
    births = 0
    
    if generation.females*chanceOfBirth < 0.5
        for i in 1:generation.females
            if rand() < chanceOfBirth
                births += 1
            end
        end
    else
        births = chanceOfBirth*generation.females
        births = convert(Int64,round(births))
    end
    
    return births
end
