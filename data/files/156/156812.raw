

type Generation
    age :: Int64
    size :: Int64
    males :: Int64
    females :: Int64
    
    function Generation(age, size, males, females)
        return new(age, size, males, females)
    end
    
    
end

type People
    
    generations :: Array{Generation,1}
    
    function People()
        return new(Array(Generation,1))
    end
    
end

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
