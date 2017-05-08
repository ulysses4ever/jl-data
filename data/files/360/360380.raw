const port = 53354
const fs = 48000
const channels = 1
const frame_length_ms = 20
const stream_timeout_s = 2.0

const frame_length = div(fs*frame_length_ms,1000)
const localhost = ip"127.0.0.1"
const timeout_message = 0xff

type Stream
    # trace id
    trace_id::Uint32
    # client id
    app_id::Uint128
    # start time on server in samples (0 for first stream)
    start::Int64
    # lookahead of this stream in samples
    lookahead::Int
    # pointer to decoder object
    decoder::Ptr{Void}
    # audio data
    data::Vector{Int16}
    # last packet arrival time
    last_arrival::Float64

    function Stream(trace_id::Uint32, app_id::Uint128, lookahead::Integer)
        t = time()
        stream = new()
        stream.trace_id = trace_id
        stream.app_id = app_id
        stream.lookahead = lookahead
        stream.decoder = decoder_create(fs,channels)
        finalizer(stream,close)
        stream.data = Int16[]
        stream
    end
end

function Stream(trace_id::Uint32)
    Stream(trace_id, uint128(0), 0)
end

function close(stream::Stream)
    if stream.decoder != C_NULL
        decoder_destroy(stream.decoder)
        stream.decoder = C_NULL
    end
end

type FinishedStream
    trace_id::Uint32
    app_id::Uint128
    start::Int64
    data::Vector{Int16}
end

type Server
    socket::UdpSocket
    # true, if socket is bound succesfully
    bound::Bool
    # streams for current trace
    streams::Dict{Uint32,Stream}
    # starting time of current recording in seconds since epoch
    start::Float64
    # finished streams
    finished_streams::Vector{FinishedStream}
    recording::Bool

    function Server()
        server = new()
        server.socket = UdpSocket()
        server.bound = false
        server.streams = (Uint32 => Stream)[]
        # start is left uninitialized
        server.recording = false
        server.finished_streams = FinishedStream[]
        finalizer(server,close)
        server
    end
end

function close(server::Server)
    if server.bound
        Base.close(server.socket)
        server.bound = false
    end
end

function isrecording(server::Server)
    server.recording
end

function listen(server::Server)
    server.bound = bind(server.socket,IPv4(0),53354)
    server.bound
end

# the alpha and omega
function start()
    server = Server()
    if listen(server)
        timer = stream_timer()
        try
            loop(server)
        catch y
            if isa(y,InterruptException)
                # Most likely Ctrl-C
                return
            else
                rethrow(y)
            end
        finally
            stop_timer(timer)
            close(server)
        end
    end
end

function stream_timer()
    send_socket = UdpSocket()
    timer = Timer() do t
        send(send_socket,localhost,port,[timeout_message])
    end
    start_timer(timer,stream_timeout_s,stream_timeout_s)
    timer
end

function loop(server::Server)
    while true
        try
            data = recv(server.socket)
            handle(server,data)
        catch y
            if !isa(y,TypeError)
                rethrow(y)
            end
            println("recv: incomplete packet")
        end
    end
end

function handle(server::Server, data::Vector{Uint8})
    msg = data[1]
    if msg == timeout_message
        t = time()
        for (tid, s) in server.streams
            if s.last_arrival < t-stream_timeout_s
                println("timeout: tid=$(hex(tid))")
            end
        end
        return
    end
    trace_id = reinterpret(Uint32,data[2:5])[1]
    stream = get!(server.streams,trace_id) do
        Stream(trace_id)
    end
    stream.last_arrival = time()

    if msg == 0
        seq = reinterpret(Int32,data[6:9])[1]
        frame = data[10:end]
    elseif msg == 1
        handle_start(server, stream, data)
    elseif msg == 2
        handle_stop(server, stream, data)
    elseif msg == 3
        seq = reinterpret(Int32,data[6:9])[1]
        frame = data[10:end]
        println("skip frame received")
    elseif msg == 4
        seq = reinterpret(Int32,data[6:9])[1]
        skipped = reinterpret(Int32,data[10:13])[1]
        frame = data[14:end]
        println("resume frame received")
    else
        println("invalid message")
    end
end

function handle_start(server::Server, stream::Stream, data::Vector{Uint8})

    # parse message
    lookahead = reinterpret(Int32,data[6:9])[1]
    app_id = reinterpret(Uint128,data[10:25])[1]

    stream.lookahead = lookahead
    stream.app_id = app_id

    # create stream
    if isrecording(server)
        stream.start = int64((time()-server.start)*fs)
    else
        server.recording = true
        server.start = time()
        stream.start = 0
        println("start recording")
    end

    println(string("  start trace: tid=$(hex(stream.trace_id)), ",
                   "app_id=$(hex(app_id)), ",
                   "lookahead=$lookahead"))
end

function handle_stop(server::Server, stream::Stream, data::Vector{Uint8})
    len = length(stream.data)

    # parse message
    seq = reinterpret(Int32,data[6:9])[1]

    # increase data size
    total_len = (seq-1)*frame_length
    sizehint(stream.data, total_len)
    for i=1:total_len-len
        push!(stream.data,0)
    end

    # compute final start time (delay)
    # TODO: some fancy autocorrelation thing

    # create finished stream
    finished_stream = FinishedStream(stream.trace_id, stream.app_id,
        stream.start, stream.data)
    push!(server.finished_streams,finished_stream)

    # release stream
    pop!(server.streams,stream.trace_id)
    close(stream)

    println("  stop trace:  tid=$(hex(stream.trace_id))")

    # stop recording if no more streams are left
    if isempty(server.streams)
        stop_recording(server)
    end
end

function stop_recording(server::Server)
    println("recording stopped")

    # TODO: do something real
    server.recording = false
    empty!(server.finished_streams)
end

