include("client_funcs.jl")

if (length(ARGS) != 2)
  println("Usage: julia client.jl server_ip server_port")
  quit()
end

ip = ARGS[1]
port = parse(Int32, ARGS[2])

ctx = Context(1)
s = Socket(ctx, ROUTER)
ZMQ.set_identity(s, "client_id")
ZMQ.connect(s, "tcp://$ip:$port")

num_iters = 1000

Base.precompile(latency, (typeof(s), Int))

# Phase 1: Latency test
println("Client entering latency test")
tic()
latency(s, num_iters)
time = toq()
println("Latency: $(time / num_iters)s")


# Phase 2: Throughput test
num_bytes = 2^14  # 16KB
A = Array(UInt8, num_bytes)
for i = 1:num_bytes
  A[i] = i % typemax(UInt8)
end

io = IOBuffer()
write(io, true, Int32(num_bytes), A)
io2 = IOBuffer()
write(io2, false, Int32(num_bytes), A)

Base.precompile(throughput, (typeof(s), typeof(io), typeof(io2), Int))

println("Client entering throughput test")
tic()
throughput(s, io, io2, num_iters)
time = toq()
println(string("Throughput: $(num_bytes * num_iters / time) bytes/s ",
"($num_iters msgs, time: $time)"))
