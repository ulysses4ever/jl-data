using DataStructures
using CountMin
import CountMin: add!


N = 1_000_000

function dotest(cms, n::Integer)
    for i in 1:n
        push!(cms, n)
    end
end

println("Doing CMS")
cms = CountMinSketch{UInt8}(4, 2^28)
dotest(cms, 1000)
@time dotest(cms, N)

println("Doing Counter")
ctr = counter(Int)
dotest(ctr, 1000)
@time dotest(ctr, N)


print("Checking equality... ")
for i in 1:N
    assert(cms[i] >= ctr[i])
end
println("All Good!")


function oflow(cms, n::Integer)
    for i in 1:n
        add!(cms, i, 255)
    end
end

println("Profiling add with overflow")
oflow(cms, 10)
@time oflow(cms, 10000)
