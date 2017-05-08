
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


import Base: start, next, done

immutable Alternative
    iter
    state_ptr
    Alternative(iter) = new(iter, [start(iter)])
end

start(i::Alternative) = i

function next(i::Alternative, s::Alternative)
    item, state = next(i.iter, i.state_ptr[1])
    i.state_ptr[1] = state
    item, i
end

done(i::Alternative, s::Alternative) = done(i.iter, i.state_ptr[1])

println("alternative")
sum(Alternative(ones(Int, 10000)))
@time sum(Alternative(ones(Int, 10000)))
