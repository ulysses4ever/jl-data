# Copyright 2014 Mitchell Kember. Subject to the MIT License.
# Google Code Jam Qualification Round 2009
# Problem A: Alien Language

# Determines whether the pattern pat matches the word w.
function ismatch(pat, w)
	for i = 1:length(w)
		if !in(w[i], pat[i])
			return false
		end
	end
	true
end

# Returns the number of words that the pattern pat matches.
nmatches(pat, words) = count(w -> ismatch(pat, w), words)

# Parses a string a pattern, returning a list of lists of characters. Ordinary
# letters in the pattern result in singleton lists, while letters enclosed in
# parentheses are grouped in the same list.
function parse_pattern(str)
	pat = Vector{Char}[]
	nested = false
	for c in str
		if !nested
			if c == '('
				push!(pat, [])
				nested = true
			else
				push!(pat, [c])
			end
		else
			if c == ')'
				nested = false
			else
				push!(last(pat), c)
			end
		end
	end
	pat
end

function main()
	_, nw, n = int(split(readline()))
	words = map(i -> chomp(readline()), 1:nw)
	for i = 1:n
		pat = parse_pattern(readline())
		nm = nmatches(pat, words)
		println("Case #$i: ", nm)
	end
end

main()
