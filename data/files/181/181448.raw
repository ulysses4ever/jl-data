# in main.jl
 
function is_divisble(n, i)
return n % i == 0
end
 
function is_prime(n::Int64)
if n <= 3
    return true
end
 
if is_divisble(n, 2)
    return false
end
 
# initialize a counter variable
i = 3
 
while i <= sqrt(n)
    if is_divisble(n, i)
        return false
    end
 
    i += 2
end
 
return true
end
