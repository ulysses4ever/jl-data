"Encode n things using integers 1:n"
type LabelEncoder{T}
    label::Vector{T}
    index::Dict{T,Int}
end

LabelEncoder(T::Type) = LabelEncoder(T[], Dict{T,Int}())

Base.length(lmap::LabelEncoder) = length(lmap.label)

function add!{T}(lmap::LabelEncoder{T}, label::T)
    if !haskey(lmap.index, label)
        push!(lmap.label, label)
        lmap.index[label] = length(lmap.label)
    end
end

function LabelEncoder{T}(labels::Vector{T})
    lmap = LabelEncoder(T)
    for label in labels
        add!(lmap, label)
    end
    return lmap
end

encode{T}(lmap::LabelEncoder{T}, label::T) = lmap.index[label]

decode(lmap::LabelEncoder, i::Int) = lmap.label[i]
