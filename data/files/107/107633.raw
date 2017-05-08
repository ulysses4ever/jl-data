
ops = Go.build_ops(100, 1)
for i in 1:10
    a, b = random_expression(Go.lheader+Go.chunk*12), random_expression(Go.lheader+Go.chunk*12)
    c = Go.weighted_rand(ops)(Vector[a, b])
    Go.unpack_expression(c)
end

d = random_population(Go.lheader+Go.chunk*50, 100)
evolve2(d, 19, 1000, 50, 10000, "../evol-1.dump")

#d = final_gen("../evol-b.log", "../evol-b.dump", 100, 0.9)
#evolve2(d, 19, 1000, 50, 10000, "../evol-c.dump")
