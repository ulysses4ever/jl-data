module EscapeString

import HttpCommon.escapeHTML

export escapestring


"Escapes string s to formt fmt."
function escapestring(s::AbstractString, fmt::Symbol)
    result = ""
    if fmt == :html_text
        result = escapeHTML(s)
    else
        error("Unrecognized format $fmt.")
    end
    result
end


end # module
