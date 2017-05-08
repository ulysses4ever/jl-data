GridCardType = CardType{:grid}()
typealias GridCard NastranCard{GridCardType}

type GRID <: GridCard
    id::Int64
    csys_id::Int64
    x::Float64
    y::Float64
    z::Float64
end
function convert(::Type{GRID},card)
    id = card[2]::Int64
    csys_id = card[3] == "" ? 0 : card[3]::Int64
    x = card[4] == "" ? 0.0 : card[4]::Float64
    y = card[5] == "" ? 0.0 : card[5]::Float64
    z = card[6] == "" ? 0.0 : card[6]::Float64
    GRID(id,csys_id,x,y,z)
end

type SPOINT <: GridCard
    id::Int64
end
function convert(::Type{SPOINT},card)
    id = card[2]::Int64
    SPOINT(id)
end
