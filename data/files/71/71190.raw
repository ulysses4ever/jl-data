function errors_main()
    lim = 10
    
    uf = UnionFinder(lim)
    
    @test_throws union!(uf, lim, 0)
    @test_throws union!(uf, 0, lim)
    @test_throws union!(uf, lim, lim + 1)
    @test_throws union!(uf, lim + 1, lim)
    
    @test_throws union!(uf, [lim lim lim] [lim lim])

    @test_throws union!(uf, [lim], [0])
    @test_throws union!(uf, [0], [lim])
    @test_throws union!(uf, [lim], [lim + 1])
    @test_throws union!(uf, [lim + 1], [lim])
    
    @test_throws union!(uf, [(lim, 0)])
    @test_throws union!(uf, [(0, lim)])
    @test_throws union!(uf, [(lim, lim + 1)])
    @test_throws union!(uf, [(lim + 1, lim)])
    
    @test_throws find!(uf, lim + 1)
    @test_throws find!(uf, 0)
    
    @test_throws size!(uf, lim + 1)
    @test_throws size!(uf, 0)
    
    cf = CompressedFinder(uf)
    
    @test_throws find(cf, lim + 1)
    @test_throws find(cf, 0)

    @test_throws UnionFinder(0)
end

errors_main()
