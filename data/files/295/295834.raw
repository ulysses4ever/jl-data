module ExtensiveForm

import Base.show, MCTS.Move, MCTS.GameState
export clone, domove, getmoves, getresult

#= TODO: add the concept of an InformationSet... all nodes in an information set
  must share the same moves/visits/wins
  In games of perfect information there is a 1:1 relationship between nodes and
  information sets.

  TODO: Move the wins/visits to the move itself? Store unique game info on the move
  move points to an iset which points to the player that "just moved"

  ???: Does that work, moves may be visited more often on one node, than another
  is that okay?  I think so... iset represents an indistiguishable version of the
  world... everything the player can condition on is encapsulated by the iset
=#

immutable InformationSet
    player::Int
    moves::Array{String,1}
end

immutable ExtensiveFormNode
  #needed? move::String                    # move from parent to this node OR "root" move
  parent::Union(ExtensiveFormNode,Nothing)
  children::Array{ExtensiveFormNode,1} # same size as iset.moves
  iset::InformationSet
end

#================= Start Chance =================#
#= TODO: Add the concept of a chance node:
    choose on the way down
    chance is just part of the similation... not back of back propagation
    N.B. sum of probs should be <= 1

    This and information sets can be encapsulated in extensive form
=#
type Chance
  parent::Union(ExtensiveFormNode,Chance,Nothing)
  children::Array{Union(ExtensiveFormNode,Chance),1}
  probs::Array{Float64,1}               # length(probs) = length(children) - 1
end

# if p[1] = 0... it should never be selected
# if p[1] = 1... it should always be selected
function selectchild(node::Chance)
  v = rand() # in [0,1]
  sum = 0
  i = 1
  for prob in node.probs
    sum += prob
    @assert sum <= 1
    if sum > 0 && v <= sum   # sum == 0 can not match even when v == 0
      break # if this is never met i should end up on the last child node
    end
    i += 1
  end
  node.children[i]
end

#================= End Chance =================#

# Create a deep clone of this game state.
function clone(state::ExtensiveFormNode)
  ExtensiveFormNode(state.player_justmoved, state.chips)
end

#= Update a state by carrying out the given move.
    Must update playerJustMoved.
=#
function domove(state::ExtensiveFormNode, move::Move{Int})
    @assert move.info >= 1 && move.info <= 3
    state.chips -= move.info
    state.player_justmoved = 3 - state.player_justmoved
end

#Get all possible moves from this state.
# We need to save these moves so that they can be re-used by other nodes in the same information set
function getmoves(state::ExtensiveFormNode)
    map(x -> Move{Int}(x), [1:1:min(3, state.chips)])
    #[1:1:min(3, state.chips)]
end

# Get the game result from the viewpoint of playerjm.
function getresult(state::ExtensiveFormNode, playerjm::Int)
    @assert state.chips == 0
    if state.player_justmoved == playerjm
        1.0 # playerjm took the last chip and has won
    else
        0.0 # playerjm's opponent took the last chip and has won
    end
end

# show path so far including chance...
function show(io::IO, state::ExtensiveFormNode)
  print(io, "Chips:$(state.chips) JustPlayed:$(state.player_justmoved)")
end

end
