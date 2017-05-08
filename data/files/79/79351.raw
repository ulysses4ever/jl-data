module Helpme

export @helpme

global database = Dict()
macro example(fn, suggestion)
	global database
	fnstr = string(fn)
	quote
		try
			$(esc(fn))()
		catch e
			database[(repr(e), $fnstr)] = $suggestion
		end
	end
end

include("examples.jl")

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
	(k1, k2) = key
	(d1, d2) = (levenshtein(k1,repr(e)), levenshtein(k2,s))
	(w1, w2) = (10, 1)
	return sqrt(d1*d1*w1+d2*d2*w2)
end

function search(e, s)
	global database
	msg = "No suggestions found. Sorry :("
	dist = Inf
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
			$(esc(ex))
		catch e
			search(e, $s)
		end
	end
end

end