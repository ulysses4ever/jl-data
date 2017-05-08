# TF-IDF style scoring
function score(count::Int, idx::PkgIndex, term::String, pkg::String)
	return count / (log(idx.terms[term]) * log1p(idx.packages[pkg]))
end

# Load inverse index from disk: keep cached in memory
function search(query::String, idx::PkgIndex)
	terms = split(lowercase(query), r"\s")
	resset = Dict{UTF8String, Float64}()
	for term in terms
		pkgs = get(idx.invindex, term, Dict{UTF8String, Int}())
		for (pkg, count) in pkgs
			resset[pkg] = get(resset, pkg, 0.0) + score(count, idx, term, pkg)
		end
	end
	bestpkgs = sort(collect(keys(resset)), by = k -> resset[k])
	return bestpkgs[1:min(length(bestpkgs), 10)]
end
