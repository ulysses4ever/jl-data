
include("Parameters.jl")
import PopulationModel
using PopulationModel

# Create initial population
first_generation = Generation(initialPopulationAge,
                              initialPopulationSize,
                              initialMales,initialFemales)
population = People()

population.generations[1] = first_generation


# For each year
for year in startYear:endYear
    println()
    println("----------YEAR $year---------------")
    
    # Count the number of births
    number_of_births = countBirths(population)
    println("Number of births = $number_of_births")
    
    # Create a generation with that number of births
    new_generation = Generation(number_of_births)
    
    # Add generation to the number of people
    push!(population.generations, new_generation)
    
    # Age the population
    agePeople(population)
    
    # Count and remove the dead from each generation
    number_of_deaths = countDead(population)
    println("Number of deaths = $number_of_deaths")
    
    # Remove empty generations from the population
    removeEmptyGeneration(population)
    
    total_size = countPopulation(population)
    
    println("Total Population = $total_size")
    
end
