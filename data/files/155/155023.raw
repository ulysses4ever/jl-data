using HttpServer
using Httplib
using Websockets

red = "\"white\""
green = "\"black\""
function construct_frame(data)
  arr = fill(green,size(data)...)
  h,w = size(data)
  for i=1:h,j=1:w
    arr[i,j] = data[i,j] ? green : red
  end
  return arr
end

addprocs({"node011","node012","node013"})
require("gameoflife.jl")

wsh = WebsocketHandler() do req::Request, ws::Websocket
  firststep = zeros(Bool,100,100)
  firststep[1,2] = true
  firststep[2,3] = true
  firststep[3,1] = true
  firststep[3,2] = true
  firststep[3,3] = true
  dprev = distribute(firststep)
  while true
    arr = construct_frame(firststep)
    write(ws,"[$(join(arr,","))]")
    step!(dprev,firststep,4)
  end
end

file = readall("/home/leah/conway.html")
http = HttpHandler() do req::Request, res::Response
    Response(file)
end

http.events["error"]  = ( client, err ) -> println( err )
http.events["listen"] = ( port )        -> println("Listening on $port...")

server = Server(http,wsh )
run( server, 80 )
