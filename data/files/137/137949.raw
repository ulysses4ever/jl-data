
import Base: done, next, repeat, start

repeat(c::Char, i::Integer) = repeat(string(c), i)

immutable Homocount{I}
    itr::I
end

homocount(itr) = Homocount(itr)
start(h::Homocount) = (1, start(h.itr))

function next(h::Homocount, state)
    u, s = next(h.itr, state[2])
    c = 1
    while !done(h.itr, s)
        v, t = next(h.itr, s)
        if u != v
            break
        end
        c += 1
        s = t
    end
    ((u, c), (state[1] + 1, state[2] + c))
end

done(h::Homocount, s) = done(h.itr, s[2])
