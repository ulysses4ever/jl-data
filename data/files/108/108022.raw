#!/usr/bin/env julia
import Base.length

type IndexedString
    string_array::Array{String, 1}
end

IndexedString(s::String) = IndexedString(parse_string_to_array(s))

function parse_string_to_array(s::String)
    current = 1
    words = String[]
    while current <= length(s)
        regex = r"[A-Za-z0-9]+"
        word = match(regex, s, current)
        if word == nothing
            break
        else
            push!(words, word.match)
            current = word.offset + length(word.match)
        end
    end
    return words
end


function getindex(s::IndexedString, index::Integer)
    if index <= 0 || index > length(s)
        return ""
    end
    return s.string_array[index]
end

function length(s::IndexedString)
    return Base.length(s.string_array)
end
    
