##
# Utility methods
#########################################################
const _cache = Dict()
cache(k, v) = _cache[k] = v
cache_clear(k) = delete!(_cacle, k)
cache_clear() = empty!(_cache)
function cached_get(k, fn)
    v = get(_cache, k, nothing)
    (nothing != v) && return v
    cache(k, fn())
end

openable(path::File) = path
openable(path::String) = File(path)


# cache deserialized objs to help the simple search implementation speed up by preventing repeated loading of indices
as_deserialized(f::File) = as_deserialized(f.path)
function as_deserialized(path::String)
    io = as_io(path)
    obj = deserialize(io)
    close(io)
    obj
end

function preprocess(entity::Union(StringDocument,Corpus))
    #prepare!(entity, strip_corrupt_utf8 | strip_case)
    prepare!(entity, strip_case)
    remove_html_tags!(entity)
    prepare!(entity, strip_whitespace | strip_non_letters | strip_articles | strip_prepositions | strip_pronouns | strip_stopwords)
    stem!(entity)

    if isa(entity, Corpus)
        standardize!(entity, TokenDocument)
    else
        entity = convert(TokenDocument, entity)
    end
    entity
end

as_serialized(obj, f::File) = as_serialized(obj, f.path)
function as_serialized(obj, path::String)
    iob = IOBuffer()
    serialize(iob, obj)

    io = open(path, "w")
    write(io, takebuf_array(iob))
    close(io)
    close(iob)
    path
end

function setup_folders(clean::Bool=false, everywhere::Bool=true)
    if everywhere
        for p in procs()
            remotecall_fetch(p, setup_folders, clean, false)
        end
    else
        println("Setting up work folders...")
        clean && isdir(fs_pfx) && rm(fs_pfx; recursive=true)
        for d in [fs_pfx, part_idx_location, doc_to_id_location, id_to_doc_location, stat_location, docs_location]
            isdir(d) || mkdir(d)
        end
        nothing
    end
end
