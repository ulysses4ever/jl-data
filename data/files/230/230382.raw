
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

buckets = count_nonempty_buckets(128, 256)
println(buckets)

println("05th %: ", minimum(find(cumsum(buckets).>0.05)))
println("50th %: ", minimum(find(cumsum(buckets).>0.5)))
println("95th %: ", minimum(find(cumsum(buckets).>0.95)))

# 5 items, 4 buckets
# 1: P(1) * 1/4
# 2: P(2) * 2/4 + P(1)*3/4
# 3: P(3) * 3/4
# 4: P(4) + P(3) * 1/4
