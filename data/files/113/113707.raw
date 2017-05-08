type NDenumerate{A<:Array}
    arr::A
end

ndenumerate(arr) = NDenumerate(arr)

Base.length(nde::NDenumerate) = Base.length(nde.arr)
Base.start(nde::NDenumerate) = ones(Int,length(size(nde.arr)))

function Base.next(nde::NDenumerate,state::Array{Int})
    shape = size(nde.arr)
    dims = length(shape)
    
    #increment the smallest index
    newstate = copy(state)
    newstate[1] += 1

    # modulate
    for i=1:dims
        if newstate[i] > shape[i]
            # if the index overflows, mod it around
            newstate[i] = newstate[i] % shape[i]
            newstate[i+1] += 1
        else
            # if there's no overflow in a an index
            # no higher-order index has overflow either
            break
        end
    end
    return (state,nde.arr[state...]),newstate
end

Base.done(nde::NDenumerate,state::Array{Int}) = state == [size(nde.arr)...]

A = rand(100,100);

@elapsed for (i,val)=enumerate(A)
    println(i,val)
end

@elapsed for (i,val)=ndenumerate(A)
    println(i,val)
end