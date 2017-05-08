
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
    VirginBirth(id) = new(Individual(id))
end

immutable SingleParentBirth <: Birth
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

type Death <: Event
    id::Individual
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
        println(events[end])

    elseif (m = match(p_random, line)) != nothing
        parent1 = parent(population, m[:a])  # triggers error on initial junk
        push!(population, Individual(m[:c]))
        push!(events, SingleParentBirth(population[end], parent1))
        println(events[end])

    elseif (m = match(p_rotate, line)) != nothing
        parent1 = parent(population, m[:a])
        parent2 = parent(population, m[:x] == m[:y] ? m[:z] : m[:y])
        push!(population, Individual(m[:c]))
        push!(events, TwoParentBirth(population[end], (parent1, parent2)))
        println(events[end])

    elseif (m = match(p_merge, line)) != nothing
        parent1 = parent(population, m[:a])
        parent2 = parent(population, m[:b])
        push!(population, Individual(m[:c]))
        push!(events, TwoParentBirth(population[end], (parent1, parent2)))
        println(events[end])

    elseif match(p_temp, line) != nothing
        for i in 1:Int(fraction * n)
            id = pop!(population)
            push!(events, Death(id))
        end
        println("died back to $(length(events))")

    else
        println("?: $(line)")
    end
end


function parse_log(log_path, dump_path, n, fraction)

    events, population = Vector{Event}(), Vector{Individual}()

    # take initial population from dump
    for expression in undump(dump_path)[2][1:n]
        push!(events, VirginBirth(name(expression)))
        push!(population, events[end].id)
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

    events
end
