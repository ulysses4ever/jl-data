#!/usr/bin/julia
#
# A cellular automata mimicking the behavior of forest fires
#
##

const N = 64        # Size of the map
const T = 1000      # Number of updates to do
const p = 0.45       # Probability of growing forest on empty
const df= 10.0      # The amount to increment f after T steps
const d = 0.75       # Initial forest density
const thresh = 0.055  # The maximum f to go up to

plotting = false

# This will hold the list of mimimum forest coverage for each ratio
coverage_list = Float64[]

f = 0.0001 # Probability of spontaneously lighting a forest cell

# Create a randomized list of the the cells we care about
indices = shuffle(reshape([[y,x] for x=2:N-1, y=2:N-1], (N-2)^2))

while thresh > f
    # The map is defined by the state of each cell:
    #  0 - Empty
    #  1 - Forest
    #  2 - Burning
    land = int(rand(N,N) .> (1-d))
    land[1,:] = 0
    land[:,1] = 0
    land[end,:] = 0
    land[:,end] = 0

    # Reset the minimum coverage
    min_coverage = sum(int(land .== 1))

    for t=1:T

        if plotting
            writedlm("out/solution.dat."*lpad(string(t),length(string(int(T))),"0"), land)
        end

        # Set boundaries to 0
        # So we don't have to worry about making the world a torus
        # or any such nonsense
        land[1,:] = 0
        land[:,1] = 0
        land[end,:] = 0
        land[:,end] = 0
    
        # Look at each cell in a random order
        for idx in indices
            y = idx[1]
            x = idx[2]
            
            # If it's on fire, kill it
            if land[y,x] == 2
                land[y,x] = 0
            # If it is a forest, check if we should light it on fire
            elseif land[y,x] == 1
                # If any neighbors are on fire, light it up
                if land[y-1,x] == 2 || land[y+1,x] == 2 ||
                      land[y,x-1] == 2 || land[y,x+1] == 2# ||
                      #land[y-1,x-1] == 2 || land[y-1,x+1] == 2 ||
                      #land[y+1,x-1] == 2 || land[y+1,x+1] == 2 
                    land[y,x] = 2
                # otherwise it just might happen anyways
                elseif rand() > f
                    land[y,x] = 2
                end
            # If it's empty, see if something will grow
            elseif rand() > p
                land[y,x] = 1
            end
        end
        # Calculate coverage and record if it's a record low
        coverage = sum(int(land .== 1))
        if min_coverage > coverage
            min_coverage = coverage        
        end
       
        # Reshuffle the access order
        shuffle!(indices)
    end
    # Record the max burn amount
    push!(coverage_list,min_coverage)

    # Increment f
    f += df
end

println(coverage_list./(N^2))

