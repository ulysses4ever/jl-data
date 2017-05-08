module TestLex
	using Base.Test
    using Ook

    s1 = "Ook. Ook! Ook. Ook?"

    @test Ook.lex(s1) == [
    	Ook.PERIOD,
    	Ook.EXCLAMATION,
    	Ook.PERIOD,
    	Ook.QUESTION,
    ]

    s2 = """
    	Ook. Ook! Ook. Ook?
    	Ook! Ook!
    """

    @test Ook.lex(s2) == [
    	Ook.PERIOD,
    	Ook.EXCLAMATION,
    	Ook.PERIOD,
    	Ook.QUESTION,
    	Ook.EXCLAMATION,
    	Ook.EXCLAMATION,
    ]
end
