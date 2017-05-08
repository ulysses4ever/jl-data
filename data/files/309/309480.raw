abstract Scale


typealias EvenScales Vector{Scale}
typealias WeightedScales Vector{(Scale, Int)} # maybe...

typealias Scales Union(EvenScales, WeightedScales)


abstract Cardinal <: Scale

type CardinalVector <: Cardinal
    data::Vector
end
type CardinalData <: Cardinal
    data::DataVector
end

cardinal(v::Vector) = CardinalVector(v ./ std(v))
cardinal(v::DataVector) = CardinalData(v ./ std(dropna(v)))


abstract Nominal <: Scale

type FixedNominal <: Nominal
    data::Vector
    range::Range1
    counts::Vector{Vector{Float64}}

    function FixedNominal(v::AbstractVector, g::Groups)
        refs = pdata(isa(v, PooledDataArray) ? data(v) : v).refs
        rmin, rmax = extrema(refs)
        r = Range1(rmin, rmax-rmin+1)
        c = expected_counts(refs, r, g)
        new(refs, r, c)
    end
end

function expected_counts(v::AbstractVector, r::Range1, g::FixedGroups)
    props = proportions(v, r)
    minimum(props) * minimum(g.sizes) < 5 && warn("Expected counts < 5")
    [props .* s for s=g.sizes]
end

nominal(v::AbstractVector, g::FixedGroups) = FixedNominal(v, g)


function prepdata(df::DataFrame, g::Groups)
    ret = Array(Scale, 0)

    for (colname, col) in eachcol(df)
        eltyp = eltype(col)

        if eltyp == Bool || eltyp <: String
            push!(ret, nominal(col, g))
        elseif eltyp <: Real
            v = col
            if isa(col, AbstractDataArray)
                if anyna(col)
                    push!(ret, nominal(isna(col), g))
                else
                    v = dropna(col)
                end
            end

            push!(ret, cardinal(v))
        else
            throw(ArgumentError("Column ($colname) has unexpected eltype ($eltyp)."))
        end
    end

    ret
end
