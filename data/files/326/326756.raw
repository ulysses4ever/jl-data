
using StatefulIterators
using Base.Test

println("raw array")
sum(ones(Int, 10000))
@time sum(ones(Int, 10000))

println("stateful iterator")
sum(StatefulIterator(ones(Int, 10000)))
@time sum(StatefulIterator(ones(Int, 10000)))

i = StatefulIterator([1,2,3,4,5])
@test collect(take(i, 3)) == [1,2,3]
@test collect(take(i, 2)) == [4,5]

i = StatefulIterator([1,2,3,4,5])
@test collect(i) == [1,2,3,4,5]
