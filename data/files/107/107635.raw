
function distinct_pair(range)
    i = rand(range)
    j = i
    while i == j
        j = rand(range)
    end
    i, j
end


function evolve(population, nplays, nrounds)
    stats = reset_stats()
    for i in 1:nrounds
        for j in 1:nplays
            a, b = pick_pair(population)
            result = play(population, a, b)
            apply_result!(population, a, b, result)
            stats = update_stats(stats, result)
        end
        update_population!(population, stats)
    end
    population
end

pick_pair(population) = distinct_pair(1:length(population))


name(data) = sha1(data)[1:8]
name(data, rank) = "$(name(data)) $(rank)"

function surprise(a, b, result)
    # best at start (low numbers); score positive if a won.
    # so if a-b is negative then a was ranked better.
    # and if score is positive then that was confirmed.
    # so a shock result is when product is positive
    result.details.score * (a-b) > 0
end

function display_result(a, b, result, s)
    print(s ? "!" : " ")
    a, b = result.score.total < 0 ? b, a : a, b
    print(name(a), " ")
    print(result.score.total == 0 ? "drew" : "beat")
    print(" ", name(b), "  ")
    @printf("%3.2f space %d stones\n", result.score.owned, result.score.stones)
end

function apply_result!(population, a, b, result)
    s = surprise(a, b, result)
    display_result(a, b, result, s)
    if s
        population[a], population[b] = population[b], population[a]
    end
end


# track fraction of owned space as an indicator of quality

reset_stats() = 0, 0.0

function update_stats(stats, result)
    n, sum = stats
    n+1, sum+result.score.owned
end


function biased_pair(population)
    a = rand(2:length(population))
    b = rand(1:(a-1))
    a, b
end

biased_single(population) = biased_pair(population)[2]

random_single(population) = rand(population)

function rotate(data::Vector)
    n = rand(1:length(data))
    vcat(data[n:end], data[1:n-1])
end

function merge(a::Vector, b::Vector)
    a, b = shuffle([a, b])
    i, j = sort(distint_rand(1:length(a)))
    vcat(a[1:i], b[i+i:j], a[j+1:end])
end

function merge_with_rotate(a::Vector, b::Vector)
    a, b = shuffle([a, b])
    merge(a, rotate(b))
end

function random_bytes(fraction)
    function change(a::Vector{UInt8})
        for i in 1:length(a)
            if rand(1.0) < fraction
                a[i] = rand(UInt8)
            end
        end
        a
    end
end

function random_bits(fraction)
    function change(a::Vector{UInt8})
        for i in 1:length(a)
            if rand(1.0) < fraction
                a[i] = a[i] $ (0x01 << rand(0:7))
            end
        end
        a
    end
end

function weighted_rand(ops)
    total = sum([op[1] for op in ops])
    limit = rand(0:Float(total))
    acc, i = 0.0, 1
    while acc < limit
        acc += ops[i][1]
        i += 1
    end
    ops[i][2]
end

function build_ops(population, stats)
    n, sum = stats
    # temperature varies from 1 (hottest) to 0 (coldest)
    temp = (1 - (sum / n))
    l = length(population[1])
    ops = Tuple{Number, Function}[
              10 => x -> random_bits(100 * temp / l)(random_single(x)),
              10 => x -> random_bytes(100 * temp / l)(random_single(x))]
    if temp > 0.25
        push!(ops, 10 => x -> merge(biased_pair(x)...))
    end
    if temp > 0.5
        push!(ops, 10 => x -> merge_with_rotate(biased_pair(x)...))
    end
    ops
end

function update_population!(population, stats)
    ops = build_ops(population, stats)
    n = length(population)
    m = Int(n/2)
    survivors = population[1:m]
    for i in m+1:n
        population[i] = weighted_rand(ops)(survivors)
    end
    population
end
