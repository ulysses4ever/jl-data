type NDenumerate{A<:Array}
    arr::A
end

ndenumerate(arr) = NDenumerate(arr)

Base.length(nde::NDenumerate) = length(nde.arr)
Base.start(nde::NDenumerate) = 1

function Base.next(nde::NDenumerate, state::Int)
    sub = ind2sub(size(nde.arr),state)
    return (sub,nde.arr[state]), state+1
end

Base.done(nde::NDenumerate, state::Int) = state == length(nde)+1