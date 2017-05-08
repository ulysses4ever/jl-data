include("mcts.jl")
include("extensiveform.jl")
include("nim.jl")
include("oxo.jl")

import Othello
import OXO
import Nim

#= with help from from mcts.ai =#

#srand(1234) # uncomment to seed the rng

state = Othello.newgame(4) # uncomment to play Othello on a square board of the given size
#state = OXO.newgame() # uncomment to play OXO
#state = Nim.newgame(9) # uncomment to play Nim with the given number of starting chips
MCTS.uct_playgame(state)
