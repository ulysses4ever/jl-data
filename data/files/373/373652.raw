#
# 大きな n 要素が入った配列を左方向に i 要素動かす（シフトさせる）
#
module ShiftArray

function split(nums, i, n)
    return sub(nums, 1:i), sub(nums, i+1:n-i), sub(nums, n-i+1:n)
end

function shift!(nums, i, n)
    a, bl, br = split(nums, i, n)
    switch_block!(a, br, i)

    remain = n-i
    blbr = sub(nums, 1:remain)

    if remain > 2i
        shift!(blbr, i, remain)
    else
        simple_shift!(blbr, i, remain)
    end
end

function switch_block!(a, b, n)
    for j in 1:n
        t    = a[j]
        a[j] = b[j]
        b[j] = t
    end
end

function simple_shift!(nums, i, n)
    for j in 1:i
        t = nums[1]
        for k in 1:n-1
            nums[k] = nums[k+1]
        end
        nums[n] = t
    end
end

end
