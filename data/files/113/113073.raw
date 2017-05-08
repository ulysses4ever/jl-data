module URLUtils

# from: https://github.com/JuliaWeb/HttpCommon.jl/blob/release-0.3/src/HttpCommon.jl

# All characters that remain unencoded in URI encoding
#                                   ( AKA URL encoding
#                                     AKA percent-encoding )
#
const URIwhitelist = Set(Any['A','B','C','D','E','F','G','H','I',
                         'J','K','L','M','N','O','P','Q','R',
                         'S','T','U','V','W','X','Y','Z',
                         'a','b','c','d','e','f','g','h','i',
                         'j','k','l','m','n','o','p','q','r',
                         's','t','u','v','w','x','y','z',
                         '0','1','2','3','4','5','6','7','8',
                         '9','-','_','.','~'])

# decodeURI
#
# Decode URI encoded strings
#
function decodeURI(encoded::String)
    enc = split(replace(encoded,"+"," "),"%")
    decoded = enc[1]
    for c in enc[2:end]
        decoded = @compat string(decoded, Char((parse(Int, c[1:2], 16))),
                                 c[3:end])
    end
    decoded
end

# encodeURI
#
# Convert strings to URI encoding
#
function encodeURI(decoded::String)
    encoded = ""
    for c in decoded
        encoded = @compat encoded * string(c in URIwhitelist ? c :
                                           "%" * uppercase(hex(Int(c))))
    end
    encoded
end

# parsequerystring
#
# Convert a valid querystring to a Dict:
#
#    q = "foo=bar&baz=%3Ca%20href%3D%27http%3A%2F%2Fwww.hackershool.com%27%3Ehello%20world%21%3C%2Fa%3E"
#    parsequerystring(q)
#    # => Dict("foo"=>"bar","baz"=>"<a href='http://www.hackershool.com'>hello world!</a>")
#
function parsequerystring(query::String)
    q = Dict{String,String}()
    if !('=' in query)
        return throw("Not a valid query string: $query, must contain at least one key=value pair.")
    end
    for set in split(query, "&")
        key, val = split(set, "=")
        q[decodeURI(key)] = decodeURI(val)
    end
    q
end

end # module
