# If I'm ranking 5 items from smallest to largest
# And guess at random, what is the chance that I
# assign none of the five the correct rank?
#
# Calculated directly this should be 11/30

num_samples  = 10_000_000
num_no_match = 0

for i=1:num_samples
    num_no_match += sum(randperm(5).==1:5)==0 ? 1 : 0
end

println(@sprintf("%0.2f", num_no_match/num_samples*100), "% of sampled permutations had no matches")
println(11/30)