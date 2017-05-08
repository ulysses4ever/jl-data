function polymorphism_main()
    uf = UnionFinder(convert(Uint16, 2))
    union!(uf, convert(Uint16, 1), convert(Uint16, 2))
    reset!(uf)
    @test Uint16 == typeof(find!(uf, convert(Uint16, 1)))
    @test Uint16 == typeof(size!(uf, convert(Uint16, 1)))

    @test_throws union!(uf, convert(Int64, 1), convert(Int64, 2))
    @test_throws union!(uf, convert(Uint16, 1), convert(Int64, 2))
    @test_throws union!(uf, convert(Int64, 1), convert(Uint16, 2))
    @test_throws find!(uf, convert(Int64, 1))
    @test_throws size!(uf, convert(Int64, 1))    

    cf = CompressedFinder(uf)
    @test Uint16 == typeof(find(cf, convert(Uint16, 1)))
    @test Uint16 == typeof(groups(cf))
    @test_throws find(cf, convert(Int64, 1))
end

polymorphism_main()
