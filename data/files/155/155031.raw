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

function add_glider(arr,i::Int,j::Int)
  arr[i,j+1] = true
  arr[i+1,j+2] = true
  arr[i+2,j] = true
  arr[i+2,j+1] = true
  arr[i+2,j+2] = true
end

wsh = WebSocketHandler() do req::Request, ws::WebSocket
  firststep = zeros(Bool,100,100)
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

file = readall("conway.html")
http = HttpHandler() do req::Request, res::Response
    Response(file)
end

http.events["error"]  = ( client, err ) -> println( err )
http.events["listen"] = ( port )        -> println("Listening on $port...")

server = Server(http, wsh)
run(server, 8080)
