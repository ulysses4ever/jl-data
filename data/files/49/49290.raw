using DataStructures
using CountMin
import CountMin: add!


N = 100
N = 10000000

function dotest(cms, n::Integer)
    while n > 0
        push!(cms, n)
        n -= 1
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

function sumtest(cms, n)
    a::UInt8 = 0
    while n > 0
        a = cms[n]
        n -= 1
    end
end

@time sumtest(cms, N)

println("Profiling add/push")
Profile.clear()
@profile dotest(cms, N)
Profile.print(maxdepth=15)

println("Profiling getitem")
Profile.clear()
@profile sumtest(cms, N)
Profile.print(maxdepth=15)

function oflow(cms, n::Integer)
    while n > 0
        add!(cms, 255)
        n -= 1
    end
end

println("Profiling add with overflow")
Profile.clear()
@profile oflow(cms, 10000)
Profile.print(maxdepth=15)
