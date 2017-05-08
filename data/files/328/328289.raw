using CA
using Model
import models
using Disp

global width = 100
global height = 100
global ca = CellularAutomata(width, height)

function init_random!(ca, model)
    init_grid!(ca, (x,y)->rand_cell(model))
end

function init_area!(ca, model, size)
    init_grid!(ca, (x,y)->ifelse(x>100 && x<100+size && y>100 && y<100+size, model.C-1, 0))
end

function init_area_random!(ca, model, size)
    init_grid!(ca, (x,y)->ifelse(x>100 && x<100+size && y>100 && y<100+size, rand(0:model.C-1), 0))
end

global model = models.cca


init_random!(ca, model)
init_area!(ca, model, 3)
init_area_random!(ca, model, 50)


function draw_grid(ca::CellularAutomata, offset::(Int64, Int64))
    OFFSET = (10, 10)
    ofsx, ofsy = OFFSET
    cell_size = 0.7
    step = 0.0

    for j in 1:ca.height
        for i in 1:ca.width
            x, y = ofsx + i*(cell_size+step), ofsy + j*(cell_size+step)
            draw_square((x, y), cell_size, 
                        Float64[float(ca.grid[j, i]) / model.C for x = 1:3]
                        )
        end
    end
end

function draw()
    draw_grid(ca, (10, 10))

    next_gen!(ca, model)
end

add_draw_function(draw)
initDisp()
mainLoop()
