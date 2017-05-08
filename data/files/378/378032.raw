#!/bin/env julia

function mergesort(stuff::Array)
    if !isempty(stuff)
        function mergeStuff(left::Array, right::Array)
            leftInt = 1
            rightInt = 1
            result = Array(typeof(left[1]), length(left) + length(right))
            
            while leftInt <= length(left) && rightInt <= length(right)
                current = leftInt + rightInt - 1
                if left[leftInt] <= right[rightInt]
                    result[current] = left[leftInt]
                    leftInt += 1
                else
                    result[current] = right[rightInt]
                    rightInt+= 1
                end
            end
            
            result[end-(length(left) - leftInt):end] = left[leftInt:end]
            result[end-(length(right) - rightInt):end] = right[rightInt:end]
            
            return result
        end
        left = stuff[1:floor(length(stuff)/2)]
        right = stuff[floor(length(stuff)/2) + 1:end]

        if length(left) == 1 || length(right) == 1
            return mergeStuff(left, right)
        end

        return mergeStuff(mergesort(left), mergesort(right))
    end
end


