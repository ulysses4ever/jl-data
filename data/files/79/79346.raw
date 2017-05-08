module Helpme

export @helpme
import Base: search

const database = [
	"MethodError(+,#\"" =>
		"Strings are concatenated with the * operator, not the + operator.",
	"MethodError(convert,(ASCIIString,#merge(" =>
		"Julia attempts to choose the proper type for Dicts when [brackets] are used, and merge can be fussy when types don't match up. To force Julia to assign the type Dict{Any,Any}, use {braces} in your variable definitions for Dicts."
]


function levenshtein(a, b, len_a=length(a), len_b=length(b))
	if a == b
		return 0
	elseif len_a == 0
		return len_b
	elseif len_b == 0
		return len_a
	else
		v0 = [i for i in 0:len_b]
		v1 = zeros(length(v0))
		for i in 1:len_a
			v1[1] = i
			for j in 1:len_b
				cost = a[i]==b[j]? 0 : 1
				v1[j+1] = minimum([
					v1[j]+1,
					v0[j+1]+1,
					v0[j]+cost
				])
			end

			for j in 1:length(v1)
				v0[j] = v1[j]
			end
		end

		return last(v1)
	end
end

function distance(key, e, s)
	(k1, k2) = split(key, '#')
	(d1, d2) = (levenshtein(k1,repr(e)), levenshtein(k2,s))
	(w1, w2) = (2, 1)
	return sqrt(d1*d1*w1+d2*d2*w2)
end

function search(e, s)
	global database
	msg = "No suggestions found. Sorry :("
	dist = sqrt(2*length(repr(e))^2 + length(s)^2)
	for key in keys(database)
		d = distance(key, e, s)
		if d < dist
			msg = database[key]
			dist = d
		end
	end

	info(msg)
	rethrow(e)
end

macro helpme(ex)
	s = string(ex)
	quote
		try
			$ex
		catch e
			search(e, $s)
		end
	end
end

end