# Copyright 2014 Mitchell Kember. Subject to the MIT License.
# Google Code Jam Round 1A 2008
# Problem B: Milkshakes

# Determines whether customer c is satisfied by the milkshake malts ms.
function satisfied(c, ms)
	for (f, m) in c
		if ms[f] == m
			return true
		end
	end
	false
end

# Returns the first malted flavour in the preferences of customer c. If all
# flavours are unmalted, returns zero.
function firstmalted(c)
	i = findfirst(p -> p[2] == 1, c)
	i == 0 ? 0 : c[i][1]
end

# Returns the list of nf malts (0 or 1) such that the number of malted flavours
# is a minimum while satisfying the preferences of all customers in cs.
function minmalts(nf, cs)
	ms = zeros(Int, nf)
	done = false
	while !done
		done = true
		for c in cs
			if !satisfied(c, ms)
				f = firstmalted(c)
				if f == 0
					return nothing
				end
				ms[f] = 1
				done = false
			end
		end
	end
	ms
end

# Parse a string as a customer's milkshake preferences. The first integer is
# ignored (the number of preferences), and subsequent pairs of integers are
# parsed as (f, m) tuples where f is the flavour and m is the malt.
function parse_customer(str)
	xs = int(split(str))
	[(xs[i], xs[i+1]) for i in 2:2:length(xs)-1]
end

function main()
	n = int(readline())
	for i = 1:n
		nf = int(readline()) # number of flavours
		nc = int(readline()) # number of customers
		cs = map(ci -> parse_customer(readline()), 1:nc)
		ms = minmalts(nf, cs)
		str = (ms === nothing) ? "IMPOSSIBLE" : join(ms, " ")
		println("Case #$i: ", str)
	end
end

main()
