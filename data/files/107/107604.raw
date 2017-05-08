
ops = GoCL.build_ops(100, 1)
for i in 1:10
    a, b = random_expression(100), random_expression(100)
    c = GoCL.weighted_rand(ops)(Vector[a, b])
    GoCL.unpack_expression(c)
end

d = random_population(100, 20)
evolve(d, 10, 1000, 9, 81, "dump.txt")
