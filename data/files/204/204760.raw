function numRotate(x)
	sx = string(x)
	cx = Char[]
	for i in [1:length(sx)]
		push!(cx, sx[i])
	end
	seq = map(x -> int(string(x)), cx)
	rotations = Int64[]
	for i in [1:length(seq)]
		back = splice!(seq, 1)
		seq = cat(1, seq, back)
		res = int(reduce(*, map(x -> string(x), seq)))
		push!(rotations, res)
	end
	rotations
end

function circlePrime(x)
	all(map(isprime, numRotate(x)))
end