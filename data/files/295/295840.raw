module MCTS

import Base.show

#================= Move ================#
type Move{T}
  wins::Float64        # expected times led to victory
  visits::Int          # times move was taken
  player::Int
  info::T              # game specific information attached to move

  Move(player, info) = new(0, 0, player, info)
  Move() = new(0, 0, 2)   # "root" move, player 1 is first, player 2 "just moved"
end

function show(io::IO, m::Move)
    print(io, "$(m.player)->$(m.info)")
end

#================= GameState ================#

#=
  A state of the game, i.e. the game board.
  The are the only functions which are absolutely necessary to implement UCT in
  any 2-player complete information deterministic zero-sum game, although they
  can be enhanced and made quicker, for example by using a GetRandomMove()
  function to generate a random move during rollout.

  getmoves(GameState)
  domove!(GameState, Move)
  getresult(GameState, Player)
  clone(GameState)

  By convention the players are numbered 1 and 2.
=#
abstract GameState

function getmoves(state::GameState, move::Move)
  @assert false
end
function domove!(state::GameState, move::Move)
  @assert false
end
function getresult(state::GameState, player::Int)
  @assert false
end
function clone(state::GameState)
  @assert false
end



#================ Node ===================#
#= A node in the game tree.
  N.B. wins is always from the viewpoint of playerJustMoved.
=#
type Node

  move::Move                    # move from parent to this node OR "root" move
  parent::Union(Node,Nothing)
  children::Array{Node,1}
  untried_moves::Array{Move,1}

  Node(state::GameState; move = Move{Nothing}(), parent = nothing) =
      new(move,
          parent,
          [],
          getmoves(state))
end

#=
  Use the UCB1 formula to select a child node. Often a constant UCTK is applied so we have
  lambda c: c.wins/c.visits + UCTK * sqrt(2*log(self.visits)/c.visits to vary the amount of
  exploration versus exploitation.
=#
function selectchild(node::Node)
    #i = indmax(map(c -> c.wins/c.visits + sqrt(2*log(node.visits)/c.visits), node.children))
    i = indmax(map(c -> c.move.wins/c.move.visits + sqrt(2*log(node.move.visits)/c.move.visits), node.children))
    node.children[i] # assumes O(1) index lookup
end

#=
  Remove m from untriedMoves and add a new child node for this move.
  Return the added child node
=#
function addchild!(parent::Node, m::Move, state::GameState)
    n = Node(state, move = m, parent = parent)
    parent.untried_moves = filter(x -> x != m, parent.untried_moves)  # TODO: linked list?
    push!(parent.children, n)
    n
end

#=
  Update this node - one additional visit and result additional wins.
  result must be from the viewpoint of playerJustmoved.
=#
function update!(node::Node, result::Float64)
    node.move.visits += 1
    node.move.wins += result
end

function show(io::IO, node::Node)
    print(io, "[M:$(node.move) W/V:$(node.move.wins)/$(node.move.visits) U:$(node.untried_moves)]")
end

#= TODO:

    def TreeToString(self, indent):
        s = self.IndentString(indent) + str(self)
        for c in self.childNodes:
             s += c.TreeToString(indent+1)
        return s

    def IndentString(self,indent):
        s = "\n"
        for i in range (1,indent+1):
            s += "| "
        return s
=#
function children_to_string(node::Node)
    s = ""
    for c in node.children
        s = "$s$c\n"
    end
    s
end

#=
  Conduct a UCT search for itermax iterations starting from rootstate.
  Return the best move from the rootstate.
  Assumes 2 alternating players (player 1 starts), with game results in the range [0.0, 1.0].
=#
function uct(rootstate::GameState, itermax::Int; verbose::Bool = false)

    println("Creating root node...")
    rootnode = Node(rootstate)

    println("Created root node...")
    for i = 1:itermax
        node = rootnode
        println("Clone...")
        state = clone(rootstate)

        # Select
        println("select...")
        while length(node.untried_moves) == 0 && length(node.children) > 0
            # node is fully expanded and non-terminal...
            node = selectchild(node)
            domove!(state, node.move)
        end

        # Expand
        println("rollout...")
        if length(node.untried_moves) > 0
            # we can expand (i.e. state/node is non-terminal)...
            m = node.untried_moves[rand(1:length(node.untried_moves))]
            domove!(state, m)
            node = addchild!(node, m, state) # add child and descend tree
        end

        # Rollout - this can often be made orders of magnitude quicker using a state.GetRandomMove() function
        println("rollout...")
        while true # while state is non-terminal
            moves = getmoves(state)
            if length(moves) == 0
              break
            end
            domove!(state, moves[rand(1:length(moves))])
        end

        # Backpropagate
        while node != nothing # backpropagate from the expanded node and work back to the root node
            update!(node, getresult(state, node.move.player)) # state is terminal. Update node with result from POV of node.playerJustMoved
            node = node.parent
        end
    end

    # Output some information about the tree - can be omitted
    if verbose
      println(rootnode.TreeToString(0))
    else
      println(children_to_string(rootnode))
    end

    i = indmax(map(c -> c.move.visits, rootnode.children))
    rootnode.children[i].move # return the move that was most visited
end

#=
  Play a sample game between two UCT players where each player gets a different
  number of UCT iterations (= simulations = tree nodes).
=#
function uct_playgame(state::GameState)

    # TODO: how to make this code agnostic to 'player_justmoved'
    while length(getmoves(state)) != 0
        println("$state")
        pl_itermax = state.player_justmoved == 1 ? 10 : 10
        pl_verbose = false
        println("UCT...")
        m = uct(state, pl_itermax, verbose = pl_verbose)
        println("Best Move: $m\n")
        domove!(state, m)
    end

    if getresult(state, state.player_justmoved) == 1.0
      println("Player $(state.player_justmoved) wins!")
    elseif getresult(state, state.player_justmoved) == 0.0
      println("Player $(3 - state.player_justmoved) wins!")
    else
      println("Nobody wins!")
    end
end

end
