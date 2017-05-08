module Nastran

import Base: show, +, -, zero

using FixedSizeArrays

export NastranDeck, GenericNastranDeck, NastranModel
export CoordSet,get_coord,get_global_xyz
export MassCG, XYZ

typealias XYZ Vec{3,Float64}
typealias Mat3x3 Mat{3,3,Float64}

include("cards.jl")
using .Cards

include("deck.jl")

include("coords.jl")
include("model.jl")
include("weights.jl")

end # module
