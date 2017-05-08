# Module clojure to implement important clojure functions

# return a random integer from in the range of 0-i
function randInt (i :: Int)
    floor(Int,i*rand ())
end

# return an array of size dim which contents are randomly generated
# integers ranges from 0 to i
function randInts (dim ::Int, i ::Int)
    res :: Array{Int,1} = zeros (Int,dim)
    for j = 1:dim
        res [j] = randInt (i)
    end
    res
end

# return the frequencies of each data in an array
function frequencies (lst :: Array)
    res = Dict {Any,Int} ()
    for l in lst
        res [l] = haskey (res,l) ? res [l]+1 : 1
    end
    res
end

# clojure's takeWhile works on range
function takeWhile (f, xs :: Range)
    res :: Array = []
    for x in xs
        if f (x)
            push! (res,x)
        else
            return res
        end
    end
    return res
end

# clojure's take-while works for array
function takeWhile (f, xs :: Array)
    res :: Array = []
    for x in xs
        if f (x)
            push! (res,x)
        else
            return res
        end
    end
    return res
end

# clojure's drop-while
function dropWhile (f, xs ::Array)
    res :: Array = []
    for i = 1:length (xs)
        if ! f (xs [i])
            return xs [i:end]
        end
    end
    return res
end

# clojure's drop-while for range
function dropWhile (f, xs :: Range)
    res :: Array = []
    for i = 1:length (xs)
        if ! f (xs [i])
            return xs [i:end]
        end
    end
    return res
end

# clojure group-by 
function groupby (f, xs :: Array)
    res = Dict ()
    for x in xs
        if haskey (res,f (x))
            push! (res [x], x)
        else
            res [(f (x))] = [x]
        end
    end
    res
end

# clojure's group-by for ranges
function groupby (f, xs :: Range)
    res = Dict ()
    for x in xs
        tmp = f (x)
        if haskey (res,tmp)
            push! (res [tmp], x)
        else
            res [tmp] = [x]
        end
    end
    res
end

# clojure's merge-with
function mergeWith (f, maps :: Array)
    # maps should an array of maps (dicts)
    res = maps [1]
    for m in maps [2:end]
        for (k,v) in m
            if haskey (res,k)
                res [k] = f (res [k], v)
            else
                res [k] = v
            end
        end
    end
    return res
end

function sortby (f, xs :: Array)
    if isempty (xs)
        return xs
    elseif isempty (xs [2:end])
        return xs [1:end]
    else
        x = xs [1]
        fx = f (x)
        smaller = sortby (f,filter (i -> f (i) <= fx, xs [2:end])) 
        larger = sortby (f,filter (i -> f (i) > fx, xs [2:end]))
        return vcat (smaller,[x],larger)
    end
end

function sortby (f, xs :: Range)
    if isempty (xs)
        return xs
    elseif isempty (xs [2:end])
        return xs [1:end]
    else
        x = xs [1]
        fx = f (x)
        smaller = sortby (f,filter (i -> f (i) <= fx, xs [2:end])) 
        larger = sortby (f,filter (i -> f (i) > fx, xs [2:end]))
        return vcat (smaller,[x],larger)
    end
end


        




