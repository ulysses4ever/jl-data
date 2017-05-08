##
# Searching
##########################################################

function search_part_idx(file, terms::Array, mapto_url=true, limit=10)
    part_idx = cached_get(file, ()->as_deserialized(file))
    results = IntSet()
    for term in terms
        union!(results, get(part_idx, term, []))
    end
    if limit > 0
        while length(results) > limit
            pop!(results)
        end
    end

    if mapto_url
        id_map_file = joinpath(id_to_doc_location, basename(file))
        id_to_doc = cached_get(id_map_file, ()->as_deserialized(openable(id_map_file)))
        result_docs = map(id->get(id_to_doc, id, ""), results)
        return Set(filter(x->!isempty(x), result_docs))
    else
        return Set(results)
    end
end

function search_index(terms::String)
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

    result_docs = @parallel union for i in 1:nworkers()
        local_files = {}
        for b in localpart(master_idx)
            append!(local_files, b)
        end
        reduce(union, map(file->search_part_idx(file, terms), local_files))
    end
    result_docs
end
