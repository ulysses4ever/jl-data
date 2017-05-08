
for i in 1:10
    p = random_position(i, 9, 20)
    e = random_expression(rand(1:1000))
    @test GoCL.pack(GoCL.unpack(e)) == e
    d = evaluate(e, p)
    compare(fix(d), "expression/random-$i.txt")
end

p = random_position(1, 9, 20)
#println(p)
for i in 1:GoCL.given
    e = GoCL.Expression()
    # poly length 1, index i, scale 1, power 1
    # (scale is 10 to counteract poly scaling)
    push!(e, GoCL.Fragment(GoCL.polynomial, [0x80, UInt8(i-1), GoCL.f2b(10.0), 0x05]))
    d = evaluate(e, p)
    compare(d, "expression/given-poly-$i.txt")
end

