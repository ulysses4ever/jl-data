using DataFrames
using Gadfly

# This was just me fiddling for fun
# HyperLogLog would be how to do this for real http://blog.notdot.net/2012/09/Dam-Cool-Algorithms-Cardinality-Estimation

# buckets[n] contains the probability that n buckets will be non-empty after num_items have been randomly inserted into the buckets 
function count_nonempty_buckets(num_buckets, num_items)
    buckets = zeros(num_buckets)
    buckets[1] = 1.0
    counts = [1:length(buckets)]

    for i=2:num_items
        buckets = buckets .* counts / num_buckets + vcat(0, buckets[1:end-1]) .* reverse(counts) / num_buckets
    end
    @assert abs(sum(buckets)-1)<1e-10
    buckets
end

function plot_item_distribution(num_buckets, filename="buckets.png")
    num_items = 3*num_buckets

    buckets = zeros(num_buckets)
    buckets[1] = 1.0
    counts = [1:length(buckets)]

    p05 = Float64[]
    p50 = Float64[]
    p95 = Float64[]

    for i=2:num_items
        buckets = buckets .* counts / num_buckets + vcat(0, buckets[1:end-1]) .* reverse(counts) / num_buckets
        push!(p05, minimum(find(cumsum(buckets).>0.05)))
        push!(p50, minimum(find(cumsum(buckets).>0.50)))
        push!(p95, minimum(find(cumsum(buckets).>0.95)))
    end

    items = [2:num_items]
    data = DataFrame(Items=items, P05=p05, P50=p50, P95=p95)
    draw(PNG(filename, 8inch, 6inch), plot(melt(data, [:Items]), x=:Items, y=:value, color=:variable, Geom.line))

    @assert abs(sum(buckets)-1)<1e-10
    data
end

function num_items_expected(num_buckets, num_nonempty_buckets, num_samples=1000)
    min_items_to_sample = zeros(num_samples)
    max_items_to_sample = zeros(num_samples)

    for i=1:num_samples
        items = 0
        nonempty_buckets = 0
        buckets = zeros(num_buckets)
        while nonempty_buckets <= num_nonempty_buckets
            items = items + 1
            bucket = rand(1:num_buckets)
            if buckets[bucket]==0
                buckets[bucket] = 1
                nonempty_buckets = nonempty_buckets + 1
                if nonempty_buckets == num_nonempty_buckets
                    min_items_to_sample[i] = items
                end
            end
        end
        max_items_to_sample[i] = items-1
    end
    println("Number of items expected for ", num_buckets, " buckets with ", num_nonempty_buckets, " not empty.")
    println("\t - Min    min items to sample: ", minimum(min_items_to_sample))
    println("\t - Median min items to sample: ", median(min_items_to_sample))
    println("\t - Median max items to sample: ", median(max_items_to_sample))
    println("\t - Max    max items to sample: ", maximum(max_items_to_sample))
    println("\t - 05th % min items to sample: ", quantile(min_items_to_sample, 0.05))
    println("\t - 05th % max items to sample: ", quantile(max_items_to_sample, 0.05))
    println("\t - 95th % min items to sample: ", quantile(min_items_to_sample, 0.95))
    println("\t - 95th % max items to sample: ", quantile(max_items_to_sample, 0.95))
    println("\t - Mean difference", mean(max_items_to_sample .- min_items_to_sample))
end
