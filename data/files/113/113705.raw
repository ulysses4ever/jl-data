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
    newstate[dims] += 1

    # modulate
    for i=[dims - j for j in 0:dims-1]
        if newstate[i] > shape[i]
            # if the index overflows, mod it around
            newstate[i] = newstate[i] % shape[i]
            # attempt to increment the next index
            try
                newstate[i-1] += 1
                # if this is BoundsError, we are done
            catch err
                if isa(err,BoundsError)
                    return (state,nde.arr[state...]),state+1
                else
                    #something is very wrong
                    error(err)
                # this is > shape, so it will trigger done
                end
            end
        else
            # if there's no overflow in a an index
            # no higher-order index has overflow either
            break
        end
    end
    return (state,nde.arr[state...]),newstate
end

Base.done(nde::NDenumerate,state::Array{Int}) = state > [size(nde.arr)...]

A = rand(10,10,10,10,10,10);

@elapsed for (i,val)=enumerate(A)
    A[i]*2;
end

@elapsed for (i,val)=ndenumerate(A)
    A[i...]*2;
end