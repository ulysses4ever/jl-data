
ops = Go.build_ops(100, 1)
for i in 1:10
    a, b = random_expression(Go.lheader+Go.chunk*12), random_expression(Go.lheader+Go.chunk*12)
    c = Go.weighted_rand(ops)(Vector[a, b])
    Go.unpack_expression(c)
end

#d = random_population(Go.lheader+Go.chunk*50, 50)
#evolve(d, 19, 1000, 25, 10000, "../evol-1.dump")

d = longest_lived("../evol-1.log", "../evol-1.dump", 50, 0.5; n2=100)
evolve(d, 19, 1000, 25, 10000, "../evol-2.dump")
