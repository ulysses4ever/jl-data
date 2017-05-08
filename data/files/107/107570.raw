
function play_direct(a::Vector{UInt8}, b::Vector{UInt8}, n, limit; seed=1)
    rng, passed, t, p = MersenneTwister(seed), 0, black, Position{n}()
    while passed < 2 && p.score.moves < limit
        m = moves(a, p, t, rng)
        if length(m) == 0
            passed += 1
        else
            p = move!(p, t, m[1]...)
            passed = 0
        end
        a, b, t = b, a, other(t)
    end
    p
end
