
abstract Algorithm

type Direct <: Algorithm
    board_size::Int
    max_moves::Int
    rng::AbstractRNG
end

function srand(d::Direct, n)
#    println("seed $n")
    d.rng = MersenneTwister(n)
end

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

function board_display(p, x, y)
    t = point(p, x, y)
    @printf("\n\n%s at (%d,%d)\n", t == black ? "black" : "white", x, y)
    println(join(fmtpoint(p.board), "\n"))
end


# for replay, pick a game from the log.  perhaps
# 1000/1000   6/20   ceaa93b88f34d14f:1   bt fb9b4e8b26cd7702:3    9 sc   81 mv   4 sp  70 st
# and calculate the seed.  in this case (1000-1)*20+6
# the read in the population and replay:
# > d = undump("evol-1.dump");
# > replay_direct(d["ceaa93b88f34d14f"], d["fb9b4e8b26cd7702"], 9, 81, 20*999+6)
# note that the higher ranked net plays first (as black), so if the result is a surprise
# (with a !) then the order of the nets must be reversed from the log.

function replay_direct(a::Vector{UInt8}, b::Vector{UInt8}, n, max, seed)
    p = play(a, b, Direct(n, max, MersenneTwister(seed)), board_display)
    println("\n\nfinal position:")
    println(p)
end
