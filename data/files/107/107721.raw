
for i in 1:10
    p = random_position(i, 9, 20)
    e = random_expression(Go.lheader+Go.chunk*rand(1:100))
    @test Go.pack_expression(Go.unpack_expression(e)) == e
    d = evaluate(e, p, white)
    compare("expression/random-$i.txt", fix(d))
    compare("expression/moves-$i.txt", p, moves(e, [p], black))
end

f = Go.pack_product((1, 2, false), (3, 4, true))
@test Go.pack_product(Go.unpack_product(f, 999)...) == f
f = Go.pack_addition((1, 2, false), (3, 4, true))
@test Go.pack_addition(Go.unpack_addition(f, 999)...) == f

p = random_position(1, 9, 20)
for i in 1:Go.given_atom
    e = Go.Expression()
    push!(e, Go.pack_addition((i, 1, false)))
    d = fix(evaluate(e, p, black))
    compare("expression/given-addition-$i.txt", d)
end

# needs index
#k = Go.pack_kernel(1, 2, (1, 2), [1 2; 3 4; 5 6])
#@test Go.pack_kernel(Go.unpack_kernel(k, 999)...) == k

p = Position{9}()
move!(p, black, 3, 3)
e = Go.Expression()
push!(e, Go.pack_kernel(3, 0, (1, 1), 0, ones(Int, 1, 1)))
d = fix(evaluate(e, p, black))
compare("expression/given-kernel-1.txt", d)

p = Position{9}()
move!(p, black, 3, 3)
move!(p, white, 7, 7)
e = Go.Expression()
push!(e, Go.pack_kernel(3, 0, (1, 1), 0, [0 0; 0 0; 0 1]))
d = fix(evaluate(e, p, black))
compare("expression/given-kernel-2.txt", d)

p = Position{9}()
e = random_expression(Go.lheader+Go.chunk*rand(1:100))
move!(p, black, 5, 5)
for (i, (x,y)) in enumerate(((4,4),(4,5),(5,6),(4,6),(6,6),(6,5),(6,4),(5,4)))
    move!(p, white, x, y)
end

m = moves(e, [p], black)
@test !((5,5) in m)
compare("expression/move-eye.txt", p, m)

for i in 1:10
    e = random_expression(Go.lheader+Go.chunk*rand(1:10))
    println(bytes2hex(e))
    dump_expression(e)
end

e = Go.Expression()
push!(e, Go.pack_addition((Go.given_atom+1, 1, false)))
push!(e, Go.pack_kernel(1, 0.0, (1,1), 0, [-1 1; 0 0]))
dump_expression(Go.pack_expression(e))

for i in 1:100
    e = random_expression(Go.lheader+Go.chunk*rand(1:10))
    p = random_position(i, 9, 20)
    m = moves(e, [p], black)
    @test m == moves(e, [p], black)
end

# bug while running - 43a15a544bcce289 at 1005
#43a15a544bcce289:2
# 1 kernel(average, 23)
# -@
# 23 kernel(min, 25)
# ++  +
#--+ - 
#+++-O 
#+- --+
# 25 jump to score

encoded = "676f7870009701505dc1148702a45c88945f8e861e26239ac88d42e4847700e755b0ebeb77fe08812d2db9c809347d8e19ed40e042d2656ed6edb7cf7527670fe3bf122814793f6fb524101c5131d8584a1639deec0de1cf38601cdf65acbd4e72fe15706c030a05514e9ea9c7d23618ffcb145154c795e3458dba80337d693028c204f0e8c803f52ade5c5174c796cb491d1a68347529902831d8756a1039defc1c1a6834ddcb6bb424106dd8305d0d257097cc351db504693a3d8ac21b3f9de7d5b0eaeb55fe08a1296db9cc89347d86192dc0c842c3456ed6871837438a988d06ae867600e755b0abeb5576aab1397fb9fc15706c830a855139defc1de1cf38601cdf652cbd0e72fe15706c030a05514e9ea9c7d23618ffcb145154c795e3458dba80333d69302a8204f0e8c803f52bde1c5174c796cb491d1268b47529902831d8756a1039defc1c1268345dcb6bb425106dd8385d0d2570978c351db504697a3dcac21b379de7d5b06beb57fe08eb7acea691b3b11030077596727f4e6c5dc030354ced8b44993f541960979e351dbf2469fa9c30"
e = Go.Expression(hex2bytes(encoded))
dump_expression(e)
println(length(e.fragment))
index = Go.build_index(e)
println(index)
println(e.fragment[23])
println(Go.unpack_kernel(e.fragment[23], 23, index))
println(e.fragment[25])
println(Go.unpack_jump(e.fragment[25], length(e.fragment)-25))
