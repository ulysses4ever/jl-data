module EscapeString

using HttpCommon

export escapestring


# Registry of available output formats and their handlers
formats = Dict{Symbol, Function}()
formats[:html_text] = escapeHTML



"Escapes string s to format fmt."
function escapestring(s::AbstractString, fmt::Symbol)
    formats[fmt](s)
end


end # module
