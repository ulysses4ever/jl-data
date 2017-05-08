using CA
using Model
import term


width = 170
height = 140
ca = CellularAutomata(width, height)

xtasy = generations([1,4,5,6], [2,3,5,6], 16)
RainZha = generations([2], [2,3], 8)
lifegame = life([2,3], [3])
brians_brain = generations([], [2], 3)
swirl        = generations([2,3], [3,4], 8)
model = swirl

init_grid!(ca, (x,y)->rand_cell(model))


colors = ASCIIString["black", "red", "green", "yellow", "blue", "purple", "cyan", "white"]
function disp_term(ca::CellularAutomata)
    for j in 1:ca.height
        for i in 1:ca.width
            print(term.characters[ca.grid[j, i]+1], " ")
#            print(ca.grid[j, i], " ")
#            print(term.color(colors[ca.grid[j, i]+1], "  "))
        end
        print("\n")
    end
end


to=200
for i in 1:to
    term.clear_display()
    disp_term(ca)
    next_gen!(ca, model)
#    sleep(0.1)
end
