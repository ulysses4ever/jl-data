#15.  The Theater Row
using Distributions





#Given a binary vector, this returns the number of pairs of adjacent elements that are non-equal.
##In other words, the number males and females sitting next to each other.
function couples(seats::BitArray)
        sparks = 0
    for i in 1:length(seats)-1
       if (seats[i] != seats[i+1] )
               sparks +=1
       end
    end
    return sparks
end


#Now just set up the simulation function
function sim(sims)
#Set up male/female pool
population = append!(trues(8), falses(7))

    results = zeros(sims)
    for i in 1:sims
            config = sample(population,length(population), replace =false)
            results[i] = couples(config)
    end
    return mean(results)
end


sim(10000)
