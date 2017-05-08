module PopulationModel

include("Parameters.jl")
include("PopulationTypes.jl")
include("Births.jl")
include("Deaths.jl")

export agePeople, countPopulation

function agePeople(pop::People)
    
    for i in 1:length(pop.generations)
        pop.generations[i].age += 1
    end
    
end

function countPopulation(pop::People)

    world_population = 0
    for i in 1:length(pop.generations)
        world_population += pop.generations[i].size
    end

    return world_population
end


end
