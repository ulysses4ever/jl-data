module TestInterpreter
    using Base.Test
    using Ook

    type MyIO <: IO
        bytes::Vector{Uint8}
    end
    Base.write(io::MyIO, val::Uint8) = push!(io.bytes, val)
    Base.read(io::MyIO, ::Type{Uint8}) = shift!(io.bytes)

    text = readall(Pkg.dir("Ook", "test", "programs", "print.ook"))
    ops = Ook.parse(Ook.lex(text))

    io1 = MyIO(Uint8[])
    write(io1, 'a')
    write(io1, 'b')
    io2 = IOBuffer()
    Ook.interpret(ops, io_in = io1, io_out = io2)
    @test takebuf_array(io2) == [0x62, 0x61, 0x63, 0x62]

    io1 = MyIO(Uint8[])
    write(io1, 'a')
    write(io1, 'b')
    io2 = IOBuffer()
    Ook.ook(text, io_in = io1, io_out = io2)
    @test takebuf_array(io2) == [0x62, 0x61, 0x63, 0x62]
end
