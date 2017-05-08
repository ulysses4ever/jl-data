# An attempt to rewrite the game of life using sets rather than arrays
# (faster for sparse boards)

# One dimensional index => two dimensional index
function ravel_index(index,shape)
    xind = index % shape[1]
    yind = ((index - xind) / shape[1]) + 1
    return (int(xind), int(yind))
end

# given a twod array, return

function lifestep(board)
    shape = size(board)
    
    for (x,y) in x=1:shape[1],y=shape[2]
        