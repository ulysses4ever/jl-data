
for i in 1:10
    p = random_position(i, 9, 20)
    e = random_expression(rand(1:1000))
    @test GoCL.pack_expression(GoCL.unpack_expression(e)) == e
    d = evaluate(e, p)
    compare(fix(d), "expression/random-$i.txt")
end

f = GoCL.pack_polynomial((1, 2, 3), (2, 3, 4))
@test GoCL.pack_polynomial(GoCL.unpack_polynomial(f, 999)...) == f

p = random_position(1, 9, 20)
#println(p)
for i in 1:GoCL.given
    e = GoCL.Expression()
    push!(e, GoCL.pack_polynomial((i, 1, 1)))
    d = fix(map(GoCL.b2f, evaluate(e, p)))
    compare(d, "expression/given-poly-$i.txt")
end

#p = Position{9}()
#move!(p, black, 3, 3)
#move!(p, white, 7, 7)
#e = GoCL.Expression()
#push!(e, 
