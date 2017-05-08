module Nastran

import Base: show, +

using ImmutableArrays

export NastranDeck, GenericNastranDeck, NastranModel
export CBEAM, CONM2, CELAS1, CQUADR, CTRIAR, CELAS2, RBE2, RBE3, CBUSH, CROD
export CoordSet,get_coord,get_global_xyz

include("cards.jl")
include("deck.jl")

include("coords.jl")
include("model.jl")

include("masscg.jl")
include("weights.jl")

end # module
