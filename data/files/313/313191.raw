[x^2 for x in 1:10] # 10-element Array{Int64,1}: 1, ..., 100

# But unlike Python, there is no conditional array comprehension
[x^2 for x in filter(iseven, 1:10)]

# With `map` instead
map(x -> x^2, filter(iseven, 1:10))
