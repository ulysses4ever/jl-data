
ops = Go.build_ops(100, 1)
for i in 1:10
    a, b = random_expression(Go.lheader+Go.chunk*12), random_expression(Go.lheader+Go.chunk*12)
    c = Go.weighted_rand(ops)(Vector[a, b])
    Go.unpack_expression(c)
end

d = random_population(Go.lheader+Go.chunk*50, 50)
#evolve(d, 19, 180, true, 25, 10000, "../evol-2.dump", Direct(MersenneTwister(1)))
evolve(d, 9, 54, true, 25, 10000, "../evol-2.dump", Direct(MersenneTwister(1)))
