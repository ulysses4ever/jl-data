##
# Searching
##########################################################

function search_part_idx(file, terms::Array, mapto_url::Bool, limit::Int)
    results = search_part_idx(file, terms, mapto_url)
    if limit > 0
        while length(results) > limit
            pop!(results)
        end
    end
    results
end

function search_part_idx(file, terms::Array, mapto_url::Bool)
    results = search_part_idx(file, terms)

    if mapto_url
        id_map_file = joinpath(id_to_doc_location, basename(file))
        id_to_doc = cached_get(id_map_file, ()->as_deserialized(openable(id_map_file)))
        result_docs = map(id->get(id_to_doc, id, ""), results)
        return Set(filter(x->!isempty(x), result_docs))
    else 
        return Set(results)
    end
end

function search_part_idx(file, terms::Array)
    part_idx = cached_get(file, ()->as_deserialized(file))
    results = IntSet()
    for term in terms
        union!(results, get(part_idx, term, []))
    end
    results
end

function search_index(terms::String; mapto_url::Bool=true, limit::Int=10)
    sd = StringDocument(terms)
    td = preprocess(sd)
    terms = tokens(td)
    terms = filter(tok->!isempty(tok), terms)

    # The Blocks library provides many ways to divide work among processors.
    # Here, we call it on the part_idx_location directory, which tells it to
    # divide up the files in that directory.
    # The call localpart(master_idx) returns a list of files to be handled
    # by the calling processor.
    master_idx = cached_get(part_idx_location, ()->Block(openable(part_idx_location), false, 2))

    results = @parallel union for i in 1:nworkers()
        local_files = Any[]
        for b in localpart(master_idx)
            append!(local_files, b)
        end
        search_results = map(file->search_part_idx(file, terms, mapto_url, limit), local_files)
        isempty(search_results) ? Any[] : reduce(union, search_results)
    end
    if limit > 0
        while length(results) > limit
            pop!(results)
        end
    end
    collect(results)
end
