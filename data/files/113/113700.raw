# An attempt to rewrite the game of life using sets rather than arrays
# (faster for sparse boards)

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

type Board
    #these should be restricted to the correct tuples and dicts
    # (need to figure out how to do this)
    dims::Tuple
    activecells::Dict
end

# board should be a dict 
function lifestep(board::Board)
    # this will be a dict whose keys are cells that have any active neighbors
    # the values are the number of active neighbors
    cells = {None => None} # how do i create an empty dict?
    for idx,activecell in enumerate(board.activecells):
        for neighbor_cell in get_neighbors(ind2sub(idx),board.dims):
            try
                cells[neighbor_cell] += 1
            catch
                cells[neighbor_cell] = 1
            end
        end
    end

    newboard = board

    # now we have to iterate over all the cells with neighbors to update things
            
    end
end