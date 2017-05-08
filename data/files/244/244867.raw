include("clojure.jl")

# Permutations of n elements from xs
function permute (xs,n :: Int)
    res :: Array = map (x->[x],xs)
    for i = 2:n
        tmp = []
        for r in res
            bhn = setdiff (xs,r)
            for b in bhn
                push! (tmp, vcat (r,[b]))
            end
        end
        res = tmp
    end
    res
end

# Like permute but an element can be inserted more than once
function permutes (xs,n::Int)
    res :: Array = map (x->[x],xs)
    for i = 2:n
        tmp = []
        for r in res
            for x in xs
                push! (tmp,vcat (r,[x]))
            end
        end
        res = tmp
    end
    res
end


