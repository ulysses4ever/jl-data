module Helpme

export @helpme

quelm(q::String) = flatten(eval(parse(":("*q*")")))
flatten(s::Symbol) = {s}
function flatten(e::Expr)
	flat = {}
	push!(flat, string(e.head))
	for arg in e.args
		append!(flat, isa(arg, Expr)? flatten(arg) : [arg])
	end

	push!(flat, e.typ)
	return flat
end

type Example
	error::Exception
	erepr::String
	fnstr::String
	suggestion::String
	equelm::Array
	squelm::Array
	Example(s::String) = new(KeyError(""), "", "", s, {}, {})
	Example(e::Exception, f::String, s::String) =
		new(e, repr(e), f, s, quelm(repr(e)), quelm(f))
end

const database = {}
macro example(fn, suggestion)
	fnstr = string(fn)
	quote
		try
			$(esc(fn))()
			warn("An example did not raise an error: "*$suggestion)
		catch e
			push!(database, Example(e, $fnstr, $suggestion))
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

r() = 1 #r(5)
r(n) = 2sum([rand() for i in 1:n])/n
const weights = (44r(), 38r(), 21r(), 33r())
function distance(example, equelm, squelm, erepr, s)
	d1 = levenshtein(example.equelm, equelm) / length(equelm)
	d2 = levenshtein(example.squelm, squelm) / length(squelm)
	d3 = levenshtein(example.erepr, erepr)   / length(erepr)
	d4 = levenshtein(example.fnstr, s)       / length(s)
	(w1, w2, w3, w4) = weights
	dist = sqrt(d1*d1*w1 + d2*d2*w2 + d3*d3*w3 + d4*d4*w4)
	return dist
end

function search(e::Exception, s::String)
	examples = Example[]
	dists = Float64[]
	max_dist = 0
	equelm = quelm(repr(e))
	squelm = quelm(s)
	erepr = repr(e)
	for example in database
		dist = distance(example, equelm, squelm, erepr, s)
		if length(examples) < 3
			push!(examples, example)
			push!(dists, dist)
			max_dist = max(dist, max_dist)
		elseif dist < max_dist
			for i in 1:3
				if dist < dists[i]
					example, examples[i] = examples[i], example
					dist, dists[i] = dists[i], dist
				end

				max_dist = maximum(dists)
			end
		end
	end

	for i in [1, 2, 1]
		if dists[i+1] < dists[i]
			examples[i+1], examples[i] = examples[i], examples[i+1]
			dists[i+1], dists[i] = dists[i], dists[i+1]
		end
	end

	return examples
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
				if haskey(messages, results[i].suggestion)
					push!(deletes, i)
				else
					messages[results[i].suggestion] = true
				end
			end

			for del in reverse(deletes)
				deleteat!(results, del)
			end

			if length(results) < 3
				push!(results, Example("Helpme not helping? Report an issue at <https://github.com/snotskie/Helpme.jl/issues>."))
			end

			for example in results
				info(example.suggestion)
			end

			rethrow(e)
		end
	end
end

end