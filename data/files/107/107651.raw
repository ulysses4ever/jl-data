
const survival = 0.5

function evolve(population, nplays, nrounds, path, algorithm)
    known = Set{UInt64}()
    exists(path) && rm(path)
    dump(known, path, population)
    for i in 1:nrounds
        stats = reset_stats()
        for j in 1:nplays
            a, b = pick_competitors(length(population))
            # seed below counts from 1 and can be reproduced from the log
            srand(algorithm, j+(i-1)*nplays)
            result = play(population[a], population[b], algorithm, null_display)
#            result = play(population[a], population[b], algorithm, board_display)
            display_result(i, nrounds, j, nplays, population, a, b, result)
            apply_result!(population, a, b, result)
            stats = update_stats(stats, result)
        end
        if i != nrounds
            population = update_population(population, stats, board_size)
            dump(known, path, population)
        end
    end
    population
end

function pick_competitors(n)
    # surprise() below assumes these are ordered
    b = rand(2:n)
    # biased to top, with one always in surviving half
    rand(1:min(b-1, Int(survival * n))), b
end

const name_length = 16
name(data) = sha1(data)[1:name_length]
name(data, rank) = "$(name(data)) $(rank)"

function surprise(a, b, result)
    # best at start (low numbers); score positive if a won.
    # so if a-b is negative then a was ranked better.
    # and if score is positive then that was confirmed.
    # so a shock result is when product is positive
    result.score.total * (a-b) > 0
end

function display_result(i, n, j, m, population, a, b, result)
    @printf("%3d/%d %3d/%d %s", i, n, j, m, surprise(a, b, result) ? "!" : " ")
    a, b = result.score.total < 0 ? (b, a) : (a, b)
    @printf(" %s:%-3d ", name(population[a]), a)
    print(result.score.total == 0 ? "dr" : "bt")
    @printf(" %s:%-3d ", name(population[b]), b)
    @printf("%2d sc  %3d mv  %2d sp  %2d st\n", abs(result.score.total), result.score.moves, result.score.owned, result.score.stones)
end

function apply_result!(population, a, b, result)
    if surprise(a, b, result)
        # this loses good individuals too quickly
#        population[a], population[b] = population[b], population[a]
        a, b = sort([a, b])
        tmp = population[b]
        population[a+1:b] = population[a:b-1]
        population[a] = tmp
    end
end


# track fraction of owned space as an indicator of quality

reset_stats() = 0, 0.0

function update_stats(stats, result)
    n, sum = stats
    # ignore games with one stone since i has an artificially high owned
    if result.score.stones > 1
        n+1, sum+result.score.owned
    else
        n, sum
    end
end


function distinct_indices(n; start=1)
    i = rand(start:n)
    j = i
    while i == j
        j = rand(start:n)
    end
    i, j
end

function biased_pair(population)
    a = rand(2:length(population))
    b = rand(1:(a-1))
    population[a], population[b]
end

function distinct_pair(population)
    a, b = distinct_indices(length(population))
    population[a], population[b]
end

biased_single(population) = biased_pair(population)[2]

random_single(population) = rand(population)

function rotate(a::Vector)
    n = rand(lheader+2:length(a))
    c = vcat(a[1:lheader], a[n:end], a[lheader+1:n-1])
    print("rotate $(n-lheader+1) $(name(a)) => $(name(c)) + ")
    c
end

function merge(a::Vector, b::Vector)
    a, b = shuffle(Vector[a, b])
    c, i, j, attempts = a, 0, 0, 0
    while c in (a, b) && attempts < 10
        i, j = sort([distinct_indices(length(a); start=lheader)...])
        c = vcat(a[1:i], b[i+1:j], a[j+1:end])
        attempts += 1
    end
    println("merge $(j-i) $(name(a)), $(name(b)) => $(name(c))")
    c
end

function merge_with_rotate(a::Vector, b::Vector)
    a, b = shuffle(Vector[a, b])
    merge(a, rotate(b))
end

function random_bytes(fraction)
    function change(a::Vector{UInt8})
        b, count = copy(a), 0
        while b == a
            for i in lheader+1:length(b)
                if rand(Float64) < fraction
                    b[i] = rand(UInt8)
                    count += 1
                end
            end
        end
        println("$(count) random bytes $(name(a)) => $(name(b))")
        b
    end
end

function random_bits(fraction)
    function change(a::Vector{UInt8})
        b, count = copy(a), 0
        while b == a
            for i in lheader+1:length(b)
                if rand(Float64) < fraction
                    b[i] = b[i] $ (0x01 << rand(0:7))
                    count += 1
                end
            end
        end
        println("$(count) random bits $(name(a)) => $(name(b))")
        b
    end
end

function weighted_rand(ops)
    total = sum([op[1] for op in ops])
    limit = rand(Float64) * total
    acc, i = ops[1][1], 1
    while acc < limit
        acc += ops[i][1]
        i += 1
    end
    ops[i][2]
end

function build_ops(length, temp)
    ops = Tuple{Number, Function}[
              (10, x -> random_bits(temp/10)(random_single(x))),
              (10, x -> merge(biased_pair(x)...)),
              (1, x -> merge_with_rotate(biased_pair(x)...)),
              (1, x -> random_bytes(temp/10)(random_single(x)))]
    if temp > 0.25
        push!(ops, (10, x -> random_bytes(temp/10)(random_single(x))))
    end
    if temp > 0.5
        push!(ops, (10, x -> merge_with_rotate(biased_pair(x)...)))
    end
    ops
end

function update_population(prev_pop, stats, board_size)
    t, sum = stats
    # temperature varies roughly from 1 (hottest) to 0 (coldest)
    temp = t == 0 ? 1 : max(0, min(1, 1 - (2 * sum / t) / board_size^2))
    @printf("temp %4.3f\n", temp)
    ops = build_ops(length(prev_pop[1]), temp)
    n = length(prev_pop)
    m = Int(survival * n)
    next_pop = Vector{UInt8}[]
    while length(next_pop) < m && length(prev_pop) > 1
        push!(next_pop, prev_pop[1])
        prev_pop = prev_pop[2:end]
    end
    while length(next_pop) < n
        push!(next_pop, weighted_rand(ops)(next_pop))
    end
    next_pop
end

function dump(known, path, population)
    open(path, "a") do io
        for data in population
            n = name(data)
            tag = reinterpret(UInt64, hex2bytes(n))[1]
            if !(tag in known)
                print(io, string(n, ":"))
                print(io, bytes2hex(data))
                print(io, "\n")
                push!(known, tag)
            end
        end
    end
end

function undump(path)
    named = Dict{AbstractString, Vector{UInt8}}()
    open(path, "r") do io
        for line in eachline(io)
            name, data = split(line, ":")
            named[name] = hex2bytes(data[1:end-1])  # drop newline
        end
    end
    named
end

