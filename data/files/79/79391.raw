module Helpme

export @helpme

features(q::String) = unique(flatten(quote;$(parse(q));end))
features(q)         = features(repr(q))
flatten(s::Symbol)  = {s}
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
	suggestion::Symbol
	efeatures::Array
	sfeatures::Array
	weights::Dict{Any,Int}
	Example(s::Symbol) = new(s, {}, {}, Dict())
	function Example(e::Exception, f::String, s::Symbol)
		weights = Dict{Any,Int}()
		efeatures = features(e)
		sfeatures = features(f)
		for feature in efeatures
			weights[feature] = 1
		end

		for feature in sfeatures
			weights[feature] = 1
		end

		new(s, efeatures, sfeatures, weights)
	end
end

################################################################################

const database = Example[]
const suggbase = Dict{Symbol, String}()
const testbase = (Exception, String, Symbol)[]
macro example(suggestion, ex)
	exstr = string(ex)
	quote
		try
			$(esc(ex))
			warn("An example did not raise an error: "*$suggestion)
		catch e
			push!(database, Example(e, $exstr, $suggestion))
		end
	end
end

macro testcase(suggestion, ex)
	exstr = string(ex)
	quote
		try
			$ex
			warn("A testcase did not raise an error: "*$suggestion)
		catch e
			push!(testbase, (e, $exstr, $suggestion))
		end
	end
end

include("suggestions.jl")
include("examples.jl")
include("testcases.jl")

################################################################################

function distance2(example, efeatures, sfeatures, erepr, s)
	dist = 0
	for feature in example.efeatures
		if !(feature in efeatures)
			dist += example.weights[feature]
		end
	end

	for feature in example.sfeatures
		if !(feature in sfeatures)
			dist += example.weights[feature]
		end
	end

	return dist
end

function search(e::Exception, s::String)
	examples = Example[]
	dists = Float64[]
	max_dist = 0
	efeatures = features(e)
	sfeatures = features(s)
	erepr = repr(e)
	for example in database
		dist = distance2(example, efeatures, sfeatures, erepr, s)
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

################################################################################

function reroll(example, adj)
	for (feature, weight) in example.weights
		if rand() < 0.5
			example.weights[feature] += adj
		end
	end
end

function train()
	info("Training database")
	clean = false
	while !clean
		clean = true
		for (error, fnstr, suggestion) in testbase
			results = search(error, fnstr)
			if !(suggestion in map(x->x.suggestion, results))
				clean = false
				for example in database
					if suggestion == example.suggestion
						reroll(example, -1)
					end
				end

				for result in results
					reroll(result, 1)
				end
			else
				# nothing
			end
		end
	end
end

function save()
	info("Saving database")
	open(joinpath(Pkg.dir(), "Helpme", "src", string("database.",VERSION,".jl")), "w") do f
		for (i, example) in enumerate(database)
			for (j, feature) in enumerate(example.efeatures)
				w = database[i].weights[database[i].efeatures[j]]
				println(f, "database[$i].weights[database[$i].efeatures[$j]]=$w")
			end

			for (j, feature) in enumerate(example.sfeatures)
				w = database[i].weights[database[i].sfeatures[j]]
				println(f, "database[$i].weights[database[$i].sfeatures[$j]]=$w")
			end
		end
	end
end

if isfile(joinpath(Pkg.dir(), "Helpme", "src", string("database.",VERSION,".jl")))
	include(string("database.",VERSION,".jl"))
else
	train()
	save()
end

################################################################################

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
				push!(results, Example(:DEFAULTMSG))
			end

			for example in results
				info(suggbase[example.suggestion])
			end

			rethrow(e)
		end
	end
end

end