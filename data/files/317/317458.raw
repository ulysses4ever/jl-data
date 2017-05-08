#
# ファイルには多くて40億の32bit整数がランダムに潜んでいて、その中に含まれない32bit整数を1つ見つける問題
#
module MissingNum

function generate_test_file(file_name, num_of_nums)
    nums = rand(1:2^32, num_of_nums)
    open(file_name, "w") do io
        write(io, join(nums, "\n"))
    end
end

function split_file(in_file_name, left_file_name, right_file_name, partition)
    num = 0
    open(in_file_name) do io
        open(left_file_name, "w") do left_io
            open(right_file_name, "w") do right_io
                for l in eachline(io)
                    num = parse(Int, l)
                    if num < partition
                        write(left_io, "$num\n")
                    else
                        write(right_io, "$num\n")
                    end
                end
            end
        end
    end
end

end
