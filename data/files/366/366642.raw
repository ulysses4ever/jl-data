ElementCardType = CardType{:element}()
typealias ElementCard NastranCard{ElementCardType}

type CBEAM <: ElementCard
    id::Int64
    prop_id::Int64
end
function convert(::Type{CBEAM},card)
    id = card[2]::Int64
    prop_id = card[3]::Int64
    CBEAM(id,prop_id)
end

type CTRIAR <: ElementCard
    id::Int64
    prop_id::Int64
    thickness1::Nullable{Float64}
    thickness2::Nullable{Float64}
    thickness3::Nullable{Float64}
end
function convert(::Type{CTRIAR},card)
    id = card[2]::Int64
    prop_id = card[3] == "" ? id : card[3]::Int64
    tflag = 0
    thickness1 = nothing
    thickness2 = nothing
    thickness3 = nothing
    if length(card) > 10
        tflag = card[11] == "" ? 0 : card[11]::Int64
        thickness1 = card[12] == "" ? nothing : card[12]::Float64
        thickness2 = card[13] == "" ? nothing : card[13]::Float64
        thickness3 = card[14] == "" ? nothing : card[14]::Float64
    else
    end
    CTRIAR(id,prop_id,thickness1,thickness2,thickness3)
end

type CQUADR <: ElementCard
    id::Int64
    prop_id::Int64
end
function convert(::Type{CQUADR},card)
    id = card[2]::Int64
    prop_id = card[3]::Int64
    CQUADR(id,prop_id)
end

type CROD <: ElementCard
    id::Int64
    prop_id::Int64
end
function convert(::Type{CROD},card)
    id = card[2]::Int64
    prop_id = card[3] == "" ? id : card[3]::Int64
    CROD(id,prop_id)
end

type CBUSH <: ElementCard
    id::Int64
end
function convert(::Type{CBUSH},card)
    id = card[2]::Int64
    CBUSH(id)
end

type RBE2 <: ElementCard
    id::Int64
end
function convert(::Type{RBE2},card)
    id = card[2]::Int64
    RBE2(id)
end

type RBE3 <: ElementCard
    id::Int64
end
function convert(::Type{RBE3},card)
    id = card[2]::Int64
    RBE3(id)
end

type CELAS1 <: ElementCard
    id::Int64
end
function convert(::Type{CELAS1},card)
    id = card[2]::Int64
    CELAS1(id)
end

type CELAS2 <: ElementCard
    id::Int64
end
function convert(::Type{CELAS2},card)
    id = card[2]::Int64
    CELAS2(id)
end

type CONM2 <: ElementCard
    id::Int64
    grid_id::Int64
    csys_id::Int64
    mass::Float64
    x::Float64
    y::Float64
    z::Float64
    I11::Float64
    I21::Float64
    I22::Float64
    I31::Float64
    I32::Float64
    I33::Float64
end
function convert(::Type{CONM2},card)
    id = card[2]::Int64
    grid_id = card[3]::Int64
    csys_id = card[4] == "" ? 0 : card[4]::Int64
    mass = card[5]::Float64
    x = card[6] == "" ? 0.0 : card[6]::Float64
    y = card[7] == "" ? 0.0 : card[7]::Float64
    z = card[8] == "" ? 0.0 : card[8]::Float64
    I11 = I21 = I22 = I31 = I32 = I33 = 0.0
    if length(card) > 9
        I11 = card[10] == "" ? 0.0 : card[10]::Float64
        I21 = card[11] == "" ? 0.0 : card[11]::Float64
        I22 = card[12] == "" ? 0.0 : card[12]::Float64
        I31 = card[13] == "" ? 0.0 : card[13]::Float64
        I32 = card[14] == "" ? 0.0 : card[14]::Float64
        I33 = card[15] == "" ? 0.0 : card[15]::Float64
    end
    CONM2(id,grid_id,csys_id,mass,x,y,z,I11,I21,I22,I31,I32,I33)
end

type CAERO1 <: ElementCard
    id::Int64
end
function convert(::Type{CAERO1},card)
    id = card[2]::Int64
    CAERO1(id)
end

type SPLINE1 <: ElementCard
    id::Int64
end
function convert(::Type{SPLINE1},card)
    id = card[2]::Int64
    SPLINE1(id)
end

type SPLINE2 <: ElementCard
    id::Int64
end
function convert(::Type{SPLINE2},card)
    id = card[2]::Int64
    SPLINE2(id)
end
