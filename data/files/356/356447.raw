module Othello

using MCTS: Move, GameState
import Base.show, MCTS.clone, MCTS.domove!, MCTS.getmoves, MCTS.getresult

#=
  A state of the game of Othello, i.e. the game board.

  The board is a 2D array where 0 = empty (.), 1 = player 1 (X), 2 = player 2 (O).
  In Othello players alternately place pieces on a square board - each piece played
  has to sandwich opponent pieces between the piece played and pieces already on the
  board. Sandwiched pieces are flipped.

  This implementation modifies the rules to allow variable sized square boards and
  terminates the game as soon as the player about to move cannot make a move
  (whereas the standard game allows for a pass move).

  adapted from mcts.ai
=#
type OthelloState <: GameState
    player_justmoved::Int
    board::Array{Int,2}
    size::Int
end

function newgame(size::Int = 8)
    println("newgame...")
    # At the root pretend the player just moved is p2 - p1 has the first move
    @assert size % 2 == 0 # size must be integral and even

    # 0 = empty, 1 = player 1, 2 = player 2
    board = zeros(Int, (size, size))
    board[size/2, size/2]   = board[size/2+1, size/2+1] = 1
    board[size/2, size/2+1] = board[size/2+1, size/2]   = 2
    OthelloState(2, board, size)
end

clone(orig::OthelloState) = OthelloState(orig.player_justmoved,
                                         copy(orig.board),
                                         orig.size)

function domove!(state::OthelloState, move::Move{(Int,Int)}) #=???{Tuple{Int,2}})=#
    println("doing move... $move\n$state")
    (x, y) = move.info
    @assert isonboard(state, x, y) && state.board[x, y] == 0
    m = getallsandwichedcounters(state, x, y)
    state.player_justmoved = 3 - state.player_justmoved
    state.board[x, y] = state.player_justmoved
    for (a, b) in m
        state.board[a, b] = state.player_justmoved
    end
end

function getmoves(state::OthelloState)
    println("getting moves...")
    moves = map(x -> Move{(Int,Int)}(3 - state.player_justmoved, x),
        filter(t -> state.board[t[1],t[2]] == 0 &&
                    existssandwichedcounter(state, t[1], t[2]),
               [(x,y) for x in 1:state.size, y in 1:state.size]))

    for m in moves
      println("$m $(typeof(m))")
    end
    println("end getting moves...")
    moves
end

# Speeds up getmoves by only considering squares which are adjacent to an enemy-occupied square.
function isadjacenttoenemy(state::OthelloState, x::Int, y::Int)
    for (dx,dy) in [(0,+1),(+1,+1),(+1,0),(+1,-1),(0,-1),(-1,-1),(-1,0),(-1,+1)]
        if state.isonboard(x+dx,y+dy) &&
           state.board[x+dx][y+dy] == state.player_justmoved
            return true
        end
    end
    false
end

# t[1] = dx, t[2] = dy... how can I deconstruct a tuple?
function adjacentenemydirections(state::OthelloState, x::Int, y::Int)
    #println("adjacentenemydirections: $x $y")
    filter(t -> isonboard(state, x+t[1], y+t[2]) &&
           state.board[x+t[1], y+t[2]] == state.player_justmoved,
      [(0,1),(1,1),(1,0),(1,-1),(0,-1),(-1,-1),(-1,0),(-1,1)])
end

# Does there exist at least one counter which would be flipped if my counter was placed at (x,y)?
function existssandwichedcounter(state::OthelloState, x::Int, y::Int)
    for (dx,dy) in adjacentenemydirections(state, x, y)
        if length(getsandwichedcounters(state, x, y, dx, dy)) > 0
            return true
        end
    end
    false
end

# Is (x,y) a possible move (i.e. opponent counters are sandwiched between (x,y) and my counter in some direction)?
function getallsandwichedcounters(state::OthelloState, x, y)
    mapreduce(t -> getsandwichedcounters(state, x, y, t[1], t[2]),
              vcat,
              adjacentenemydirections(state, x, y))
end

# Return the coordinates of all opponent counters sandwiched between (x,y) and my counter.
function getsandwichedcounters(state::OthelloState, x::Int, y::Int, dx::Int, dy::Int)
    x += dx
    y += dy
    sandwiched = (Int,Int)[]
    while isonboard(state, x, y) && state.board[x, y] == state.player_justmoved
        push!(sandwiched, (x,y))
        x += dx
        y += dy
    end
    if isonboard(state, x, y) && state.board[x, y] == 3 - state.player_justmoved
        sandwiched
    else
        [] # nothing sandwiched
    end
end

function isonboard(state::OthelloState, x::Int, y::Int)
    x >= 1 && x <= state.size && y >= 1 && y <= state.size
end

function getresult(state::OthelloState, player::Int)
    (jmcount,notjmcount) = reduce((acc, t) ->
                                    state.board[t[1], t[2]] == player ?
                                      (acc[1]+1, acc[2]) : (acc[1], acc[2]+1),
      [(x,y) for x in 1:state.size, y in 1:state.size])

    #notjmcount = len([(x,y) for x in range(self.size) for y in range(self.size) if self.board[x][y] == 3 - playerjm])
    if jmcount > notjmcount
        1.0
    elseif notjmcount > jmcount
        0.0
    else
        0.5 # draw
    end
end

function show(io::IO, state::OthelloState)
    for y in state.size:-1:1
        for x in 1:state.size
            print(io, space_str(state.board[x, y]))
        end
        print(io, "\n")
    end
end

function space_str(value::Int)
    value == 0 ? "." : value == 1 ? "X" : "O"
end

end
