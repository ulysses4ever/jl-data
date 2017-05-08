# ファイルには多くて40億の32ビ ット整数がランダムにli1/ん でいて、その中に含まれない32ビ ット整数を1つ見つける のが問題でした。
# 2^32は4,294,967,296な ので、数字が40億個しかないのなら、その中 に含まれない整数 (「 欠けている整数」とよぶことにします)が必、ずあるはずです。
module MissingNum

function generate_test_file(file_name, num_of_nums)
    nums = rand(1:2^32, num_of_nums)
    open(file_name, "w") do io
        write(io, join(nums, "\n"))
    end
end

end
