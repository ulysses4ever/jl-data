using CA
using Model
import term
using disp

const width = 160
const height = 80
ca = CellularAutomata(width, height)
const cyclic_spirals = Cyclic(8, 3, 5, nbhd.moore(3))
const model = cyclic_spirals
init_grid!(ca, (x,y)->rand_cell(model))

function main()
    const width = 160
    const height = 80

    ca = CellularAutomata(width, height)

    const xtasy = generations([1,4,5,6], [2,3,5,6], 16)
    const RainZha = generations([2], [2,3], 8)
    const lifegame = life([2,3], [3])
    const brians_brain = generations([], [2], 3)
    const swirl        = generations([2,3], [3,4], 8)
    const cubism = Cyclic(3, 2, 5, nbhd.neumann(2))

    const cyclic_spirals = Cyclic(8, 3, 5, nbhd.moore(3))

    const model = cyclic_spirals

    init_grid!(ca, (x,y)->rand_cell(model))


    const colors = ASCIIString["black", "red", "green", "yellow", "blue", "purple", "cyan", "white"]
    function disp_term(ca::CellularAutomata)
        for j in 1:ca.height
            for i in 1:ca.width
                print(term.characters[ca.grid[j, i]+1], "")
    #            print(ca.grid[j, i], " ")
#                print(term.color(colors[ca.grid[j, i]+1], "  "))
            end
            print("\n")
        end
    end


    const to=2000
    for i in 1:to
        term.clear_display()
        disp_term(ca)
        next_gen!(ca, model)
        sleep(0.1)
    end

end
#main()


function draw_grid(ca::CellularAutomata)
    OFFSET = (0, 0)
    ofsx, ofsy = OFFSET
    cell_size = 0.1
    step = 0.1

    for j in 1:ca.height
        for i in 1:ca.width
            x, y = ofsx + i*(cell_size+step), ofsy + j*(cell_size+step)
            draw_square((x, y), cell_size, 
                        [ca.grid[j, i] / model.C for x = 1:3] * 255
                        )
        end
    end
end

function draw()
    draw_grid(ca)
    next_gen!(ca, model)
    sleep(0.1)
end

add_draw_function(draw)
disp_main()
