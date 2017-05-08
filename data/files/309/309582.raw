PropertyCardType = CardType{:property}()
typealias PropertyCard NastranCard{PropertyCardType}

type PSHELL <: PropertyCard id::Int64
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

type PBUSH <: PropertyCard
    id::Int64
end
function convert(::Type{PBUSH},card)
    id = card[2]::Int64
    PBUSH(id)
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

type PELAS <: PropertyCard
    id::Int64
end
function convert(::Type{PELAS},card)
    id = card[2]::Int64
    PELAS(id)
end
