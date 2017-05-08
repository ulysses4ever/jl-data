module Helpme

export @helpme

global keybase = {}
global database = Dict()
macro example(fn, suggestion)
	global database
	global keybase
	fnstr = string(fn)
	quote
		try
			$(esc(fn))()
			info("An example did not raise an error: "*$suggestion)
		catch e
			key = (repr(e), $fnstr)
			database[key] = $suggestion
			push!(keybase, key)
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

flatten(s::Symbol) = {s}
function flatten(e::Expr)
	flat = {}
	push!(flat, string(e.head))
	for arg in e.args
		append!(flat, isa(arg, Expr)? flatten(arg) : [arg])
	end

	return flat
end

function quelm(q)
	return flatten(eval(parse(":("*q*")")))
end

#weights = (50, 0, 50, 1) # 3
#weights = (85, 56, 38, 1) # 2.65
weights = (67, 54, 54, 0.2) # 2.24
# weights = (100rand(), 100rand(), 100rand(), 100rand())
function distance(key, e, s)
	global weights
	(k1, k2) = key
	d1 = levenshtein(quelm(k1), quelm(repr(e)))
	d2 = levenshtein(quelm(k2), quelm(s))
	d3 = levenshtein(k1, repr(e))
	d4 = levenshtein(k2, s)
	(w1, w2, w3, w4) = weights
	return sqrt(d1*d1*w1 + d2*d2*w2 + d3*d3*w3 + d4*d4*w4)
end

function search(e, s)
	global database
	results = {}
	for key in keys(database)
		d = distance(key, e, s)
		push!(results, (d, key, database[key]))
	end

	sort!(results, by=first)
	return results[1:3]
end

macro helpme(ex)
	s = string(ex)
	quote
		try
			$(esc(ex))
		catch e
			results = search(e, $s)
			deletes = Int[]
			messages = Dict()
			for i in 1:length(results)
				if haskey(messages, results[i][3])
					push!(deletes, i)
				else
					messages[results[i][3]] = true
				end
			end

			for del in reverse(deletes)
				deleteat!(results, del)
			end

			if length(results) < 3
				push!(results, (0, (), "TODO nice fallback message here"))
			end

			for (d, id, msg) in results
				info(msg)
			end

			rethrow(e)
		end
	end
end

end