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

type PSHELL <: PropertyCard
    id::Int64
    mat1_id::Int64
    thickness::Nullable{Float64}
    nonstructural_mass::Float64
end
function convert(::Type{PSHELL},card)
    id = card[2]::Int64
    mat1_id = card[3]::Int64
    thickness = card[4] == "" ? Void : card[4]::Float64
    nonstructural_mass = card[9] == "" ? 0.0 : card[9]::Float64
    PSHELL(id,mat1_id,thickness,nonstructural_mass)
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

type PROD <: PropertyCard
    id::Int64
    mat_id::Int64
    A::Float64
    J::Float64
    C::Float64
    nonstructural_mass::Float64
end
function convert(::Type{PROD},card)
    id = card[2]::Int64
    mat_id = card[3]::Int64
    A = card[4]::Float64
    J = card[5]::Float64
    C = card[6] == "" ? 0.0 : card[6]::Float64
    nonstructural_mass = card[7] == "" ? 0.0 : card[7]::Float64
    PROD(id,mat_id,A,J,C,nonstructural_mass)
end

type CBUSH <: ElementCard
    id::Int64
end
function convert(::Type{CBUSH},card)
    id = card[2]::Int64
    CBUSH(id)
end

type PBUSH <: PropertyCard
    id::Int64
end
function convert(::Type{PBUSH},card)
    id = card[2]::Int64
    PBUSH(id)
end

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

type PBEAM <: PropertyCard
    id::Int64
    mat_id::Int64
    nonstructural_mass::Float64
    nonstructural_inertiaA::Float64
    nonstructural_inertiaB::Float64
end

is_continuation(field) = field == "YES"
is_double_continuation(field) = field == "YESA" || field == "NO"
function convert(::Type{PBEAM},card)
    id = card[2]::Int64
    mat_id = card[3]::Int64
    nonstructural_mass = card[9] == "" ? 0.0 : card[9]::Float64
    nonstructural_inertiaA = 0.0
    nonstructural_inertiaB = 0.0
    i = 10
    while i < length(card)
        if is_continuation(card[i])
        elseif is_double_continuation(card[i])
            i += 8
        else
            if card[i+4] != ""
                nonstructural_inertiaA = card[i+4]::Float64
            end
            if card[i+5] != ""
                nonstructural_inertiaB = card[i+5]::Float64
            end
        end
        i += 8
    end
    PBEAM(id,mat_id,nonstructural_mass,nonstructural_inertiaA,nonstructural_inertiaB)

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

type PELAS <: PropertyCard
    id::Int64
end
function convert(::Type{PELAS},card)
    id = card[2]::Int64
    PELAS(id)
end

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

type CONM2 <: ElementCard
    id::Int64
    grid_id::Int64
    csys_id::Int64
    mass::Float64
    x::Float64
    y::Float64
    z::Float64
end
function convert(::Type{CONM2},card)
    id = card[2]::Int64
    grid_id = card[3]::Int64
    csys_id = card[4] == "" ? 0 : card[4]::Int64
    mass = card[5]::Float64
    x = card[6] == "" ? 0.0 : card[6]::Float64
    y = card[7] == "" ? 0.0 : card[7]::Float64
    z = card[8] == "" ? 0.0 : card[8]::Float64
    CONM2(id,grid_id,csys_id,mass,x,y,z)
end

type SPOINT <: GridCard
    id::Int64
end
function convert(::Type{SPOINT},card)
    id = card[2]::Int64
    SPOINT(id)
end

type MPC <: ConstraintCard
    id::Int64
end
function convert(::Type{MPC},card)
    id = card[2]::Int64
    MPC(id)
end
