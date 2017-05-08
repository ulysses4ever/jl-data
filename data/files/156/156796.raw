
include("params.jl")
include("population.jl")
include("birth.jl")
include("death.jl")

using Parameters
# Create initial population
first_generation = Generation(20,2,1,1)
population = People()

population.generations[1] = first_generation


# For each year
for year in startYear:endYear
    # Count the number of births
    number_of_births = countBirths(population)
    println("Number of births in year $year = $number_of_births")
    
    # Create a generation with that number of births
    new_generation = createGeneration(number_of_births)
    
    # Add generation to the number of people
    push!(population.generations, new_generation)
    
    # Age the population
    agePeople(population)
    
    # Count the number of deaths in each year
    countDead(population)
    
    # Remove deaths from each generation
    
    # Remove empty generations from the population
    removeEmptyGeneration(population)
    
    total_size = countPopulation(population)
    
    println("Total size = $total_size")
    
end
