# Given a multidimensional index, return the indices of it neighbors
function get_neighbors(index,shape)
    i,j = index
    offsets = filter(x -> x != (0,0),
                     [(dx,dy) for dx in -1:1, dy in -1:1])
    neighbors = {}
    for (dx,dy) in offsets
        x = i + dx
        y = j + dy
        if 1 <= x <= shape[1] &&  1 <= y <= shape[2]
            push!(neighbors,(x,y))
        end
    end
    return neighbors
end

# Given a boolean array representing a game of life board, 
# take one time step and replace the given array with the new one
function lifestep(board)
    shape = size(board)
    newboard = copy(board)

    for (index_1d,cell) in enumerate(board)
        index_2ds = get_neighbors(ind2sub(shape,index_1d),shape)
        num_neighbors = sum(map(idx -> board[idx...], index_2ds))        

        # there are only two real cases
        if num_neighbors == 3
            newboard[index_1d] = true
        elseif num_neighbors != 2
            newboard[index_1d] = false
        end
    end
    return newboard
end

function life(board, steps)
    evolution = {board}
    for i=1:steps
        push!(evolution, lifestep(evolution[i]))
    end
    return evolution
end
