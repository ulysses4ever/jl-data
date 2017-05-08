module TestPrograms
    using Base.Test
    using Ook

    text = readall(Pkg.dir("Ook", "test", "programs", "squares.ook"))
    ops = Ook.parse(Ook.lex(text))
    io = IOBuffer()
    Ook.interpret(ops, io_out = io)
    @test takebuf_string(io) == "1 4 9 16 25 36 49 64 81 100 "

    text = readall(Pkg.dir("Ook", "test", "programs", "squares2.ook"))
    ops = Ook.parse(Ook.lex(text))
    io = IOBuffer()
    Ook.interpret(ops, io_out = io)
	output = takebuf_string(io)
	reference = ""
	for i in 0:100
		reference = string(reference, @sprintf("%d\n", i^2))
	end
	@test output == reference
end
