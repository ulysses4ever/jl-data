
using StatefulIterators
using Base.Test


import Base: start, next, done

immutable Alternative
    iter
    state_ptr
    Alternative(iter) = new(iter, [start(iter)])
end

start(i::Alternative) = i

function next(i::Alternative, s::Alternative)
    item, state = next(i.iter, i.state_ptr[1])
    i.state_ptr[1] = state
    item, i
end

done(i::Alternative, s::Alternative) = done(i.iter, i.state_ptr[1])


println("raw array")
sum(ones(Int, 10000))
@time sum(ones(Int, 10000))

for T in (StatefulIterator, StatefulIterators.IterIterator, Alternative)

    println("$(typeof(T([1,2,3])))")
    sum(T(ones(Int, 10000)))
    @time sum(T(ones(Int, 10000)))

    i = T([1,2,3,4,5])
    @test collect(take(i, 3)) == [1,2,3]
    @test collect(take(i, 2)) == [4,5]

    i = T([1,2,3,4,5])
    @test collect(i) == [1,2,3,4,5]

    if (T != Alternative)
        @test read(T([0x1,0x2,0x3,0x4,0x5])) == 0x1
        @test read(T([0x1,0x2,0x3,0x4,0x5]), 2, 2) == [0x1 0x3; 0x2 0x4]
        if (T != StatefulIterators.IterIterator)
            @test read(T([0x1,0x2,0x3,0x4,0x5]), UInt16) == 0x0201
            @test read(T([0x1,0x2,0x3,0x4,0x5]), UInt16, 2) == [0x0201, 0x0403]
            @test read(T(UInt16[0x0201, 0x0403]), UInt8, 4) == [0x1,0x2,0x3,0x4]
        end
    end

end



# bug in GoCL

e = zeros(UInt8, 7)
e[1:4] = map(UInt8, collect("goxp"))
e[5] = 0x00
e[6:7] = reinterpret(UInt8, UInt16[1000])
s = StatefulIterator(e)
@test read(s, 4) == map(UInt8, collect("goxp"))
@test read(s) == 0x00
@test read(s, UInt16) == 1000
