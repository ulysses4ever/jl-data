# max sub array problem
function findMaxCrossingSubarray(A,low,mid,high)
    left_sum = typemin(Float64)
    sum = 0
    max_left = 1
    for i=[mid:-1:low]
        sum += A[i]
        if sum>left_sum
            left_sum = sum
            max_left = i
        end
    end
    right_sum = typemin(Float64)
    sum = 0
    max_right = 1
    for j=[mid+1:high]
        sum += A[j]
        if sum>right_sum
            right_sum = sum
            max_right = j
        end
    end
    return max_left,max_right,left_sum+right_sum
end

function findMaxSubarray(A,low,high)
    if high == low
        return low,high,A[low]
    else
        mid = floor((low+high)/2)
        left_low,left_high,left_sum = findMaxSubarray(A,low,mid)
        right_low,right_high,right_sum = findMaxSubarray(A,mid+1,high)
        cross_low,cross_high,cross_sum = findMaxCrossingSubarray(A,low,mid,high)
        if left_sum>right_sum && left_sum>cross_sum
            return left_low,left_high,left_sum
        elseif right_sum>left_sum && right_sum>cross_sum
            return right_low,right_high,right_sum
        else
            return cross_low,cross_high,cross_sum
        end
    end
end

function test()
    arr = [13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7]
    low,high,sum = findMaxSubarray(arr,1,length(arr))
    println(low)
    println(high)
    println(sum)
end
