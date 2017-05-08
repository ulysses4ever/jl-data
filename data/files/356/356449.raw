module OXO

using MCTS: Move, GameState
import Base.show, MCTS.clone, MCTS.domove!, MCTS.getmoves, MCTS.getresult

#=
  A state of the game, i.e. the game board.
  Squares in the board are in this arrangement
  012
  345
  678
  where 0 = empty, 1 = player 1 (X), 2 = player 2 (O)

  adapted from mcts.ai
=#
type OXOState <: GameState
    player_justmoved::Int
    board::Array{Int}
end

newgame() = OXOState(2, zeros(Int,9))

# TODO: rename copy?
clone(orig::OXOState) = OXOState(orig.player_justmoved, copy(orig.board))

function domove!(state::OXOState, move::Move{Int})
    @assert move.info >= 1 && move.info <= 9 && state.board[move.info] == 0
    state.player_justmoved = move.player
    state.board[move.info] = move.player
end

function getmoves(state::OXOState)
    map(x -> Move{Int}(3 - state.player_justmoved, x),
      filter(i -> state.board[i] == 0,
        [1:1:9]))
end

function getresult(state::OXOState, player::Int)
    for (x,y,z) in [(1,2,3), (4,5,6), (7,8,9),
                    (1,4,7), (2,5,8), (3,6,9),
                    (1,5,9), (3,5,7)]
        if state.board[x] == state.board[y] && state.board[x] == state.board[z]
            return state.board[x] == player ? 1.0 : 0.0
        end
    end
    @assert length(getmoves(state)) == 0
    0.5 # draw
end

function show(io::IO, state::OXOState)
    for i in 1:9
        print(io, space_str(state.board[i]))
        i % 3 == 0 && print(io, "\n")
    end
end

function space_str(value::Int)
    value == 0 ? "." : value == 1 ? "X" : "O"
end

end
