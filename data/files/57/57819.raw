#https://en.wikipedia.org/wiki/Closure_%28computer_programming%29

function start(x)
    if x < 10
        x = 10 #setting conditional environment
    end
    function increment(y)
        return x + y
    end
    return increment
end

f = start(15)
g = start(1)

println("15 + 4 = ",f(4))
println("15 + 20 = ", f(20))
println("10 + 4 = ", g(4))
println("10 + 24 = ", g(24))
