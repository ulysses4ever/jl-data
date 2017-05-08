module Nim

using MCTS: Move, GameState
import Base.show, MCTS.clone, MCTS.domove!, MCTS.getmoves, MCTS.getresult

#=
  A state of the game Nim. In Nim, players alternately take 1,2 or 3 chips with the
  winner being the player to take the last chip.
  In Nim any initial state of the form 4n+k for k = 1,2,3 is a win for player 1
  (by choosing k) chips.

  Any initial state of the form 4n is a win for player 2.

  adapted from mcts.ai
=#
type NimState <: GameState
    player_justmoved::Int
    chips::Int
end

# At the root pretend the player just moved is p2 - p1 has the first move
newgame(chips::Int) = NimState(2, chips)

clone(state::NimState) = NimState(state.player_justmoved, state.chips)

#= Update a state by carrying out the given move.
    Must update playerJustMoved.
=#
function domove!(state::NimState, move::Move{Int})
    @assert move.info >= 1 && move.info <= 3  # valid number of chips chosen
    state.chips -= move.info
    @assert (3 - state.player_justmoved) == move.player # other player's turn
    state.player_justmoved = move.player
end

#Get all possible moves from this state.
function getmoves(state::NimState)
    map(x -> Move{Int}(3 - state.player_justmoved, x),
      [1:1:min(3, state.chips)])
end

# Get the game result from the viewpoint of given player.
# Should only be called from a terminal state
function getresult(state::NimState, player::Int)
    @assert state.chips == 0
    if state.player_justmoved == player
        1.0 # player took the last chip and has won
    else
        0.0 # player's opponent took the last chip and has won
    end
end

function show(io::IO, state::NimState)
    print(io, "Chips:$(state.chips) JustPlayed:$(state.player_justmoved)")
end

end
