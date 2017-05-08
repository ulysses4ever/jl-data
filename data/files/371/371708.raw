function qs!(a, l, n, getpivot)
    if n - l <= 0 return(0) end
    println("Quicksorting from $l to $n")
    cp = n - l
    println("Comparisons: $cp")
    p = getpivot(a, l, n) 
    println("Pivot index: $p")
    a[l], a[p] = a[p], a[l]
    m = prt!(a, l, n)
    cp = cp + qs!(a, l, m - 1, getpivot)
    cp = cp + qs!(a, m + 1, n, getpivot)
    return(cp)
end

function getfirstpivot(a, l, r)
    return(l)
end

function getlastpivot(a, l, r)
    return(r)
end

function getmedianpivot2(a, l, r)
    println("Looking for median pivot: $(a[l:r]')")
    m = iceil((r - l) / 2) + l - 1 
    println("Selecting median pivot from $(a[l]) $(a[m]) $(a[r])") 
    p = ifloor(median(a[[l, m, r]])) 
    println("Found pivot value $p")
    if p == a[l]
        return(l)
    elseif p == a[m]
        return(m)
    elseif p == a[r]
        return(r)
    end
end

function getmedian(a, l, m, r)
    if (a[l] >= a[m] && a[l] <= a[r]) || (a[l] >= a[r] && a[l] <= a[m]) return(l) end
    if (a[m] >= a[l] && a[m] <= a[r]) || (a[m] >= a[r] && a[m] <= a[l]) return(m) end
    if (a[r] >= a[l] && a[r] <= a[m]) || (a[r] >= a[m] && a[r] <= a[l]) return(r) end
end

function getmedianpivot(a, l, r)
    n = r - l
    m = l + iceil(n / 2) - 1 
    p = getmedian(a, l, m, r)
    return(p)
end

function prt!(a, l, r)
    println("Parting: $(a[l:r]')")
    p = a[l]
    i = l + 1
    for j = l + 1:r
        if a[j] < p
            a[i], a[j] = a[j], a[i]
            i = i + 1
        end
    end
    a[i - 1], a[l] = a[l], a[i - 1]
    println("Parted: $(a[l:r]')")
    return(i - 1)
end

a = readcsv("qs1000.txt", Int64)
b = copy(a)
c = copy(a)
sanity = sortrows(a)

using Base.Test
# Test median functions
@test getmedian([1,2,3], 1, 2, 3) == 2
@test getmedian([3,2,1], 1, 2, 3) == 2
@test getmedian([1,10,9], 1, 2, 3) == 3
@test getmedian([1,4,5,7,8], 1, 3, 5) == 3
@test getmedian([1,4,5,7], 1, 2, 4) == 2

@test getmedianpivot([8,2,4,5,7,1], 1, 6) == 3  
@test getmedianpivot([4,5,6,7], 1, 4) == 2
@test getmedianpivot([1,2,3,4,5,6,7], 3, 4) == 3

# Run code and test
firstpivottotal = qs!(a, 1, length(a), getfirstpivot)
@test a == sanity
@test length(a) == length(sanity)

lastpivottotal = qs!(b, 1, length(b), getlastpivot)
@test b == sanity
@test length(b) == length(sanity)

medianpivottotal = qs!(c, 1, length(c), getmedianpivot2)
@test c == sanity
@test length(c) == length(sanity)

println("Comparisons using first element as pivot: $firstpivottotal")
println("Comparisons using last element as pivot: $lastpivottotal")
println("Comparisons using median element as pivot: $medianpivottotal")
