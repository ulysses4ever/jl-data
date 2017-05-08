using HttpServer, LevelDB

db_path = if haskey(ENV, "KEYVAL_DIR") ENV["KEYVAL_DIR"] else "/tmp/keyval" end
db = open_db(db_path, true)

http = HttpHandler() do req::Request, res::Response
  if req.method == "GET"
    res.data = db_get(db, req.resource)
  elseif req.method == "POST" || req.method == "PUT"
    parts = split(req.resource, '=')
    db_put(db, parts[1], parts[2], length(parts[2]))
  end
  res.status = 200
  res
end

server = Server(http)
port = 7000
run(server, port)
info("Keyval server running on $port")
run(server, host=IPv4(127,0,0,1), port=port)
