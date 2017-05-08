using ZMQ

# Phase 1: latency test.
function server_latency(s)
    println("Server entering phase 1")
    cont = true
    while cont
        #println("Server waiting for message")
        sender = bytestring(ZMQ.recv(s))
        @assert(sender == "client_id", "Received msg from unknown client $sender")
        #println("Server got a message!")
        msg = ZMQ.recv(s)
        io = seek(convert(IOStream, msg), 0)
        m = read(io, Int8)
        @assert(m == 42, "Received corrupted message.")
        cont = read(io, Bool)
        ZMQ.send(s, "client_id", SNDMORE)
        ZMQ.send(s, Message("ack"))
    end
    println("Server finished phase 1")
    nothing
end

# Phase 2: Throughput test
function server_throughput(s)
    println("Server entering phase 2")
    cont = true
    correct_num_bytes = 2^14
    i = 0
    while cont
        #println("Server waiting for message")
        sender = bytestring(ZMQ.recv(s))
        @assert(sender == "client_id", "Received msg from unknown client $sender")
        msg = ZMQ.recv(s)
        #println("Server got a message!")
        io = seek(convert(IOStream, msg), 0)
        cont = read(io, Bool)
        num_bytes = read(io, Int32)
        @assert(num_bytes == correct_num_bytes,
                "Received corrupted message $num_bytes")

        #A = map(ntoh, read(io, Uint8, num_bytes))
        # Comment this out for a better network bandwidth assessment.
        #for i = 1:num_bytes
        #  @assert(A[i] == (i % typemax(Uint8)), "Message A is corrupted.")
        #end
        i = i + 1
        #println("Bytes verified")
    end
    ZMQ.send(s, "client_id", SNDMORE)
    ZMQ.send(s, Message("ack"))
    println("Server finished phase 2. Received $i msgs.")
    nothing
end
