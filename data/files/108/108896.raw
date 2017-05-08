function findMatch(pattern::Regex, myString::AbstractString)
   if match(pattern, myString) == nothing
       return("")
   else
       return(myString)
   end
end
findMatch(pattern::Regex, mySymbol::Symbol) = findMatch(pattern, string(mySymbol))


function queryColumns(pattern, col_names; logic = "", level = "outer")
    matches = Symbol[]
    if logic == "anti"
        op = ==
    else
        op = !=
    end

    #Return the whole string (outer), the actual match(inner), or the nth element of a split?
    if level == "inner"
        extract(pattern, s) = symbol(match(pattern, s).match)
    #nth half
    elseif typeof(level) == Int
        extract(pattern, s) = split(s, pattern)[level]
    #Outer
    else
        extract(pattern, s) = symbol(s)
    end

    for s in col_names
        s = string(s)
        if op(findMatch(pattern, s), "")
            push!(matches, extract(pattern, s))
        end
    end
    return(matches)
end
queryColumns(pattern, table::DataFrame; logic = "", level = "outer") = queryColumns(pattern, String[string(name) for name in names(table)]; logic = logic, level = level)
