
typealias Chars Union(Char,AbstractVector{Char},Set{Char})

# search in a string from the reverse direction
function rsearch(s::String, c::Chars, i::Integer)
    l = length(s)
    ret = search(reverse(s), c, l-i+1)
    (0 == ret) ? 0 : (l-ret+1)
end
rsearch(s::String, c::Chars) = rsearch(s,c,endof(s))

function rsearch(s::String, t::String, i::Integer)
    l = length(s)
    r = search(reverse(s), reverse(t), l-i+1)
    (0 == r.start) ? r : Range1(l-r.start-r.len+2, r.len)
end
rsearch(s::String, t::String) = rsearch(s,t,endof(s))

function rsplit(str::String, splitter, limit::Integer, keep_empty::Bool)
    strs = String[]
    i = start(str)
    n = endof(str)
    r = rsearch(str,splitter,n)
    j = first(r)-1 
    k = last(r)
    while((0 <= j < n) && (length(strs) != limit-1))
        if(i <= k)
            (keep_empty || (k < n)) && unshift!(strs, str[k+1:n])
            n = j
        end
        (k <= j) && (j = prevind(str,j))
        r = rsearch(str,splitter,j)
        j = first(r)-1
        k = last(r)
    end
    (keep_empty || (n > 0)) && unshift!(strs, str[1:n])
    return strs
end
rsplit(s::String, spl, n::Integer) = rsplit(s, spl, n, true)
rsplit(s::String, spl, keep::Bool) = rsplit(s, spl, 0, keep)
rsplit(s::String, spl)             = rsplit(s, spl, 0, true)

const _default_delims = [' ','\t','\n','\v','\f','\r']
rsplit(str::String) = rsplit(str, _default_delims, 0, false)

