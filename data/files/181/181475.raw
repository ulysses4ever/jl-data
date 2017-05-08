###
  Repeated stepping through the list
  comparing each pair of adjacent items
  swapping them if they are in the wrong order
###

import Base.Sort
immutable BubbleSortAlg <: Sort.Algorithm end
const BubbleSort = BubbleSortAlg()

function Base.sort!(v::AbstractVector, lo::Int, hi::Int, ::BubbleSortAlg, o::Sort.Ordering)
    while true
        clean = true
        for i = lo:hi-1
            if Sort.lt(o, v[i+1], v[i])
                v[i+1], v[i] = v[i], v[i+1]
                clean = false
            end
        end
        clean && break
    end
    return v
end
