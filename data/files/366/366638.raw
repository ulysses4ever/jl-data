ConstraintCardType = CardType{:constraint}()
typealias ConstraintCard NastranCard{ConstraintCardType}

type MPC <: ConstraintCard
    id::Int64
end
function convert(::Type{MPC},card)
    id = card[2]::Int64
    MPC(id)
end