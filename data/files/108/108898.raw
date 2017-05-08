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

#Convert a string of booleans to an array of 0 and 1
function convertPattern(a::AbstractString)
    pat = []
    for c in a
        if c == '0'
            pat = [pat; [0]]
        elseif c == '1'
            pat = [pat; [1]]
        end
    end
    return(pat)
end
#Convert an array of 0 and 1 to a string of booleans
function convertPattern(a::DataArray{Bool})
    pat = ""
    for c in a
        pat = pat * string(convert(Int, c))
    end
    return(pat)
end
