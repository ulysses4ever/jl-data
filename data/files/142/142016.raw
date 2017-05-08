using Delta

universe = Collection([], [])
one = Source(hard(Delta(1)))
counter = Socket(0)

args = hard(Delta((socket_id(one), counter.id, counter.id)))
plus = Worker(+, no_sockets(), [Source(args)])
minus = Worker(+, no_sockets(), [Source(args)])

push!(universe, one)
push!(universe, plus)
push!(universe, minus)
push!(universe, counter)

run!(universe, 5)
