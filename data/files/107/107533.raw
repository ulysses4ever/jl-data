
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

abstract Birth <: Event

immutable VirginBirth <: Birth
    id::Individual
end

immutable OneParentBirth <: Birth
    id::Individual
    parent::Individual
end

immutable TwoParentBirth <: Birth
    id::Individual
    parents::Tuple{Individual, Individual}
end

abstract Challenge <: Event

immutable FailedChallenge <: Challenge
    won::Individual
    lost::Individual
end

immutable SuccessfulChallenge <: Challenge
    won::Individual
    lost::Individual
end

immutable Death <: Event
    id::Individual
end

# constructed later, by merging FailedChallenge and Death
immutable FinalFailedChallenge <: Challenge
    won::Individual
    lost::Individual
end

# constructed later, by merging Deaths
immutable Deaths <: Event
    ids::Vector{Individual}
end

# constructed later, by merging VirgniBirths
immutable VirginBirths <: Event
    ids::Vector{Individual}
end


# delete unused individuals completely; merge FailedChallenge and
# Death to give FinalFailedChallenge
function prune1(events)

    deletes = Int[]
    uses = Dict{Individual, Int}()
    births = Dict{Individual, Int}()
    failures = Dict{Individual, Int}()

    for (i, event) in enumerate(events)
        if isa(event, Birth)
            @assert !haskey(uses, event.id)
            uses[event.id] = 0
            births[event.id] = i
            if isa(event, OneParentBirth)
                delete!(failures, event.parent)
                uses[event.parent] += 1
            elseif isa(event, TwoParentBirth)
                delete!(failures, event.parents[1])
                uses[event.parents[1]] += 1
                delete!(failures, event.parents[2])
                uses[event.parents[2]] += 1
            end
        elseif isa(event, Challenge)
            uses[event.won] += 1
            uses[event.lost] += 1
            if isa(event, FailedChallenge)
                failures[event.lost] = i
            else
                delete!(failures, event.lost)
                delete!(failures, event.won)
            end
        else
            @assert isa(event, Death)
            if uses[event.id] == 0
                push!(deletes, i)
                push!(deletes, births[event.id])
            elseif haskey(failures, event.id)
                j = failures[event.id]
                failure = events[j]
                events[j] = FinalFailedChallenge(failure.won, failure.lost)
                push!(deletes, i)
            end
            delete!(uses, event.id)
            delete!(births, event.id)
            delete!(failures, event.id)
        end
    end

    # pending unused
    for id in keys(births)
        if uses[id] == 0
            push!(deletes, births[id])
        end
    end

    sort!(deletes)
    deleteat!(events, deletes)

    println("pruned $(length(deletes)) unusued events")
    events
end

# merge Death into Deaths
function prune2(events)

    deletes = Int[]
    j = 0

    for (i, event) in enumerate(events)
        if isa(event, Death)
            if j == 0
                j = i
                events[j] = Deaths([event.id])
            else
                push!(deletes, i)
                push!(events[j].ids, event.id)
            end
        else
            j = 0
        end
    end

    sort!(deletes)
    deleteat!(events, deletes)

    @assert length(filter(x -> isa(x, Death), events)) == 0

    println("pruned $(length(deletes)) unusued events")
    events
end

# merge VirginBirth into VirginBirths
function prune3(events)
    replacement = VirginBirths(Individual[])
    i = 1
    while isa(events[i], VirginBirth)
        push!(replacement.ids, events[i].id)
        i += 1
    end
    if i > 1
        splice!(events, 1:i-1, Event[replacement])
        println("pruned $(i-2) unusued events")
    end
    events
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
        push!(events, OneParentBirth(population[end], parent1))
#        println(events[end])

    elseif (m = match(p_rotate, line)) != nothing
        parent1 = parent(population, m[:a])
        parent2 = parent(population, m[:x] == m[:y] ? m[:z] : m[:y])
        push!(population, Individual(m[:c]))
        push!(events, TwoParentBirth(population[end], (parent1, parent2)))
#        println(events[end])

    elseif (m = match(p_merge, line)) != nothing
        parent1 = parent(population, m[:a])
        parent2 = parent(population, m[:b])
        push!(population, Individual(m[:c]))
        push!(events, TwoParentBirth(population[end], (parent1, parent2)))
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

    # take initial population from dump
    for expression in undump(dump_path)[2][1:n]
        push!(population, Individual(name(expression)))
        push!(events, VirginBirth(population[end]))
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

    prune1(events)
    prune2(events)
    prune3(events)
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
        elseif isa(event, Deaths)
            n -= length(event.ids)
        elseif isa(event, Death)
            n -= 1
        elseif isa(event, FinalFailedChallenge)
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
    push!(p, popn)
end

function expand!(p::Vector{Vector{Individual}}, e::VirginBirths)
    popn = isempty(p) ? Individual[] : copy(p[end])
    for id in e.ids
        push!(popn, id)
    end
    push!(p, popn)
end

function expand!(p::Vector{Vector{Individual}}, e::Deaths)
    popn = copy(p[end])
    for id in e.ids
        i = findfirst(popn, id)
        splice!(popn, i:i)
    end
    push!(p, popn)
end

function expand!(p::Vector{Vector{Individual}}, e::SuccessfulChallenge)
    popn = copy(p[end])
    i = findfirst(popn, e.lost)
    j = findfirst(popn, e.won)
    popn[i+1:j] = popn[i:j-1]
    popn[i] = e.won
    push!(p, popn)
end

function expand!(p::Vector{Vector{Individual}}, e::FailedChallenge)
    popn = copy(p[end])
    push!(p, popn)
end

function expand!(p::Vector{Vector{Individual}}, e::FinalFailedChallenge)
    popn = copy(p[end])
    i = findfirst(popn, e.lost)
    popn[i:end-1] = popn[i+1:end]
    pop!(popn)
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

# this assumes pruned events
function plot_tramlines(events, path; ratio=1.5, min_scale=2, min_axis=1000)
    s, nx, ny = make_state(events, ratio, min_scale, min_axis)
    break!(events, s)
    popn = Vector{Vector{Individual}}()
    for e in events
        expand!(popn, e)
    end
    popn2 = copy(popn)
    splice!(popn2, 1:0, popn2[1:1])
    popn2[1] = Individual[]
    grey!(s, popn)
    D.with(D.PNG(path, ceil(Int, nx), ceil(Int, ny)),
           D.Axes(scale=s.rows*s.max_pop)) do
        for (b, e, a) in zip(popn2, events, popn)
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

function plot(s, b, e::FinalFailedChallenge, a)
    plot_step(s, b, a)
    plot_step(s, s.colours[e.lost], findfirst(b, e.lost), findfirst(a, e.won))
end

function plot(s, b, e::TwoParentBirth, a)
    plot_step(s, b, a)
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

function plot(s, b, e::OneParentBirth, a)
    plot_step(s, b, a)
    plot_step(s, s.colours[e.id], findfirst(b, e.parent), findfirst(a, e.id))
end

function plot(s, b, e::VirginBirths, a)
    s.row += 1
    s.col = 1
end

plot(s, b, e::Deaths, a) = plot_step(s, b, a)

