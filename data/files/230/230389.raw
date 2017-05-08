using DataFrames
using Gadfly

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

buckets = count_nonempty_buckets(128, 256)
println(buckets)

println("05th %: ", minimum(find(cumsum(buckets).>0.05)))
println("50th %: ", minimum(find(cumsum(buckets).>0.5)))
println("95th %: ", minimum(find(cumsum(buckets).>0.95)))

@time plot_item_distribution(256, "buckets_256.png")
@time plot_item_distribution(2^14, "buckets_16384.png")
