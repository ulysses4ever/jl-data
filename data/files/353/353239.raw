module Inv

const data_fl = "IntegerArray.txt"

function inv_main()

    num_data = 100_000
    data = Array{Int64,1}(num_data)
    open(data_fl) do file
        num_line = 0
        while !eof(file)
            num_line += 1
            num = parse(Int64, strip(readline(file)))
            data[num_line] = num
        end
    end

    count = inv_count(data)

    print_with_color(:green, "The number of inversions is $(count) !")
end

function inv_count(data::Array{Int64,1})
    if length(data) == 1
        return 0
    else
        ind_m = round(Int64, length(data)/2)
        left = data[1:ind_m]
        right = data[ind_m+1:end]
        l = inv_count(left)
        r = inv_count(right)
        m = inv_merge(left, right)
        return l+r+m
    end

    throw("You can't see me!")
end

function inv_merge(left::Array{Int64,1}, right::Array{Int64,1})
    count = 0
    left_ord = merge_sort(left)
    right_ord = merge_sort(right)

    for l in left_ord, r in right_ord
        if l > r
            count += 1
        elseif l == r
            throw("inv_merge found two equal integer.")
        end
    end

    count
end

#level_stack = 0

function merge_sort(data::Array{Int64,1})
#   global level_stack += 1
#   l = length(data)
#   print_with_color(:blue,"The length of data is $(l)\n")
#   print_with_color(:green, "merge_sort in the stack level $(level_stack).\n")
    num_data = length(data)
    if num_data > 1
        middle = round(Int64, num_data / 2)
        left = merge_sort(data[1:middle])
        right = merge_sort(data[middle+1:end])
        return merge(left,right)::Array{Int64,1}
    elseif num_data == 1
        return data
    else
        throw("input data cann't be empty!")
    end
end

function merge(left::Array{Int64,1}, right::Array{Int64,1})
    num_left = length(left)
    num_right = length(right)
    result = similar(left, num_left+num_right)
    n = 0
    p_left = 1
    p_right = 1
    while n <= (num_left+num_right)
        n += 1
        first_left = left[p_left]
        first_right = right[p_right]

        if first_left < first_right
            result[n] = first_left
            p_left += 1
            if p_left > num_left
                result[n+1:end] = right[p_right:end]
                break
            end
        elseif first_left > first_right
            result[n] = first_right
            p_right += 1
            if p_right > num_right
                result[n+1:end] = left[p_left:end]
                break
            end
        else
            throw("merge found two numbers is same")
        end
    end
    result
end


end

