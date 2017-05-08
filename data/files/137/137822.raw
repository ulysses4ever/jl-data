
# Simple Dynamic Time Warping example

function d(x, y)  
    abs(x - y) 
end


function DTW(seqA::Array{Int64}, seqB::Array{Int64})
    # cost matrix
    r = size(seqA)[1]
    c = size(seqB)[1]
    cost = zeros(r,c)

    # initialization
    cost[1, 1] = d(seqA[1], seqB[1])
    for i = 2:r
        cost[i, 1] = cost[i-1, 1] + d(seqA[i], seqB[1])
    end

    for j = 2:c
        cost[1, j] = cost[1, j-1] + d(seqA[1], seqB[j])
    end

    for i = 2:r
        for j = 2:c
            cost[i, j] = min(cost[i-1, j], cost[i, j-1], cost[i-1, j-1]) + d(seqA[i], seqB[j])
        end
    end

    # print
    for i = 2:r
        for j = 2:c
            println(" ", cost[i, j])
        end
        println("")
    end 

    return cost[end,end]
end