using PkgUtils
using JSON

idx = PkgUtils.indexpkgs()

using HttpServer

# Build the request handler
http = HttpHandler() do req::Request, res::Response
    if ismatch(r"^/search/\?query=", req.resource)
        query = replace(req.resource, "/search/?query=", "")
        query = replace(query, "+", " ")
        results = PkgUtils.search(query, idx)
        return Response(JSON.json(results))
    else
        return Response(400, "Error: invalid URL")
    end
end

# Basic event handlers
http.events["error"]  = ( client, err ) -> println( err )
http.events["listen"] = ( port )        -> println("Listening on $port...")

# Boot up the server
server = Server(http)
run(server, 8000)
