function start()
    socket = UdpSocket()
    ip = ip"0.0.0.0"
    port = 53354
    fs = 48000
    channels = 1
    enc = encoder_create(fs, channels)
    try
        listen(socket,ip,port)
    catch y
        if isa(y, InterruptException)
            return
        else
            throw(y)
        end
    finally
        encoder_destroy(enc)
        close(socket)
    end
end

function listen(socket,ip,port)
    if !bind(socket,ip,port)
        return
    end
    while true
        data = recv(socket)
        process(data)
    end
end

function process(data)
    msg = data[1]
    trace_id = reinterpret(Uint32,data[2:5])[1]
    if msg == 0
        seq = reinterpret(Int32,data[6:9])[1]
        frame = data[10:]
    elseif msg == 1
        lookahead = reinterpret(Int32,data[6:9])[1]
        app_id = reinterpret(Uint128,data[10:25])[1]
        println(string("start trace: tid=$(hex(trace_id)), ",
                       "app_id=$(hex(app_id)), ",
                       "lookahead=$lookahead"))
    elseif msg == 2
        seq = reinterpret(Int32,data[6:9])[1]
        println("stop trace:  tid=$(hex(trace_id))")
    elseif msg == 3
        seq = reinterpret(Int32,data[6:9])[1]
        frame = data[10:]
        println("skip frame received")
    elseif msg == 4
        seq = reinterpret(Int32,data[6:9])[1]
        skipped = reinterpret(Int32,data[10:13])[1]
        frame = data[14:]
        println("resume frame received")
    else
        println("invalid message")
    end
end

