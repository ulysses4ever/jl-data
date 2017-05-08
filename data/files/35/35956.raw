# is n divisable by all numbers from 1 to m
function divisable(n::Int64, m::Int64)
    for i in 1:m
        if mod(n, i) != 0
            return false
        end
    end
    return true
end

# find smallest number divisable by numbers from 1 to m
function findsmallest(m::Int64, max::Int64)
    for n in 1:max
       if divisable(n, m)
           return n
       end
    end
    return nothing
end