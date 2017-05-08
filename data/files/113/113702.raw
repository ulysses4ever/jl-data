import Base.start
import Base.next
import Base.length

type NDenumerate{A<:Array}
    arr::A
end

ndenumerate(arr) = NDenumerate(arr)

length(nde::NDenumerate) = length(nde.arr)
start(nde::NDenumerate) = ones(Int,length(size(nde.arr)))

function next(nde::NDenumerate,state::Array{Int})
    println(state)
    shape = size(nde.arr)
    dims = length(shape)
    
    #increment the smallest index
    newstate = state + vcat(zeros(Int,dims-1),[1])

    # modulate
    for i=[dims - j for j in 0:dims-1]
        if newstate[i] > shape[i]
            newstate[i] = newstate[i] % shape[i]
            newstate[i-1] += 1
        else
            # if this is not true at an index, the rest won't change
            break
        end
    end
    return @show nde.arr[state...],newstate
end

function Base.done(nde::NDenumerate,state::Array{Int})
    @show state
    @show [size(nde.arr)...]
    @show state == [size(nde.arr)...]
end

mynde = NDenumerate(rand(5,5))

state = start(mynde)
while !done(mynde, state)
  (i, state) = next(mynde, state)
end