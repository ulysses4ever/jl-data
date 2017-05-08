#
# 電話番号のような重複のない数字が大量に入力ファイルへ存在する。ソートした結果を出力する
#
module PPearl

function make_bitarray(in_file::String, max_num::Int)
    nums = falses(max_num)
    open(in_file) do io
        for l in eachline(io)
            num = parse(Int, l)
            if num > max_num
                error("$num is larger than $max_num")
            end
            nums[num] = true
        end
    end
    return nums
end

function print(nums::BitArray{1})
    for i in 1:length(nums)
        if nums[i]
            println(i)
        end
    end
end

end
