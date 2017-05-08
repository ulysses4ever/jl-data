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
        middle   = round(Int64, num_data/2)
        left = merge_sort(data[1:middle])
        right = merge_sort(data[middle:end])
        merge(left,right)
    elseif num_data == 1
        return data[1]
    end
end

function merge(left::Array{Int64,1}, right::Array{Int64,1})
    num_left = length(left)
    num_right = length(right)
    result = similar(left, num_left+num_right)
    n = 0
    while n <= (num_left+num_right)
        n += 1
        


    end

end


end

