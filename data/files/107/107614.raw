
ops = Go.build_ops(100, 1)
for i in 1:10
    a, b = random_expression(100), random_expression(100)
    c = Go.weighted_rand(ops)(Vector[a, b])
    Go.unpack_expression(c)
end

d = random_population(200, 50)
evolve(d, 9, 54, true, 25, 10000, "../evol-2.dump", Direct(MersenneTwister(1)))
