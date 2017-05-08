SetCardType = CardType{:set}()
typealias SetCard NastranCard{SetCardType}

type AEFACT <: SetCard
    id::Int64
    factors::Vector{Float64}
end
function convert(::Type{AEFACT},card)
    id = card[2]::Int64
    i_br = 0
    for (i,f) in enumerate(card[3:end])
        if f == ""
            if i_br == 0
                i_br = i + 1
            end
        elseif i_br != 0
            throw(ExceptionError("Embedded blanks not allowed in AEFACT"))
        elseif typeof(f) != Float64
            throw(ExceptionError("AEFACT factors must be floats"))
        end
    end
    if i_br == 0
        factors = card[3:end]
    else
        factors = card[3:i_br]
    end
    AEFACT(id,factors)
end

type SET1 <: SetCard
    id::Int64
end
function convert(::Type{SET1},card)
    SET1(card[2]::Int64)
end

type AELIST <: SetCard
    id::Int64
end
function convert(::Type{AELIST},card)
    AELIST(card[2]::Int64)
end
