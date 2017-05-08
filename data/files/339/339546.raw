using MathUtils
using Base.Test

# Test log_sum_exp()
original = log(sum(exp([1, 2])))
ours = log_sum_exp([1, 2])
@test abs(ours - original) <= eps(original)

original = log(sum(exp([1, 2, 3, 4, 5, 6])))
ours = log_sum_exp([1, 2, 3, 4, 5, 6])
@test abs(ours - original) <= eps(original)

original = log(sum(exp([1, 1, 1, 1, 1])))
ours = log_sum_exp([1, 1, 1, 1, 1])
@test abs(ours - original) <= eps(original)

# Test sample_discrete_logspace() by comparing with a simpler sampler
# (given the same random input they should behave identically)
dist = [0.1, 0.7, 0.2]
log_dist = log(dist)
num_test = 1000
vals1 = zeros(num_test)
# run sample_discrete_logspace
srand(1)
for i in 1:num_test
  vals1[i] = sample_discrete_logspace(log_dist)
end
# run sample_discrete
srand(1)
vals2 = zeros(num_test)
for i in 1:num_test
  vals2[i] = sample_discrete(dist)
end
@test vals1 == vals2
