function qs!(a, l, n)
    if n - l <= 0 return end
    p = l
    #a[l], a[p] = a[p], a[l]
    m = prt!(a, l, n)
    qs!(a, l, m - 1)
    qs!(a, m + 1, n)
end

function prt!(a, l, r)
#    println("parting: $(a[l:r]) left: $(l) right: $(r)")
    p = a[l]
    i = l + 1
    for j = l + 1:r
        if a[j] < p
            a[i], a[j] = a[j], a[i]
            i = i + 1
        end
    end
    a[i - 1], a[l] = a[l], a[i - 1]
#    println("parted: $(a[l:r]) middle: $(i - 1)")
    return(i - 1)
end

a = readcsv("QuickSort.txt")
b = copy(a)
qs!(a, 1, length(a))
#b = [4,3,2,1,1,6,8,4,5,6,3,2]
@time qs!(b, 1, length(a))
