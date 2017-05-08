using HttpServer
using HttpCommon
using WebSockets
using JSON

function construct_frame(data)
  arr = fill("black",size(data)...)
  h,w = size(data)
  for i=1:h,j=1:w
    arr[i,j] = data[i,j] ? "black" : "white"
  end
  return arr
end

#addprocs({"node011","node012","node013"})
addprocs(3)
require("gameoflife.jl")

wsh = WebSocketHandler() do req::Request, ws::WebSocket
  firststep = zeros(Bool,100,100)

  #tessalate gliders
  for i=1:97,j=1:97
    if i % 5 == 1 && j % 5 == 1
      add_glider(firststep,i,j)
    end
  end

  dprev = distribute(firststep)
  while true
    arr = construct_frame(firststep)
    write(ws,json(arr))
    print(".")
    step!(dprev,firststep)
  end
end

file = readall("conway.html") #TODO: make this a mustache template
http = HttpHandler() do req::Request, res::Response
    Response(file)
end

server = Server(http, wsh)
println("Starting Server on port 8080")
run(server, 8080)
