
# this file used something like:

# julia-0.4 -e 'using Go; d = undump("evol-1.dump")[1]; replay_direct(d, "514/10000  13/25   cb91577f4ddb175e:1   bt e7d7a5f40ef149a5:2    3 sc  356 mv  24 sp  337 st")'

# where the quoted string is cut+paste from the log


# here, a plays first (black)
function play(a::Vector{UInt8}, b::Vector{UInt8}, board_size, max_moves, display_move, display_pass)
    passed, t, h = 0, black, [Position{board_size}()]
    # white must pass last
    while (passed < 2 || t == white) && h[end].stats.moves < max_moves
        played = false
        for m in moves(a, h, t)
            p = Position(h[end])
            move!(p, t, m...)
            if length(filter(x -> x.board == p.board, h)) > 0
                println("repeated position")
            else
                push!(h, p)
                display_move(p, m...)
                played = true
                break
            end
        end
        if played
            passed = 0
        else
            passed += 1
            push!(h, pass!(t, Position(h[end])))
            display_pass(h[end], t)
        end
        a, b, t = b, a, other(t)
    end
    h[end]
end

null_display(p, x, y) = nothing
null_display(p, t) = nothing

function board_display(p, x, y)
    t = point(p, x, y)
    @printf("\n\n%d (%3.1f): %s at (%d,%d)\n", p.stats.moves, p.stats.score, t == black ? "black" : "white", x, y)
    println(join(fmtpoint(p.board), "\n"))
end

function pass_display(p, t)
    @printf("\n\n%d (%3.1f): %s pass\n", p.stats.moves, p.stats.score, t == black ? "black" : "white")
end

# for replay, pick a game from the log.  perhaps
# 1000/1000   6/20   ceaa93b88f34d14f:1   bt fb9b4e8b26cd7702:3    9 sc   81 mv   4 sp  70 st
# and calculate the seed.  in this case (1000-1)*20+6
# the read in the population and replay:
# > d = undump("evol-1.dump");
# > replay_direct(d["ceaa93b88f34d14f"], d["fb9b4e8b26cd7702"], 9, 81, 20*999+6)

function replay_direct(a::Vector{UInt8}, b::Vector{UInt8}, board_size, max_moves)
    p = play(a, b, board_size, max_moves, board_display, pass_display)
    println("\n\nfinal position:")
    println(p)
    p
end

function replay_direct(d::Dict{AbstractString, Vector{UInt8}}, line::AbstractString; board_size=19, max_moves=1000)
# 50/10000  10/25 ! 8414ac2df622accd:38  bt c340be963d5fc19f:5   14 sc  100 mv   5 sp  67 st
# 50/10000  11/25   c340be963d5fc19f:6   bt 6b34dd72635a19e6:19   2 sc   45 mv   6 sp  45 st   
    p = r"^\s*(?P<i>\d+)/(?P<n>\d+)\s+(?P<j>\d+)/(?P<m>\d+) (?P<surprise>(?:!| )) (?P<a>[a-f0-9]+):\d+\s+(?:>|=|<)\s+(?P<b>[a-f0-9]+):\d+.*$"
    m = match(p, line)
    println(m.captures)
    i, n, j, m, surprise, a, b = m.captures
    seed = (parse(Int, i)-1) * parse(Int, m) + parse(Int, j)
    println("$a v $b (seed $(seed))")
    replay_direct(d[a], d[b], board_size, max_moves)
end

function replay_pair(path, a, b; board_size=19, max_moves=1000)
    d = undump(path)[1]
    replay_direct(d[a], d[b], board_size, max_moves)
end

function replay_latest(; log_path="evol-2.log", dump_path="evol-2.dump", 
                       a=1, b=2, n=100, fraction=0.9,
                       board_size=19, max_moves=1000)
    events = parse_log(log_path, dump_path, n, fraction)
    popn = Vector{Vector{Individual}}()
    for e in events
        expand!(popn, e)
    end
    named = undump(dump_path)[1]
    ea, eb = named[popn[end][a].tag], named[popn[end][b].tag]
    if ea > eb
        ea, eb = eb, ea
        a, b = b, a
    end
    println("black: $(name(ea)):$(a); white: $(name(eb)):$(b)\n")
    replay_direct(ea, eb, board_size, max_moves)
end
