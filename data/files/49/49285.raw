using DataStructures
using CountMin


N = 100000

function dotest(cms, n::Integer)
    for i in 1:n
        push!(cms, i+=1)
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
    sm::UInt = 0
    for i in 1:N
        sm += cms[i]
    end
end

println("Profiling add/push")
Profile.clear()
@profile dotest(cms, N)
Profile.print()

println("Profiling getitem")
Profile.clear()
@profile sumtest(cms, N)
Profile.print()
#dotest(ctr, 1000)

