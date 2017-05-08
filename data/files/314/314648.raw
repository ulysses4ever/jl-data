function ms(a)
    if length(a) > 1
        mid = round(length(a) / 2)
        l = a[1:mid]
        r = a[mid + 1:length(a)]
        ms(l)
        ms(r)
        mg(a, l, r)
    end
end

function mg(a, l, r)
    i = 1
    j = 1
    k = 1
    while(k <= length(a) && i <= length(l) && j <= length(r))
        if l[i] < r [j]
            a[k] = l[i]
            i = i + 1
        elseif r[j] < l[i]
            global inversions = inversions + (length(l) - i + 1)
            a[k] = r[j]
            j = j + 1
        end
        k = k + 1
    end
    if i > length(l)
        for k = k:length(a)
            a[k] = r[j]
            j = j + 1
        end
    elseif j > length(r)
        for k = k:length(a)
            a[k] = l[i]
            i = i + 1
        end
    end
end
inversions = 0
a = readcsv("IntegerArray.txt")
ms(a)
println(inversions)
