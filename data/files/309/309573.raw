CoordinateSystemCardType = CardType{:coordinate_system}()
typealias CoordinateSystemCard NastranCard{CoordinateSystemCardType}

type CORD1R <: CoordinateSystemCard
    id::Int64
    gridA::Int64
    gridB::Int64
    gridC::Int64
end
function convert(::Type{CORD1R},card)
    CORD1R(card[2]::Int64,
           card[3]::Int64,
           card[4]::Int64,
           card[5]::Int64)
end

type CORD2R <: CoordinateSystemCard
    id::Int64
    csys_id::Int64
    gridAx::Float64
    gridAy::Float64
    gridAz::Float64
    gridBx::Float64
    gridBy::Float64
    gridBz::Float64
    gridCx::Float64
    gridCy::Float64
    gridCz::Float64
end
function convert(::Type{CORD2R},card)
    CORD2R(card[2]::Int64,
           card[3] == "" ? 0 : card[3]::Int64,
           card[4]::Float64,
           card[5]::Float64,
           card[6]::Float64,
           card[7]::Float64,
           card[8]::Float64,
           card[9]::Float64,
           card[10]::Float64,
           card[11]::Float64,
           card[12]::Float64)
end
