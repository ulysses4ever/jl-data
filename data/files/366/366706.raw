module Nastran

import Base: show, +, -

using ImmutableArrays

export NastranDeck, GenericNastranDeck, NastranModel
export CoordSet,get_coord,get_global_xyz
export MassCG

include("cards.jl")
using .Cards

include("deck.jl")

include("coords.jl")
include("model.jl")
include("weights.jl")

end # module
