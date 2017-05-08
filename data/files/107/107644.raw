
const survival = 0.5

function evolve(population, nplays, nrounds, board_size, limit, path)
    for i in 1:nrounds
        stats = reset_stats()
        for j in 1:nplays
            a, b = pick_competitors(length(population))
            # seed below counts from 1 and can be reproduced from the log
            result = play_direct(population[a], population[b], board_size, limit; seed=j+(i-1)*nplays)
            display_result(i, nrounds, j, nplays, population, a, b, result)
            apply_result!(population, a, b, result)
            stats = update_stats(stats, result)
        end
        dump(path, population)
        if i != nrounds
            update_population!(population, stats, board_size)
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


name(data) = sha1(data)[1:8]
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

function rotate(data::Vector)
    n = rand(lheader+2:length(data))
    print("rotate $(n-lheader+1) + ")
    vcat(data[1:lheader], data[n:end], data[lheader+1:n-1])
end

function merge(a::Vector, b::Vector)
    a, b = shuffle(Vector[a, b])
    c, i, j = a, 0, 0
    while c in (a, b)
        i, j = sort([distinct_indices(length(a); start=lheader+1)...])
        c = vcat(a[1:i], b[i+1:j], a[j+1:end])
    end
    println("merge $(j-i)")
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
        println("$(count) random bytes")
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
        println("$(count) random bits")
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

function update_population!(population, stats, board_size)
    n, sum = stats
    # temperature varies roughly from 1 (hottest) to 0 (coldest)
    temp = n == 0 ? 1 : max(0, min(1, 1 - (2 * sum / n) / board_size^2))
    @printf("temp %4.3f\n", temp)
    ops = build_ops(length(population[1]), temp)
    n = length(population)
    m = Int(survival * n)
    survivors = population[1:m]
    for i in m+1:n
        population[i] = weighted_rand(ops)(survivors)
    end
    population
end


function dump(path, population)
    if exists(path)
        backup = "$(path)-old"
        exists(backup) && rm(backup)
        mv(path, backup)
    end
    open(path, "w") do io
        for data in population
            print(io, bytes2hex(data))
            print(io, "\n")
        end
    end
end
