MaterialCardType = CardType{:material}()
typealias MaterialCard NastranCard{MaterialCardType}

type MAT1 <: MaterialCard
    id::Int64
    E::Float64
    G::Float64
    NU::Float64
    rho::Float64
end
function convert(::Type{MAT1},card)
    id = card[2]::Int64
    E = card[3] == "" ? 0 : card[3]::Float64
    G = card[4] == "" ? 0.0 : card[4]::Float64
    NU = card[5] == "" ? 0.0 : card[5]::Float64
    rho = card[6] == "" ? 0.0 : card[6]::Float64
    MAT1(id,E,G,NU,rho)
end
