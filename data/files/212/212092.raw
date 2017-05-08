HODIndex(client::HODClient, name::AbstractString) = HODIndex(client, utf8(name))

Base.length(index::HODIndex) = length(index.documents)

function Base.push!(index::HODIndex, document::UTF8String)
    push!(index.documents, document)
end

function Base.append!(index::HODIndex, documents::Vector{UTF8String})
    append!(index.documents, documents)
end

function commit(index::HODIndex; async::Bool = false)
    response = add_documents(index, async = async)
    empty!(index.documents)
    return response
end

add_document(index::HODIndex; async::Bool = false) = add_documents([doc], async)

function add_documents(index::HODIndex; async::Bool = false)
    documents = Dict("documents" => index.documents)
    data = Dict("json" => json(documents), "index" => index.name)
    response = post(
        index.client,
        "addtotextindex",
        data = data,
        files = Dict("fake" => ""),
        async = async
    )
end

Base.delete!(index::HODIndex) = delete_index(index.client, index.name)
