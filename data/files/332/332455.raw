using ZMQ

# Phase 1: latency test.
function latency(s, num_iters)
    io = IOBuffer()
    for i = 1:num_iters
        truncate(io, 0)
        if (i == num_iters)
            write(io, Int8(42), false)
        else
            write(io, Int8(42), true)
        end
        ZMQ.send(s, "server_id", SNDMORE)
        ZMQ.send(s, Message(io))

        # Receive ack from server.
        sender = bytestring(ZMQ.recv(s))
        @assert(sender == "server_id", "Received msg from unknown client $sender")
        msg = ZMQ.recv(s)
        ret_msg = bytestring(msg)
        @assert(ret_msg == "ack", "Expecting 'ack', but got $ret_msg")
    end
end

function throughput(s, io, io2, num_iters)
    for i = 1:num_iters
        ZMQ.send(s, "server_id", SNDMORE)
        if (i == num_iters)
            ZMQ.send(s, Message(io2))
        else
            ZMQ.send(s, Message(io))
        end
    end
    # Receive final ack from server.
    sender = bytestring(ZMQ.recv(s))
    @assert(sender == "server_id", "Received msg from unknown client $sender")
    ack_msg = bytestring(ZMQ.recv(s))
    @assert(ack_msg == "ack", "Expecting 'ack', but got $ack_msg")
end
