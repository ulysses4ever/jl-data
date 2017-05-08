function insertSort!(a)
    for i = 2:length(a)
        key = a[i]
        j = i - 1
        while j > 0 && a[j] > key
            a[j + 1] = a[j]
            j = j - 1
        end
        a[j + 1] = key
    end 
end
a = [5,2,10,34,1,4] 
insertSort!(a)
println(a)
