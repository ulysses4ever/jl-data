
# Actually, don't do this; recursive is so bad.   
function fibrec(n)
    if n < 2
        return 1
    end
    fibrec(n - 1) + fibrec (n -2)
end

# actual solution starts here
val = 2
val1 = 1
val2 = 0
sum = 0
while val < 4000000
    if val % 2 == 0
        sum += val
    end
    val2 = val1
    val1 = val
    val = val1 + val2
end
print("$sum\n")



