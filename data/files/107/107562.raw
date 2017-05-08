
# this file used something like:

# julia-0.4 -e 'using Go; e = parse_log("evol-1.log", "evol-1.dump", 50, 0.5; limit=-1); plot_tramlines(e, "go.png"; min_axis=1900, tint=ancestors("05f051414412588b"))'

# where the ancestors tag is typically a recent, high scoring individual


const p_challenge = r"^\s*(?P<i>\d+)/(?P<n>\d+)\s+(?P<j>\d+)/(?P<m>\d+) (?P<surprise>(?:!| )) (?P<a>[a-f0-9]+):(?P<x>\d+)\s+(?:>|=|<)\s+(?P<b>[a-f0-9]+):(?P<y>\d+).*$"

# 34 random bytes d1862e709058196a => fddd8634d3f25690
# 30 random bits 755e948bc02367be => d68ad2353d0c378a
const p_random = r"^\s*\d+ random (?:bits|bytes|deltas) (?P<a>[a-f0-9]+) => (?P<c>[a-f0-9]+)\s*$"

# rotate 262 cb03e03f73d749c2 => 326e568542888c67 + merge 123 326e568542888c67, fddd8634d3f25690 => f2b69ec0fe5c1fd7
# rotate chunk 7 0043f8c791de1a53 => 0bf67111a514bd9d + merge 97 f7e67544a9a5ef3c, 0bf67111a514bd9d => da7fc58918b190c0
const p_rotate = r"^\s*rotate (?:chunk )?\d+ (?P<a>[a-f0-9]+) => (?P<x>[a-f0-9]+) \+ merge \d+ (?P<y>[a-f0-9]+), (?P<z>[a-f0-9]+) => (?P<c>[a-f0-9]+)\s*$"

# merge 264 0f9139cba0588c2a, d9a5f3b8d06028d9 => 9b6504a9fe224d56
const p_merge = r"^\s*merge \d+ (?P<a>[a-f0-9]+), (?P<b>[a-f0-9]+) => (?P<c>[a-f0-9]+)\s*$"

# temp 0.819
const p_temp = r"\s*temp \d+\.\d+\s*$"

const INK = C.RGB(0.2, 0.2, 0.2)
const PEN = 0.45

# this is not hashed - each instance is unique, and we can have
# multiple, distinct instances with the same tag.
type Individual
    tag::AbstractString
end

abstract Event

immutable VirginBirths <: Event
    ids::Vector{Individual}
end

type Birth <: Event
    id::Individual
    parents::Vector{Individual}
    deaths::Vector{Individual}
    Birth(id, parents) = new(id, parents, Individual[])
end

abstract Challenge <: Event

immutable FailedChallenge <: Challenge
    won::Individual
    lost::Individual
end

type SuccessfulChallenge <: Challenge
    won::Individual
    lost::Individual
    deaths::Vector{Individual}
    SuccessfulChallenge(won, lost) = new(won, lost, Individual[])
end

immutable Deaths <: Event
    ids::Vector{Individual}
    Deaths(ids::Vector{Individual}) = new(ids)
    Deaths(id::Individual) = new(Individual[id])
end

delete!(v::Vector, i::Integer) = splice!(v, i:i)

function prune!(events, id)

    death = Nullable{Event}()
    function clear_death()
        if ! isnull(death)
            delete!(get(death).deaths, findfirst(get(death).deaths, id))
        end
    end
    function set_death(e)
        clear_death()
        findfirst(e.deaths, id) == 0 && push!(e.deaths, id)
        death = Nullable{Event}(e)
    end

    deleted, positive, i, dies = 0, false, length(events), false
    for i = length(events):-1:1
        e = events[i]
        if isa(e, VirginBirths) && id in e.ids
            if ! positive && dies
                delete!(e.ids, findfirst(e.ids, id))
                deleted += 1
                clear_death()
            end
            return deleted
        elseif isa(e, Birth) && e.id == id
            if ! positive # && dies  so we clear out near start too
                events[i] = Deaths(e.deaths)
                deleted += 1
                clear_death()
            end
            return deleted
        elseif isa(e, Birth) && ! positive
            if dies
                set_death(e)
            end
            positive = id in e.parents
        elseif isa(e, SuccessfulChallenge) && e.won == id
            positive = true
        elseif isa(e, SuccessfulChallenge) && e.lost == id
            if ! positive && dies
                set_death(e)
            end
            positive = true
        elseif isa(e, SuccessfulChallenge) && ! positive && dies
            set_death(e)
        elseif isa(e, Deaths) && id in e.ids
            dies = true
        end
    end
    deleted
end

allids(e::VirginBirths) = e.ids
allids(e::Birth) = vcat(e.id, e.parents, e.deaths)
allids(e::Challenge) = vcat(e.won, e.lost, e.deaths)
allids(e::Deaths) = e.ids

function prune!(events)
    deleted, ids, i = 0, Set{Individual}(), length(events)
    while i > 0
        idcpy = collect(allids(events[i]))
        for id in idcpy
            if ! (id in ids)
                push!(ids, id)
                deleted += prune!(events, id)
            end
        end
        i = min(i-1, length(events))
    end
    println("deleted $(deleted) (from unsuccessful individuals)")
    deleted
end

function prune_type!(events, T)
    count = 0
    for i = length(events):-1:1
        if isa(events[i], T)
            delete!(events, i)
            count += 1
        end
    end
    println("deleted $(count) $(T)")
    events
end

parent(population, tag) = population[findfirst(id -> id.tag == tag, population)]

function parse_line(events, population, line, n, fraction)

#    println("$(length(population)) $(line)")

    if (m = match(p_challenge, line)) != nothing
        x, y = parse(Int, m[:x]), parse(Int, m[:y])
        a, b = population[x], population[y]
         @assert a.tag == m[:a]
        @assert b.tag == m[:b]
        # order so x/a is the higher rated
        if y < x
            x, y = y, x
            a, b = b, a
        end
        if m[:surprise] == "!"
            push!(events,  SuccessfulChallenge(b, a))
            population[x+1:y] = population[x:y-1]
            population[x] = b
        else
            push!(events, FailedChallenge(a, b))
        end
        return 1

    elseif (m = match(p_random, line)) != nothing
        parent1 = parent(population, m[:a])  # triggers error on initial junk
        push!(population, Individual(m[:c]))
        push!(events, Birth(population[end], [parent1]))
        return 1

    elseif (m = match(p_rotate, line)) != nothing
        parent1 = parent(population, m[:a])
        parent2 = parent(population, m[:x] == m[:y] ? m[:z] : m[:y])
        push!(population, Individual(m[:c]))
        push!(events, Birth(population[end], [parent1, parent2]))
        return 1

    elseif (m = match(p_merge, line)) != nothing
        parent1 = parent(population, m[:a])
        parent2 = parent(population, m[:b])
        push!(population, Individual(m[:c]))
        push!(events, Birth(population[end], [parent1, parent2]))
        return 1

    elseif match(p_temp, line) != nothing
        push!(events, Deaths(Individual[]))
        while length(population) > Int(fraction * n)
            id = pop!(population)
            push!(events[end].ids, id)
        end
        return 1

    else
        return 0
    end
end

function parse_log(log_path, dump_path, n, fraction; limit=-1)

    events, population = Vector{Event}(), Vector{Individual}()
    push!(events, VirginBirths(Individual[]))

    # take initial population from dump
    for expression in undump(dump_path)[2][1:n]
        push!(population, Individual(name(expression)))
        push!(events[1].ids, population[end])
    end

    open(log_path, "r") do io

        started = false

        for line in eachline(io)

            try
                if ! started
                    # discard any junk breeding
                    population = population[1:n]
                end
                k = parse_line(events, population, line[1:end-1], n, fraction)
                started = started || isa(events[end], Challenge)
                if started 
                    limit -= k
                    limit == 0 && break
                end
            catch
                if started
                    rethrow()
                end
            end

        end
    end

    println("initial $(length(events)) events")
    prune_type!(events, FailedChallenge)
    while prune!(events) > 0 end
    prune_type!(events, Deaths)
    println("final $(length(events)) events")

    events
end

typealias ColourTable Tuple{Int, C.Colorant}

type PlotState
    max_pop::Int
    rows::Int
    cols::Int
    row::Int
    col::Int
    colour_index::Dict{Individual, Tuple{Int,Int,Int}}
    colour_table::Dict{Int, C.Colorant}
    PlotState(max_pop, rows, cols) = new(max_pop, rows, cols, 0, 0,
                                         Dict{Individual, Tuple{Int,Int,Int}}(),
                                         Dict{Int, C.Colorant}())
end

show(io::IO, s::PlotState) = show(io, "PlotState($(s.max_pop),$(s.col)/$(s.cols),$(s.row)/$(s.rows))")

function expand!(p::Vector{Vector{Individual}}, e::Birth)
    popn = copy(p[end])
    push!(popn, e.id)
    for id in e.deaths
        i = findfirst(popn, id)
        i > 0 && delete!(popn, i)
    end
    push!(p, popn)
end

function expand!(p::Vector{Vector{Individual}}, e::VirginBirths)
    popn = isempty(p) ? Individual[] : copy(p[end])
    for id in e.ids
        push!(popn, id)
    end
    push!(p, popn)
end

function expand!(p::Vector{Vector{Individual}}, e::SuccessfulChallenge)
    popn = copy(p[end])
    i = findfirst(popn, e.lost)
    j = findfirst(popn, e.won)
    @assert i < j (i, j)
    popn[i+1:j] = popn[i:j-1]
    popn[i] = e.won
    for id in e.deaths
        i = findfirst(popn, id)
        i > 0 && delete!(popn, i)
    end
    push!(p, popn)
end

function expand!(p::Vector{Vector{Individual}}, e::FailedChallenge)
    popn = copy(p[end])
    push!(p, popn)
end

function make_state(events, ny, ratio, min_scale, min_axis)
    nx = length(events)
    rows = max(1, floor(Int, sqrt(nx * ny / ratio) / ny))
    cols = ceil(Int, nx / rows) + 1
    s = PlotState(ny, rows, cols)
    n = max(min_scale * cols, min_axis / 1.2)
    scale = n / cols
    m = scale * ny * rows + 0.2 * n
    n = n + 0.2 * n
    println("($(nx),$(ny)) -> $s, ($n, $m), $(scale)")
    s, n, m
end

function break!(e, p, s::PlotState)
    for i in 1:(s.rows-1)
        j = i*s.cols
        splice!(e, j:j-1, [VirginBirths(Individual[])])
        splice!(p, j:j-1, Vector{Individual}[p[j]])
    end
end

function getc(s, id, k)
    (b, kk, a) = s.colour_index[id]
    if k <= kk
        s.colour_table[b]
    else
        s.colour_table[a]
    end
end

function grey!(s, popn, events)
    s.colour_table[0] = INK
    for p in popn
        for id in p
            if ! haskey(s.colour_index, id)
                s.colour_index[id] = (0, 0, 0)
            end
        end
    end
end

function multi(s, popn, events)
    for p in popn
        for id in p
            if ! haskey(s.colour_index, id)
                n = length(s.colour_table) + 1
                s.colour_table[n] = convert(C.RGB{N.UFixed8}, C.HSV(360 * rand(), 0.5 + 0.5 * rand(), 0.2 + 0.8 * rand()))
                s.colour_index[id] = (n, 0, n)
            end
        end
    end
end

function multig(s, popn, events)
    for p in popn
        for id in p
            if ! haskey(s.colour_index, id)
                n = length(s.colour_table) + 1
                s.colour_table[n] = convert(C.RGB{N.UFixed8}, C.HSV(0, 0, 0.8 * rand()))
                s.colour_index[id] = (n, 0, n)
            end
        end
    end
end

function find(tag, popn)
    for k in length(popn):-1:1
        for id in popn[k]
            if id.tag == tag
                return id
            end
        end
    end
    error("$(tag) does not exist")
end

function ancestors(tag...)

    function tint!(s, popn, events)

        parents = Dict{Individual, Tuple{Int, Vector{Individual}}}()
        for (k, e) in enumerate(events)
            if isa(e, Birth)
                parents[e.id] = (k, e.parents)
            end
        end

#        grey!(s, popn, events)
        multig(s, popn, events)
        zero = length(s.colour_table)

        for (h, t) in enumerate(tag)
            println("$h $t")
            print("tinting...")
            qcount, pcount = 0, 0
            id = find(t, popn)
            queue = Tuple{Int, Int, Individual}[(1, length(events), id)]
            while length(queue) > 0
                (depth, k, id) = splice!(queue, 1:1)[1]
                index = h * 1000 + depth + zero
                if ! haskey(s.colour_table, index)
                    z = 0.95^(depth-1)
                    s.colour_table[index] = convert(C.RGB{N.UFixed8}, C.HSV((h-1) * 60.0, z, 0.2+0.8*z))
                    print(" $depth,")
                end
                c = s.colour_table[index]
                if s.colour_index[id][2] == 0
                    s.colour_index[id] = (index, k, s.colour_index[id][3])
                    pcount += 1
                end
                (k, ps) = get(parents, id, (0, []))
                for p in ps
                    # tweak for efficiency - queue was huge
                    if s.colour_index[p][2] == 0
                        push!(queue, (depth+1, k, p))
                        qcount += 1
                    end
                end
            end
            println(" done")
            println("$(qcount) queued; $(pcount) altered")
        end
    end
end

function children(tag...)

    function tint!(s, popn, events)

        children = Dict{Individual, Vector{Individual}}()
        for (k, e) in enumerate(events)
            if isa(e, Birth)
                for p in e.parents
                    children[p] = push!(get(children, p, Individual[]), e.id)
                end
            end
        end

        multig(s, popn, events)
        zero = length(s.colour_table)

        for (h, t) in enumerate(tag)
            println("$h $t")
            print("tinting...")
            qcount, pcount = 0, 0
            id = find(t, popn)
            queue = Tuple{Int, Individual}[(1, id)]
            while length(queue) > 0
                (depth, id) = splice!(queue, 1:1)[1]
                index = h * 1000 + depth + zero
                if ! haskey(s.colour_table, index)
                    z = 0.95^(depth-1)
                    s.colour_table[index] = convert(C.RGB{N.UFixed8}, C.HSV((h-1) * 60.0, z, 0.2+0.8*z))
                    print(" $depth,")
                end
                c = s.colour_table[index]
                if s.colour_index[id][2] == 0
                    s.colour_index[id] = (index, 1, index)
                    pcount += 1
                end
                for c in get(children, id, [])
                    # tweak for efficiency - queue was huge
                    if s.colour_index[c][2] == 0
                        push!(queue, (depth+1, c))
                        qcount += 1
                    end
                end
            end
            println(" done")
            println("$(qcount) queued; $(pcount) altered")
        end
    end
end

function rshift(popn)
    popn2 = copy(popn)
    splice!(popn2, 1:0, popn2[1:1])
    popn2[1] = Individual[]
    popn2
end

function plot_tramlines(events, path; 
                        ratio=1.4, min_scale=2, min_axis=1000, tint=grey!,
                        lo=1, hi=-1)

    popn = Vector{Vector{Individual}}()
    for e in events
        expand!(popn, e)
    end

    if lo > 1
        popn = popn[lo:end]
        events = events[lo+1:end]
        splice!(events, 1:0, [VirginBirths(popn[1])])
    end
    if hi != -1
        popn = popn[1:hi-lo+1]
        events = events[1:hi-lo+1]
    end
    max_pop = maximum(map(length, popn)) 

    s, nx, ny = make_state(events, max_pop, ratio, min_scale, min_axis)
    break!(events, popn, s)

    dk = ceil(Int, length(events) / 10)
    tint(s, popn, events)
    D.with(
           D.PNG(path, ceil(Int, nx), ceil(Int, ny)),
#           D.PDF(path; size="letter"),
           D.Axes(scale=(s.cols, s.rows*s.max_pop)),
           D.Pen(PEN; cap="round", join="round")) do
        print("plotting $(length(events))...")
        for (k, (b, e, a)) in enumerate(zip(rshift(popn), events, popn))
            if k % dk == 0
                print(" $k,")
            end
            plot(s, b, e, a, k)
        end
        println(" done")
    end
end

gety(s, i) = (s.rows - (s.row-1)) * s.max_pop - i

function plot_step(x, yb, ya)
    D.move(x, yb)
    if yb-ya > 0.1
        D.line(x+0.5, yb-0.5)
        D.line(x+0.5, ya+0.5)
        D.line(x+1, ya)
    elseif yb-ya < -0.1
        D.line(x+0.5, yb+0.5)
        D.line(x+0.5, ya-0.5)
        D.line(x+1, ya)
    else
        D.line(x+1, ya)
    end
end

function plot_steps(s, b, a, k)
    for id in reverse(a)
        c, i, j = getc(s, id, k), findfirst(b, id), findfirst(a, id)
        if i > 0 && j > 0
            x = s.col
            yb, ya = gety(s, i), gety(s, j)
            D.draw(D.Ink(c)) do
                plot_step(x, yb, ya)
            end
        end
    end    
    s.col += 1
end

plot(s, b, e::SuccessfulChallenge, a, k) = plot_steps(s, b, a, k)

fade(c) = D.WHITE - 0.5 * (D.WHITE - c)

function plot(s, b, e::Birth, a, k)
    x = s.col
    ya = gety(s, findfirst(a, e.id))
    for id in e.parents
        yb = gety(s, findfirst(b, id))
        D.draw(D.Ink(fade(getc(s, id, k)))) do
            plot_step(x, yb, ya)
        end
    end
    plot_steps(s, b, a, k)
end

function plot(s, b, e::VirginBirths, a, k)
    s.row += 1
    s.col = 1
end

# d = longest_lived("evol-1.log", "evol-1.dump", 50, 0.5; n2=100)
# evolve(d, 19, 1000, 25, 10000, "evol-2.dump")

function longest_lived(log_path, dump_path, n1, fraction; limit=-1, n2=-1)

    events = parse_log(log_path, dump_path, n1, fraction; limit=limit)
    popn = Vector{Vector{Individual}}()
    for e in events
        expand!(popn, e)
    end

    n2 = n2 < 1 ? n1 : n2
    score = Dict{AbstractString, Float64}()
    for p in popn
        for (rank, id) in enumerate(p)
            if ! haskey(score, id.tag)
                score[id.tag] = 0.0
            end
            score[id.tag] += 1.0 / rank
        end
    end

    pairs = [(score[id], id) for id in keys(score)]
    sort!(pairs; by = x -> x[1], rev=true)

    # read dump fike a second time - inefficient, but used only once
    named = undump(dump_path)[1]
    names = map(x -> x[2], pairs[1:n2])
    expressions = [named[name] for name in names]

    for (i, (name, expression)) in enumerate(zip(names, expressions))
        println("$(name):$i")
        dump_expression(expression)
    end
    
    return expressions
end

# d = final_gen("evol-2.log", "evol-2.dump", 100, 0.9)
# evolve(d, 19, 1000, 25, 10000, "evol-3.dump")

function final_gen(log_path, dump_path, n, fraction; limit=-1)


    events = parse_log(log_path, dump_path, n, fraction; limit=limit)
    popn = Vector{Vector{Individual}}()
    for e in events
        expand!(popn, e)
    end
    
    tags = AbstractString[]
    for id in popn[end]
        if !(id.tag in tags)
            push!(tags, id.tag)
        end
    end

    named = undump(dump_path)[1]
    expressions = [named[tag] for tag in tags]

    temp = 1.0
    ops = build_ops(n, temp)
    while length(expressions) < n
        expression = weighted_rand(ops)(expressions)
        if !(expression in expressions)
            println("adding $(name(expression))")
            push!(expressions, expression)
        end
    end
    while length(expressions) > n
        expression = pop!(expressions)
        println("dropping $(name(expression))")
    end

    for (i, expression) in enumerate(expressions)
        println("$(name(expression)):$i")
        dump_expression(expression)
    end

    return expressions    
end
