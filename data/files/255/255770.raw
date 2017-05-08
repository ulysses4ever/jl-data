function collatz(x)
col = [x]
z = x
while z != 1
    if z % 2 == 0
        z = z/2
        push!(col,z)
    else
        z = 3*z + 1
        push!(col,z)
    end
end
return length(col)
end

function checknums(x)
hilen = 1
histart = 1
for i = 1:x
    if collatz(i) > hilen
        hilen = collatz(i)
        histart = i
    end
end
return histart
end

println(checknums(999999))