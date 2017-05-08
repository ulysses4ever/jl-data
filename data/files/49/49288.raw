using DataStructures
using CountMin


N = 100000

function dotest(cms, n::Integer)
    while n > 0
        push!(cms, n-=1)
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
    assert(cms[i] == ctr[i])
end
println("All Good!")

function sumtest(cms, n)
    sm = 0
    for i in 1:N
        sm += cms[i]
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
