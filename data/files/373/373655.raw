#
# ファイルには多くて40億の32bit整数がランダムに潜んでいて、その中に含まれない32bit整数を1つ見つける問題
#
module MissingNum

function generate_test_file(file_name, num_of_nums, max_bitnum)
    nums = rand(1:2^max_bitnum, num_of_nums)
    open(file_name, "w") do io
        write(io, join(nums, "\n"))
    end
end

function split_file(in_file_name, left_file_name, right_file_name, partition)
    num         = 0
    left_count  = 0
    right_count = 0
    open(in_file_name) do io
        open(left_file_name, "w") do left_io
            open(right_file_name, "w") do right_io
                for l in eachline(io)
                    num = parse(Int, l)
                    if num < partition
                        left_count += 1
                        write(left_io, "$num\n")
                    else
                        right_count += 1
                        write(right_io, "$num\n")
                    end
                end
            end
        end
    end
    return left_count, right_count
end

function find_missing(in_file_name, min_num, max_num)
    println("Find missing value, min: $min_num, max: $max_num")

    base_file_name  = replace(in_file_name, ".dat", "")
    left_file_name  = "$(base_file_name)_L.dat"
    right_file_name = "$(base_file_name)_R.dat"
    partition_num   = round(Int, (min_num + max_num) / 2)

    left_count, right_count = split_file(in_file_name, left_file_name, right_file_name, partition_num)

    if left_count == 0
        print("Found missing value, $(partition_num - 1)")

    elseif right_count == 0
        print("Found missing value, $(partition_num + 1)")

    elseif left_count < right_count
        println("Go to left, $left_count < $right_count ")
        find_missing(left_file_name, min_num, partition_num)

    elseif left_count > right_count
        println("Go to right, $left_count > $right_count ")
        find_missing(right_file_name, partition_num, max_num)

    else
        error("$left_count == $right_count")
    end
end

end
