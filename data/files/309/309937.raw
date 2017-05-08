module DictIO

export writedict, readdict

"Save the type and data of the passed dictionary as text."
function writedict(f::IOStream, dict::Dict)
    println(f, join(match(r"[A-z]+{([^,]+),([^}]+)}", string(typeof(dict))).captures, '\t'))
    for (k,v) in dict
        println(f, string(k)*"\t"*string(v))
    end
end
function writedict(fileName::AbstractString, dict::Dict)
    f = open(fileName, "w")
    writedict(f, dict)
    close(f)
end

"""
Read the type and data of the passed dictionary.

Numeric types are converted automatically, and string type are
preserved, but other types may fail to load.
"""
function readdict(f::IOStream; reversed=false)
    parts = split(strip(readline(f)), '\t')
    type1 = eval(parse(parts[1]))
    type2 = eval(parse(parts[2]))
    d = reversed ? Dict{type2,type1}() : Dict{type1,type2}()
    for line in eachline(f)
        k,v = split(strip(line), '\t', limit=2)
        if type1 <: Number
            k = parse(type1, k)
        end
        if type2 <: Number
            v = parse(type2, v)
        end

        reversed ? d[v] = k : d[k] = v
    end
    d
end
function readdict(fileName::AbstractString; reversed=false)
    f = open(fileName)
    d = readdict(f, reversed=reversed)
    close(f)
    d
end

end # module
