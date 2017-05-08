immutable PkgIndex
	# Packages to 1-grams with counts
	index::Dict{UTF8String, Dict{UTF8String, Int}}
	# 1-grams to packages with counts
	invindex::Dict{UTF8String, Dict{UTF8String, Int}}
	# Overall counts per word
	terms::Dict{UTF8String, Int}
	# Overall counts per package
	packages::Dict{UTF8String, Int}
end

function PkgIndex()
	PkgIndex(Dict{UTF8String, Dict{UTF8String, Int}}(),
	         Dict{UTF8String, Dict{UTF8String, Int}}(),
	         Dict{UTF8String, Int}(),
	         Dict{UTF8String, Int}())
end

function finddocs(pkgpath::String)
	readme = joinpath(pkgpath, "README.md")
	if isfile(readme)
		return UTF8String[readme]
	else
		return UTF8String[]
	end
end

function indexdoc!(package::String, docpath::String, idx::PkgIndex)
	# Read in the full text of the doc
	doc = convert(StringDocument, FileDocument(docpath))

	# Drop non-letters. TextAnalysis is broken in that regard.
	remove_case!(doc)
	remove_punctuation!(doc)
	remove_whitespace!(doc)

	# Get 1-grams
	onegrams = ngrams(doc, 1)

	for (term, count) in onegrams
		if !haskey(idx.index, package)
			idx.index[package] = Dict{UTF8String, Int}()
		end
		idx.index[package][term] =
		  get(idx.index[package], term, 0) + count
		if !haskey(idx.invindex, term)
			idx.invindex[term] = Dict{UTF8String, Int}()
		end
		idx.invindex[term][package] =
		  get(idx.invindex[term], package, 0) + count
		idx.terms[term] = get(idx.terms, term, 0) + count
		idx.packages[package] =
		  get(idx.packages, package, 0) + count
	end
	return
end

function indexpkgs()
	idx = PkgIndex()
	paths = readdir(Pkg.dir())
	for path in paths
		if ispath(joinpath(Pkg.dir(path), "README.md"))
			# Is a package and worth indexing
			pdir = Pkg.dir(path)
			docpaths = finddocs(pdir)
			for docpath in docpaths
				indexdoc!(path, docpath, idx)
			end
		end
	end
	return idx
end
