
abstract Algorithm

type Direct <: Algorithm
    board_size::Int
    max_moves::Int
    rng::AbstractRNG
end

srand(d::Direct, n) = d.rng = MersenneTwister(n)

function play(a::Vector{UInt8}, b::Vector{UInt8}, d::Direct, display)
    passed, t, p = 0, black, Position{d.board_size}()
    while passed < 2 && p.score.moves < d.max_moves
        m = moves(a, p, t, d.rng)
        if length(m) == 0
            passed += 1
        else
            p = move!(p, t, m[1]...)
            display(p, m[1]...)
            passed = 0
        end
        a, b, t = b, a, other(t)
    end
    p
end

null_display(p, x, y) = nothing
