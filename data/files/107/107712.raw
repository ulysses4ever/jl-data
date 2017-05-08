
for i in 1:10
    p = random_position(i, 9, 20)
    e = random_expression(Go.lheader+Go.chunk*rand(1:100))
    @test Go.pack_expression(Go.unpack_expression(e)) == e
    d = evaluate(e, p, white)
    compare("expression/random-$i.txt", fix(d))
    compare("expression/moves-$i.txt", 
            p, moves(e, [p], black, false, MersenneTwister(1)))
end

f = Go.pack_product((1, 2, false), (3, 4, true))
@test Go.pack_product(Go.unpack_product(f, 999)...) == f
f = Go.pack_addition((1, 2, false), (3, 4, true))
@test Go.pack_addition(Go.unpack_addition(f, 999)...) == f

p = random_position(1, 9, 20)
for i in 1:Go.given
    e = Go.Expression()
    push!(e, Go.pack_addition((i, 1, false)))
    d = fix(evaluate(e, p, black))
    compare("expression/given-addition-$i.txt", d)
end

k = Go.pack_kernel(1, 2, (1, 2), [1 2; 3 4; 5 6])
@test Go.pack_kernel(Go.unpack_kernel(k, 999)...) == k

p = Position{9}()
move!(p, black, 3, 3)
e = Go.Expression()
push!(e, Go.pack_kernel(3, 0, (1, 1), ones(Int, 1, 1)))
d = fix(evaluate(e, p, black))
compare("expression/given-kernel-1.txt", d)

p = Position{9}()
move!(p, black, 3, 3)
move!(p, white, 7, 7)
e = Go.Expression()
push!(e, Go.pack_kernel(3, 0, (1, 1), [0 0; 0 0; 0 1]))
d = fix(evaluate(e, p, black))
compare("expression/given-kernel-2.txt", d)

p = Position{9}()
e = random_expression(Go.lheader+Go.chunk*rand(1:100))
move!(p, black, 5, 5)
for (i, (x,y)) in enumerate(((4,4),(4,5),(5,6),(4,6),(6,6),(6,5),(6,4),(5,4)))
    move!(p, white, x, y)
end

m = moves(e, [p], black, false, MersenneTwister(1))
@test !((5,5) in m)
compare("expression/move-eye.txt", p, m)

e = random_expression(Go.lheader+Go.chunk*rand(1:10))
dump_expression(e)

e = Go.Expression()
push!(e, Go.pack_addition((Go.given+1, 1, false)))
push!(e, Go.pack_kernel(1, 0.0, (1,1), [-1 1; 0 0]))
dump_expression(Go.pack_expression(e))

for i in 1:100
    e = random_expression(Go.lheader+Go.chunk*rand(1:10))
    p = random_position(i, 9, 20)
    m = moves(e, [p], black, false, MersenneTwister(1))
    @test m == moves(e, [p], black, true, MersenneTwister(1))
end
