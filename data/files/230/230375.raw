include("collisions.jl")

buckets = count_nonempty_buckets(128, 256)
println(buckets)

println("05th %: ", minimum(find(cumsum(buckets).>0.05)))
println("50th %: ", minimum(find(cumsum(buckets).>0.5)))
println("95th %: ", minimum(find(cumsum(buckets).>0.95)))

@time num_items_expected(128, 64)
@time num_items_expected(16384, 100)
@time num_items_expected(16384, 8192)

@time plot_item_distribution(256, "buckets_256.png")
@time plot_item_distribution(2^14, "buckets_16384.png")
