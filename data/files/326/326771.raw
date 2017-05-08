
using StatefulIterators
using Base.Test


function suite_123(make_iter; explicit=true, bits=true)

    print(make_iter(), " ... ")

    s = StatefulIterator(make_iter())
    @test read(s) == 1
    @test read(s) == 2
    c = explicit ? copy(s) : StatefulIterator(make_iter())
    @test read(s) == 3
    @test eof(s)
    
    if explicit
        @test !eof(c)
        @test read(c) == 3
        @test eof(c)
    else
        for x in (copy, peek, available)
            @test_throws ErrorException x(c)
        end
    end
    
    s = StatefulIterator(make_iter())
    if bits
        @test read(s, UInt8) == 0x01
        # TODO - document this behaviour (restarts on instance boundary)
        @test read(s, UInt8, 8) == [0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00]
    else
        @test_throws Exception read(s, UInt8)
        @test_throws Exception read(s, UInt8, 1)
    end

    @test collect(take(StatefulIterator(make_iter()), 2)) == [1, 2]
    @test read(StatefulIterator(make_iter()), 2) == [1, 2]
    if bits
        @test read(StatefulIterator(make_iter()), UInt8, 2) == [0x01, 0x00]
    end

    s = StatefulIterator(make_iter())
    if explicit
        @test peek(s) == 1
        if bits
            @test peek(s, UInt8) == 0x01
            @test peek(s, UInt8, 2) == [0x01, 0x00]
        end
        @test read(s) == 1
        p = position(s)
        @test read(s) == 2
        seek(s, p)
        @test read(s) == 2
        seekend(s)
        @test done(s)
        seek(s, p)
        @test read(s) == 2
        @test available(s) == 1
        if bits
            @test available(s, UInt8) == sizeof(Int) / sizeof(UInt8)
        end
        seekstart(s)
        @test available(s) == 3
        if bits
            @test available(s, UInt8) == 3 * sizeof(Int) / sizeof(UInt8)
        end
        skip(s, 1)
        @test read(s) == 2
    else
        for x in (peek, position, available)
            @test_throws Exception x(s)
        end
        for x in (seek,)
            @test_throws Exception x(s, 1)
        end
        seekend(s)
        @test done(s)
    end

    @test size(read(StatefulIterator(make_iter()), 1, 2)) == (1, 2)
    @test size(read(StatefulIterator(make_iter()), 2, 1)) == (2, 1)

    s = StatefulIterator(make_iter())
    if bits
        a = zeros(Int, 2)
    else
        a = Any[0, 0]
    end
    read!(s, a)
    @test a == [1, 2]

    if bits
        s = StatefulIterator(make_iter())
        a = zeros(UInt8, 2)
        read!(s, a)
        @test a == [0x01, 0x00]
        s = StatefulIterator(make_iter())
        a = readbytes(s, 2)
        @test a == [0x01, 0x00]
        s = StatefulIterator(make_iter())
        a = zeros(UInt32, 3)
        read!(s, a)
        @test a == [0x00000001,0x00000000,0x00000002]
        s = StatefulIterator(make_iter())
        a = readbytes(s, 10)
        @test a == [0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00]
    end

    for n in 2:5
        s = StatefulIterator(make_iter())
        if n <= 3
            skip(s, n)
            @test done(s) == (n == 3)
        else
            @test_throws EOFError skip(s, n)
        end
    end

    println("ok")
end

suite_123(() -> [1,2,3])
suite_123(() -> 1:3)
suite_123(() -> 1:1:3)
suite_123(() -> Task(() -> (for i in 1:3; produce(i); end)); explicit=false, bits=false)
suite_123(() -> Any[1,2,3]; bits=false)

# chunking to larger bitlengths
@test read(StatefulIterator([0x01, 0x00, 0x00, 0x00]), UInt32) == one(UInt32)

# strange step size
@test available(StatefulIterator(1:2:7)) == length(collect(1:2:7))
for iter in ([1,2,3], 1:3, 1:2:7, 1:1:3, 1:2:6, 1:2:7, 2:2:3, 2:2:4)
    s = StatefulIterator(iter)
    skip(s, 1)
    @test collect(s) == collect(iter)[2:end]
    seekend(s)
    @test done(s)
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

# text only
s = StatefulIterator("hello\nworld\n")
@test readline(s) == "hello\n"

function suite_speed(make_iter, target)
    s = make_iter()
    println(typeof(s))
    n = sum(s)
    @test n == target
    s = make_iter()
    @time sum(s)
end

suite_speed(() -> ones(Int, Int(1e6)), 1e6)
suite_speed(() -> StatefulIterator(ones(Int, Int(1e6))), 1e6)
