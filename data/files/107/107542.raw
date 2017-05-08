
const p_challenge = r"^\s*(?P<i>\d+)/(?P<n>\d+)\s+(?P<j>\d+)/(?P<m>\d+) (?P<surprise>(?:!| )) (?P<a>[a-f0-9]+):(?P<x>\d+)\s+(?:bt|dr)\s+(?P<b>[a-f0-9]+):(?P<y>\d+).*$"

# 34 random bytes d1862e709058196a => fddd8634d3f25690
# 30 random bits 755e948bc02367be => d68ad2353d0c378a
const p_random = r"^\s*\d+ random (?:bits|bytes) (?P<a>[a-f0-9]+) => (?P<c>[a-f0-9]+)\s*$"

# rotate 262 cb03e03f73d749c2 => 326e568542888c67 + merge 123 326e568542888c67, fddd8634d3f25690 => f2b69ec0fe5c1fd7
# rotate chunk 7 0043f8c791de1a53 => 0bf67111a514bd9d + merge 97 f7e67544a9a5ef3c, 0bf67111a514bd9d => da7fc58918b190c0
const p_rotate = r"^\s*rotate (?:chunk )?\d+ (?P<a>[a-f0-9]+) => (?P<x>[a-f0-9]+) \+ merge \d+ (?P<y>[a-f0-9]+), (?P<z>[a-f0-9]+) => (?P<c>[a-f0-9]+)\s*$"

# merge 264 0f9139cba0588c2a, d9a5f3b8d06028d9 => 9b6504a9fe224d56
const p_merge = r"^\s*merge \d+ (?P<a>[a-f0-9]+), (?P<b>[a-f0-9]+) => (?P<c>[a-f0-9]+)\s*$"

# temp 0.819
const p_temp = r"\s*temp \d+\.\d+\s*$"


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
    deaths::Vector{Bool}
    Birth(id, parents) = new(id, parents, zeros(Bool, length(parents)))
end

abstract Challenge <: Event

immutable FailedChallenge <: Challenge
    won::Individual
    lost::Individual
end

type SuccessfulChallenge <: Challenge
    won::Individual
    lost::Individual
    death::Bool  # loser dies
    SuccessfulChallenge(won, lost) = new(won, lost, false)
end

immutable Death <: Event
    id::Individual
end

delete!(v::Vector, i::Integer) = splice!(v, i:i)

function prune!(events, id)
    deleted, positive, i = 0, false, length(events)
    while i > 0
        e = events[i]
        if isa(e, VirginBirths) && id in e.ids
            if ! positive
                delete!(e.ids, findfirst(e.ids, id))
            end
            return
        elseif isa(e, Birth) && e.id == id
            if ! positive
                delete!(events, i)
            end
            return
        elseif isa(e, Birth) && id in e.parents
            j = findfirst(e.parents, id)
            e.deaths[j] = ! positive
            positive = true
        elseif isa(e, FailedChallenge) && (e.lost == id || e.won == id)
            delete!(events, i)
        elseif isa(e, SuccessfulChallenge) && e.won == id
            positive = true
        elseif isa(e, SuccessfulChallenge) && e.lost == id
            e.death = ! positive
            positive = true
        elseif isa(e, Death) && e.id == id
            delete!(events, i)
        end
        i = min(i-1, length(events))
    end
end

allids(e::VirginBirths) = e.ids
allids(e::Birth) = vcat(e.id, e.parents)
allids(e::Challenge) = vcat(e.won, e.lost)
allids(e::Death) = [e.id]

function prune!(events)
    deleted, ids, i = 0, Set{Individual}(), length(events)
    while i > 0
        for id in allids(events[i])
            if ! (id in ids)
                push!(ids, id)
                n = length(events)
                prune!(events, id)
                n -= length(events)
                deleted += n
            end
        end
        i = min(i-1, length(events))
    end
    println("deleted $(deleted)")
    deleted
end


parent(population, tag) = population[findfirst(id -> id.tag == tag, population)]

function parse_line(events, population, line, n, fraction)

    if (m = match(p_challenge, line)) != nothing
        x, y = parse(Int, m[:x]), parse(Int, m[:y])
        a, b = population[x], population[y]
        @assert a.tag == m[:a]
        @assert b.tag == m[:b]
        if m[:surprise] == "!"
            push!(events,  SuccessfulChallenge(a, b))
            population[y+1:x] = population[y:x-1]
            population[y] = a
        else
            push!(events, FailedChallenge(a, b))
        end
#        println(events[end])

    elseif (m = match(p_random, line)) != nothing
        parent1 = parent(population, m[:a])  # triggers error on initial junk
        push!(population, Individual(m[:c]))
        push!(events, Birth(population[end], [parent1]))
#        println(events[end])

    elseif (m = match(p_rotate, line)) != nothing
        parent1 = parent(population, m[:a])
        parent2 = parent(population, m[:x] == m[:y] ? m[:z] : m[:y])
        push!(population, Individual(m[:c]))
        push!(events, Birth(population[end], [parent1, parent2]))
#        println(events[end])

    elseif (m = match(p_merge, line)) != nothing
        parent1 = parent(population, m[:a])
        parent2 = parent(population, m[:b])
        push!(population, Individual(m[:c]))
        push!(events, Birth(population[end], [parent1, parent2]))
#        println(events[end])

    elseif match(p_temp, line) != nothing
        for i in 1:Int(fraction * n)
            id = pop!(population)
            push!(events, Death(id))
        end
#        println("died back to $(length(events))/$(length(population))")

    else
#        println("?: $(line)")
    end
end

function parse_log(log_path, dump_path, n, fraction)

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
                parse_line(events, population, line[1:end-1], n, fraction)
                started = started || isa(events[end], Challenge)
            catch
                if started
                    rethrow()
                end
            end

        end
    end

    while prune!(events) > 0 end
    events
end


type PlotState
    max_pop::Int
    rows::Int
    cols::Int
    row::Int
    col::Int
    colours::Dict{Individual, C.Colorant}
    PlotState(max_pop, rows, cols) = new(max_pop, rows, cols, 0, 0,
                                         Dict{Individual, C.Colorant}())
end

show(io::IO, s::PlotState) = show(io, "PlotState($(s.max_pop),$(s.col)/$(s.cols),$(s.row)/$(s.rows))")

function max_pop(events)
    n, m = 0, 0
    for event in events
        if isa(event, VirginBirths)
            n += length(event.ids)
        elseif isa(event, Birth)
            n += 1
            for d in event.deaths
                n -= d ? 1 : 0
            end
        elseif isa(event, Death)
            n -= 1
        elseif isa(event, SuccessfulChallenge) && event.death
            n -= 1
        end
        m = max(n, m)
    end
    m
end

function make_state(events, ratio, min_scale, min_axis)
    nx = length(events)
    ny = max_pop(events)
    rows = max(1, Int(fld(sqrt(nx * ny / ratio), ny)))
    cols = Int(cld(nx, rows)) + 1
    s = PlotState(ny, rows, cols)
    n = max(min_scale * cols, min_axis / 1.2)
    scale = n / cols
    m = scale * ny * rows + 0.2 * n
    n = n + 0.2 * n
    println("($(nx),$(ny)) -> $s, ($n, $m), $(scale)")
    s, n, m
end

function expand!(p::Vector{Vector{Individual}}, e::Birth)
    popn = copy(p[end])
    push!(popn, e.id)
    for (id, death) in zip(e.parents, e.deaths)
        if death
            delete!(popn, findfirst(popn, id))
        end
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
    popn[i+1:j] = popn[i:j-1]
    popn[i] = e.won
    if e.death
        delete!(popn, i+1)
    end
    push!(p, popn)
end

function expand!(p::Vector{Vector{Individual}}, e::FailedChallenge)
    popn = copy(p[end])
    push!(p, popn)
end

function break!(e, s::PlotState)
    for i in 1:(s.rows-1)
        splice!(e, i*(s.cols-1):i*(s.cols-1)-1, [VirginBirths(Individual[])])
    end
end

function grey!(s, popn)
    for p in popn
        for id in p
            if !haskey(s.colours, id)
                s.colours[id] = parse(C.Colorant, "grey")
            end
        end
    end
end

function rshift(popn)
    popn2 = copy(popn)
    splice!(popn2, 1:0, popn2[1:1])
    popn2[1] = Individual[]
    popn2
end

function plot_tramlines(events, path; ratio=1.5, min_scale=2, min_axis=1000)
    s, nx, ny = make_state(events, ratio, min_scale, min_axis)
    break!(events, s)
    popn = Vector{Vector{Individual}}()
    for e in events
        expand!(popn, e)
    end
    mp = maximum(map(length, popn)) 
    println("$((mp, s.max_pop))")
    @assert mp == s.max_pop (mp, s.max_pop)
    grey!(s, popn)
    D.with(D.PNG(path, ceil(Int, nx), ceil(Int, ny)),
           D.Axes(scale=(s.cols, s.rows*s.max_pop))) do
        for (b, e, a) in zip(rshift(popn), events, popn)
            plot(s, b, e, a)
        end
    end
end

gety(s, i) = (s.rows - (s.row-1)) * s.max_pop - i

function plot_step(s, b, a)
    s.col += 1
    for id in a
        plot_step(s, s.colours[id], findfirst(b, id), findfirst(a, id))
    end    
end

function plot_step(s, c, i, j)
    if i > 0 && j > 0
        x = s.col
        D.draw(D.Ink(c), D.Pen(0.5)) do
            D.move(x-1, gety(s, i))
            D.line(x, gety(s, j))
        end
    end
end

plot(s, b, e::SuccessfulChallenge, a) = plot_step(s, a, b)

function plot(s, b, e::FailedChallenge, a)
    plot_step(s, b, a)
    plot_step(s, s.colours[e.lost], findfirst(b, e.lost), findfirst(a, e.won))
end

function plot(s, b, e::Birth, a)
    plot_step(s, b, a)
    if length(e.parents) == 1
        plot_step(s, s.colours[e.id], findfirst(b, e.parents[1]), findfirst(a, e.id))
    else
        i = findfirst(b, e.parents[1])
        j = findfirst(b, e.parents[2])
        i, j = i > j ? (j, i) : (i, j)
        x = s.col
        D.draw(D.Ink(s.colours[e.id]), D.Pen(0.5)) do
            D.move(x-1, gety(s, i))
            D.line(x-1, gety(s, j))
            D.line(x, gety(s, findfirst(a, e.id)))
        end
    end
end

function plot(s, b, e::VirginBirths, a)
    s.row += 1
    s.col = 1
end

