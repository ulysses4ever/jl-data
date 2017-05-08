module TestParse
	using Base.Test
    using Ook

    s = """
        Ook. Ook?
        Ook? Ook.
        Ook. Ook.
        Ook! Ook!
        Ook. Ook!
        Ook! Ook.
        Ook! Ook?
        Ook? Ook!

        Ook? Ook!
        Ook! Ook?
        Ook! Ook.
        Ook. Ook!
        Ook! Ook!
        Ook. Ook.
        Ook? Ook.
        Ook. Ook?
    """

    tokens =  Ook.lex(s)

    ops = Ook.parse(tokens)

    @test ops == [
        Ook.OP1,
        Ook.OP2,
        Ook.OP3,
        Ook.OP4,
        Ook.OP5,
        Ook.OP6,
        Ook.OP7,
        Ook.OP8,
        Ook.OP8,
        Ook.OP7,
        Ook.OP6,
        Ook.OP5,
        Ook.OP4,
        Ook.OP3,
        Ook.OP2,
        Ook.OP1,
    ]
end
