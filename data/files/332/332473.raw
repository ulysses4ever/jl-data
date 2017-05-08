include("server_funcs.jl")

if (length(ARGS) != 1)
  println("Usage: julia server.jl server_port")
  quit()
end

port = parse(Int32, ARGS[1])
ctx = Context(1)
s = Socket(ctx, ROUTER)
ZMQ.set_identity(s, "server_id")
ZMQ.bind(s, "tcp://*:$port")

Base.precompile(server_latency, (typeof(s),))
Base.precompile(server_throughput, (typeof(s),))

server_latency(s)
server_throughput(s)

println("Server shutdown")
