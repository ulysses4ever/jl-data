abstract Groups

typealias GRanges Vector{Range1{Int}}


type FixedGroups <: Groups
    titles::Vector{Symbol}
    sizes::Vector{Int}

    FixedGroups(titles::Vector{Symbol}, sizes::Vector{Int}) =
        length(titles) == length(sizes) ?
            new(titles, sizes) : error("Argument lengths don't match.")
end

function groups2ranges(g::FixedGroups)
    p = 0
    Range1{Int}[(p + 1):(p = p + s) for s=g.sizes]
end
