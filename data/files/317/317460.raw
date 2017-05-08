#
# ファイルには多くて40億程度の32bit整数がランダムに並んでいて、その中に含まれない32bit整数を1つ見つける問題
#
module MissingNum

function generate_test_file(file, max_bitnum)
    open(file, "w") do io
        for num in 1:2^max_bitnum
            if (num % 97) != 0          # 含まれない数字を適当に
                write(io, "$num\n")
            end
        end
    end
end

function split_file(in_file_name, lower_file_name, upper_file_name, partition)
    num         = 0
    lower_count = 0
    upper_count = 0
    open(in_file_name) do io
        open(lower_file_name, "w") do lower_io
            open(upper_file_name, "w") do upper_io
                for l in eachline(io)
                    num = parse(Int, l)
                    if num < partition
                        lower_count += 1
                        write(lower_io, "$num\n")
                    else
                        upper_count += 1
                        write(upper_io, "$num\n")
                    end
                end
            end
        end
    end
    return lower_count, upper_count
end

function find_missing(in_file_name, min_num, max_num)
    println("Finding missing value, min: $min_num, max: $max_num")

    base_file_name  = replace(in_file_name, ".dat", "")
    lower_file_name = "$(base_file_name)_L.dat"
    upper_file_name = "$(base_file_name)_R.dat"
    partition_num   = round(Int, (min_num + max_num) / 2)

    lower_count, upper_count = split_file(in_file_name, lower_file_name, upper_file_name, partition_num)

    if upper_count == 0
        print("Found missing value, $(partition_num)")
    elseif lower_count == 0
        print("Found missing value, $(partition_num - 1)")
    elseif lower_count < upper_count
        println("Go to lower, $lower_count < $upper_count ")
        find_missing(lower_file_name, min_num, partition_num)
    else
        println("Go to upper, $lower_count > $upper_count ")
        find_missing(upper_file_name, partition_num, max_num)
    end
end

end
