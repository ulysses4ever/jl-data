function fib_next(l::Array{Int,1})
    if length(l) < 2 # initialize the list
        push!(l, 0, 1)
        return l
    end
    push!(l, l[length(l)] + l[length(l) - 1])
    return l
end

# uses fib_next to return a list of all fibonacci numbers up to max
function fib_up_to(max::Int)
    list = fib_next(Int[])
    while list[length(list)] < max
        list = fib_next(list)
    end
    return list[1:length(list)-1] # don't include the last element
end
