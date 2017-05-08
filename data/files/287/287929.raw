#!/usr/bin/julia
#
# A cellular automata mimicking the behavior of forest fires
#
##

const N = 128      # Size of the map
const T = 10000    # Number of updates to do
const p = 0.15     # Probability of growing forest on empty
const f = 0.005    # Probability of spontaneously igniting a forest
const d = 0.35     # Initial forest density

# The map is defined by the state of each cell:
# 
# 0 - Empty
# 1 - Forest
# 2 - Burning
#
land = int(rand(N,N) .> d)

# Create a randomized list of all of the cells we care about
indices = shuffle(reshape([[y,x] for x=2:N-1, y=2:N-1], (N-2)^2))
for t=1:T
    
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
        println(idx)
        # If it's on fire, kill it
        if land[y,x] == 2
            land[y,x] = 0
        # If it is a forest, check if we should light it on fire
        elseif land[y,x] == 1
            # If any neighbors are on fire, light it up
            if land[y-1,x] == 2 || land[y+1,x] == 2 ||
                  land[y,x-1] == 2 || land[y,x+1] == 2 ||
                  land[y-1,x-1] == 2 || land[y-1,x+1] == 2 ||
                  land[y+1,x-1] == 2 || land[y+1,x+1] == 2 
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

    # Reshuffle the access order
    shuffle!(indices)

end


