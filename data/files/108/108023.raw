#!/usr/bin/env julia
import Base.length

type IndexedString
    string_array::Array{String, 1}
end

IndexedString(s::String) = IndexedString(parse_string_to_array(s))

function parse_string_to_array(s::String)
    regex = r"[A-Za-z0-9]+"
    words = matchall(regex, s)
    return String[string(word) for word in words]
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
    
