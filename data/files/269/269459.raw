using ZMQ

if (length(ARGS) != 2)
  println("Usage: julia client.jl server_ip server_port")
  quit()
end

ip = ARGS[1]
port = int32(ARGS[2])

ctx = Context(1)
s = Socket(ctx, ROUTER)
ZMQ.set_identity(s, "client_id")
ZMQ.connect(s, "tcp://$ip:$port")

# Phase 1: latency test.
tic()
num_iters = 1000
for i = 1:num_iters
  io = IOBuffer()
  if (i == num_iters)
    write(io, int8(42), false)
  else
    write(io, int8(42), true)
  end
  ZMQ.send(s, "server_id", SNDMORE)
  ZMQ.send(s, Message(io))

  # Receive ack from server.
  sender = bytestring(ZMQ.recv(s))
  @assert(sender == "server_id", "Received msg from unknown client $sender")
  msg = ZMQ.recv(s)
  @assert(bytestring(msg) == "ack", "Expecting 'ack', but got $ret_msg")
end
time = toq()
println("Latency: $(time / num_iters)s")


# Phase 2: Throughput test
println("Client entering phase 2")
num_bytes = 2^14  # 16KB
A = Array(Uint8, num_bytes)
for i = 1:num_bytes
  A[i] = i % typemax(Uint8)
end

A = repeat("1", 2^14)
tic()
io = IOBuffer()
write(io, true, int32(num_bytes), A)
for i = 1:num_iters
  if (i == num_iters)
    io = IOBuffer()
    write(io, false, int32(num_bytes), A)
  end
  #=
  io = IOBuffer()
  if (i == num_iters)
    #write(io, false, int32(num_bytes), map(hton, A))
    write(io, false, int32(num_bytes), A)
  else
    write(io, true, int32(num_bytes), A)
  end
  =#
  ZMQ.send(s, "server_id", SNDMORE)
  ZMQ.send(s, Message(io))
  #println("Client done with iter $i")
end
# Receive final ack from server.
sender = bytestring(ZMQ.recv(s))
@assert(sender == "server_id", "Received msg from unknown client $sender")
ack_msg = bytestring(ZMQ.recv(s))
@assert(ack_msg == "ack", "Expecting 'ack', but got $ack_msg")
time = toq()
println(string("Throughput: $(num_bytes * num_iters / time) bytes/s ",
"($num_iters msgs, time: $time)"))
