# Cuts off `str` to a maximum actual `width`. Does handle unicode strings.
# If `str` is too wide and `dots` is true, the last character will be an ellipsis.
function strcut(str, width; dots::Bool=true)
    w = strwidth(str)
    if w <= width
        return str
    elseif w == length(str)
        # No unicode-stuff to care about, should be the most common case for labels.
        if dots
            return str[1:min(end,width-1)] * "…"
        else
            return str[1:min(end,width)]
        end
    else
        # Handle unicode where a char may have any width.
        i = 1; w = 0
        cw = charwidth(str[i])
        while (w + cw < width + !dots) && nextind(str, i) <= endof(str)
            w += cw
            i = nextind(str, i)
            cw = charwidth(str[i])
        end
        return str[1:i-1] * (dots ? "…" : "")
    end
end
