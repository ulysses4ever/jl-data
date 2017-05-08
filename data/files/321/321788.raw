#!/usr/bin/env julia

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

function insertionsort(stuff::Array)
    if !isempty(stuff)
        for i in 2:length(stuff)
            current = stuff[i]
            checkIndex = i

            while checkIndex > 1 && stuff[checkIndex - 1] > current
                stuff[checkIndex] = stuff[checkIndex - 1]
                checkIndex -= 1
            end

            stuff[checkIndex] = current
        end
        return stuff
    end
end

function bubblesort(stuff::Array)
    if !isempty(stuff)
        swapped = true
        while swapped
            swapped = false
            for ii = 2:length(stuff)
                if stuff[ii - 1] > stuff[ii]
                    stuff[ii - 1], stuff[ii] = stuff[ii], stuff[ii - 1]
                    swapped = true
                end
            end
        end
        return stuff
    end
end

function quicksort(stuff::Array)
    if !isempty(stuff)
        function quicksortStuff(newStuff, left, right)
            if left < right
                pivotPosition = partition(newStuff, left, right)
                quicksortStuff(newStuff, left, pivotPosition - 1)
                quicksortStuff(newStuff, pivotPosition + 1, right)
                return newStuff
            end
        end

        function partition(newStuff, left, right)
            pivotIndex = pickpivot(newStuff, left, right)
            pivotValue = newStuff[pivotIndex]
            newStuff[pivotIndex], newStuff[right] = newStuff[right], newStuff[pivotIndex]
            current = left
            for ii in left:right - 1
                if newStuff[ii] <= pivotValue
                    newStuff[ii], newStuff[current] = newStuff[current], newStuff[ii]
                    current += 1
                end
            end
            newStuff[current], newStuff[right] = newStuff[right], newStuff[current]
            return current
        end

        function pickpivot(newStuff, left, right)
            ## return median([newStuff[left], newStuff[right], newStuff[left + floor((right - left)/2)]])
            return left + floor((right - left)/2)
        end

        return quicksortStuff(stuff, 1, length(stuff))
    end
end
