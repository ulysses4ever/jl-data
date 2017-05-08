module Inv

const data_fl = "IntegerArray.txt"

function inv_main()

    num_data = 1000_000
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


end

function inv_merge(left, rigth)
    if length(left) == length(right) == 1
        if left > right
            return 1
        else
            return 0
        end
    end

    inv_merge(left)
end

function merge_sort(data::Array{Int64,1})
    num_data = length(data)
    if num_data > 1
        middle = round(Int64, num_data/2)
        left = merge_sort(data[1:middle])
        right = merge_sort(data[middle:end])
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

