
for i in 1:10
    p = random_position(i, 9, 20)
    e = random_expression(rand(1:1000))
    @test GoCL.pack_expression(GoCL.unpack_expression(e)) == e
    d = evaluate(e, p)
    compare(fix(d), "expression/random-$i.txt")
    compare(moves(e, p, black), "expression/moves-$i.txt")
end

f = GoCL.pack_product((1, 2, false), (3, 4, true))
@test GoCL.pack_product(GoCL.unpack_product(f, 999)...) == f
f = GoCL.pack_addition((1, 2, false), (3, 4, true))
@test GoCL.pack_addition(GoCL.unpack_addition(f, 999)...) == f

p = random_position(1, 9, 20)
for i in 1:GoCL.given
    e = GoCL.Expression()
    push!(e, GoCL.pack_addition((i, 1, false)))
    d = fix(evaluate(e, p))
    compare(d, "expression/given-addition-$i.txt")
end

k = GoCL.pack_kernel(1, 2, (1, 2), [1 2; 3 4; 5 6])
@test GoCL.pack_kernel(GoCL.unpack_kernel(k, 999)...) == k

p = Position{9}()
move!(p, black, 3, 3)
e = GoCL.Expression()
push!(e, GoCL.pack_kernel(3, 0, (1, 1), ones(Int, 1, 1)))
d = fix(evaluate(e, p))
compare(d, "expression/given-kernel-1.txt")

p = Position{9}()
move!(p, black, 3, 3)
move!(p, white, 7, 7)
e = GoCL.Expression()
push!(e, GoCL.pack_kernel(3, 0, (1, 1), [0 0; 0 0; 0 1]))
d = fix(evaluate(e, p))
compare(d, "expression/given-kernel-2.txt")

