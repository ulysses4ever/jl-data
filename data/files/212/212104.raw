module HavenOnDemand

using JSON
using Requests

       # Types
export HODClient,
       HODIndex,
       HODSyncResponse,
       HODAsyncResponse,
       HODException,
       DocumentException,

       # Client
       create_index,
       parse_index,
       has_index,
       get_index,
       delete_index,
       list_indexes,
       post,
       post_async,
       call_API,
       get_async_result,

       # Index
       size,
       push_doc,
       push_docs,
       commit,
       add_doc,
       add_docs,
       delete,

       # Responses
       json,
       get_result

include("types.jl")
include("client.jl")
include("responses.jl")
include("index.jl")
include("exceptions.jl")

end # module
