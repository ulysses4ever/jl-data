module Nastran

import Base: show, +

using ImmutableArrays

export NastranDeck, GenericNastranDeck, NastranModel
export CBEAM, CONM2, CELAS1, CQUADR, CTRIAR, CELAS2, RBE2, RBE3, CBUSH, CROD
export CoordSet,get_coord,get_global_xyz

typealias GenericCard Vector{Any}
typealias GenericNastranDeck Vector{GenericCard}

abstract NastranCard{CardType}

immutable CardType{T} end

ElementCardType = CardType{:element}()
typealias ElementCard NastranCard{ElementCardType}

PropertyCardType = CardType{:property}()
typealias PropertyCard NastranCard{PropertyCardType}

MaterialCardType = CardType{:material}()
typealias MaterialCard NastranCard{MaterialCardType}

GridCardType = CardType{:grid}()
typealias GridCard NastranCard{GridCardType}

ConstraintCardType = CardType{:constraint}()
typealias ConstraintCard NastranCard{ConstraintCardType}

CoordinateSystemCardType = CardType{:coordinate_system}()
typealias CoordinateSystemCard NastranCard{CoordinateSystemCardType}

typealias NastranDeck Vector{NastranCard}

include("cards.jl")
include("coords.jl")
include("masscg.jl")
include("deck.jl")
include("model.jl")
include("weights.jl")

end # module
