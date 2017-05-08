import JSON
 
function tparse{T}(::Type{T}, json::String)
    return eval(parse(json))::T
end
 
function tparse(::Type{DataType}, json::String)
    eval(symbol(json))::DataType
end
 
function tparse{T}(::Type{Dict{String,T}}, json::Dict{String,Any})
    r = Dict{String,T}()
    for (n, d) = json
        r[n] = tparse(T, d)
    end
    r
end
 
function tparse(typ::DataType, json::Dict{String,Any})
    r = typ()
    for (n, d) = json
        s = symbol(n)
        t = typ.types[findfirst(typ.names, s)]
        setfield(r, s, tparse(t, d))
    end
    r
end
 
# define our types
type DefB
    datatype::DataType
    unique::Bool
    DefB() = new(Any, false) # default values
end
 
type DefA
    childAs::Dict{String, DefA}
    childBs::Dict{String, DefB}
    
    DefA() = new(Dict{String, DefA}(), Dict{String, DefB}())
end
 
# a sample JSON document
json = """
{
    "childAs":
    {
        "z": {},
        "x":
        {
            "childBs":
            {
                "b1": { "datatype": "Int", "unique": "false" },
                "b2": { "datatype": "String", "unique": "false" }
            }
        }
    },
    "childBs":
    {
        "b3": { "datatype": "Int32", "unique": "false" },
        "b4" :{ "datatype": "String", "unique": "false" }
    }
}"""
 
# go
tparse(DefA, JSON.parse(json))