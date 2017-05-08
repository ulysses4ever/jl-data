
import Base: done, next, repeat, start

repeat(c::Char, i::Integer) = repeat(string(c), i)

immutable Homocount{I}
    itr::I
end

homocount(itr) = Homocount(itr)
start(h::Homocount) = start(h.itr)

function next(h::Homocount, s)
    u, s = next(h.itr, s)
    c = 1
    while !done(h.itr, s)
        v, t = next(h.itr, s)
        if u != v
            break
        end
        c += 1
        s = t
    end
    ((u, c), s)
end

done(h::Homocount, s) = done(h.itr, s)
