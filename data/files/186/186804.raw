#!/usr/bin/env julia

include("redis.jl")
using Redis
using FactCheck

blacklisted_ports = []

port_list_cmd = `netstat -an` |> `grep '^tcp'` |> `grep LISTEN` |> `grep -v LISTENING`
function get_ports_in_use()
    ports = []
    open(port_list_cmd) do stream
        while !eof(stream)
            line = chomp(readline(stream))
            m = match(r"^\S+\s+\S+\s+\S+\s+[.:0-9]+:([0-9]+)\s+.+", line)
            if m != nothing
                ports = vcat(ports, int(m.captures[1]))
            end
        end
    end
    ports
end

function start_server(first_port::Integer=6380, last_port::Integer=7000; pass=nothing)
    bad_ports = vcat(get_ports_in_use(), blacklisted_ports)
    for port in first_port:last_port
        if in(port, bad_ports)
            continue
        end
        if pass == nothing
            cmd = `redis-server --port $port`
        else
            cmd = `redis-server --port $port --requirepass $pass`
        end
        try
            spawn(cmd)
            println("Redis server running on port $port.")
            return port
        catch
            continue
        end
    end
end

facts("Start, Ping, Shutdown") do
    global blacklisted_ports
    port = start_server()
    sleep(0.2)
    conn = connect(LOCALHOST, port)
    @fact ping(conn) => "PONG"
    @fact_throws shutdown(conn)
    close(conn)
    @fact in(port, get_ports_in_use()) => false
    blacklisted_ports = vcat(blacklisted_ports, port)
end

facts("Password authentication") do
    global blacklisted_ports
    port = start_server(pass="AL0ngButUn1mag1nat1vePassw0rdJustF0rTest1ng")
    sleep(0.2)
    conn = connect(LOCALHOST, port)
    @fact_throws ping(conn)
    @fact auth(conn, "AL0ngButUn1mag1nat1vePassw0rdJustF0rTest1ng") => "OK"
    @fact ping(conn) => "PONG"
    @fact_throws shutdown(conn)
    close(conn)
    blacklisted_ports = vcat(blacklisted_ports, port)
end

facts("Test Basic Functionality") do
    global blacklisted_ports
    port = start_server()
    sleep(0.2)
    conn = connect(LOCALHOST, port)
    context("Verify that we have a connection and the DB is empty") do
        @fact ping(conn) => "PONG"
        @fact keys(conn) => []
        @fact echo(conn, "Hello There!") => "Hello There!"
        @fact select(conn, 2) => "OK"
    end
    context("Quit and reconnect") do
        @fact quit(conn) => nothing
        sleep(0.2)
        @fact isopen(conn) => false
        conn = connect(LOCALHOST, port)
        @fact ping(conn) => "PONG"
    end
    context("Basic DB & key manipulation") do
        @fact dbsize(conn) => 0
        @fact set(conn, "one", "aardvark") => "OK"
        @fact get(conn, "one") => "aardvark"
        @fact set(conn, "two", "bacon") => "OK"
        @fact dbsize(conn) => 2
        @fact select(conn, 3) => "OK"
        @fact dbsize(conn) => 0
        @fact keys(conn) => []
        @fact select(conn, 0) => "OK"
        @fact dbsize(conn) => 2
        @fact sort(keys(conn)) => ["one", "two"]
        @fact flushdb(conn) => "OK"
        @fact dbsize(conn) => 0
    end
    context("*SET* and similar commands should return OK")
        # \\  Strings  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
        @fact set(conn, "stipulations", "cattiest", 10, EX, XX) => 0
        @fact set(conn, "hefty", "engages", 10, EX, NX) => "OK"
        @fact set(conn, "hefty", "vanquish", 10, EX, NX) => nothing
        @fact set(conn, "hefty", "glorying", 10, EX, XX) => "OK"
        @fact set(conn, "ducklings", "transmuting", 17, PX) => "OK"
        @fact set(conn, "hawks", "villains", XX) => 0
        @fact set(conn, "hawks", "villains", NX) => "OK"
        @fact set(conn, "hawks", "bogeyed", NX) => nothing
        @fact set(conn, "fazes", "nymph") => "OK"
        @fact mset(conn, "flyweight", "Hester") => "OK"
        @fact mset(conn, [("dizzies", "hipster"), ("Ramiro", "circuitry"), ("assessing", "divined")]) => "OK"
        @fact msetnx(conn, [("dizzies", "speller"), ("unceremoniously", "reconstructs")]) => 0
        @fact msetnx(conn, [("hydroelectric", "nonspirituals"), ("premiered", "minuet")]) => 0
        @fact_throws psetex(conn, "publicizing", 0, "Wiggins")
        @fact_throws psetex(conn, "publicizing", -37, "Wiggins")
        @fact psetex(conn, "publicizing", 514, "Wiggins") => "OK"
        @fact_throws setex(conn, "summerhouse", 0, "handkerchief")
        @fact_throws setex(conn, "summerhouse", -108, "handkerchief")
        @fact setex(conn, "summerhouse", 244, "handkerchief") => "OK"
        @fact setnx(conn, "summerhouse", "pinker") => 0
        @fact setnx(conn, "temperature", "45") => "OK"
        @fact setrange(conn, "renegading", 34, "hijacker") => "OK"
        @fact setrange(conn, "hawks", 3, "hijacker") => "OK"
        @fact append(conn, "summerhouse", "ton") => "OK"
        @fact_throws decr(conn, "summerhouse")
        @fact_throws decrby(conn, "summerhouse", 15)
        @fact_throws incr(conn, "summerhouse")
        @fact_throws incrby(conn, "summerhouse", 84)
        @fact_throws incrbyfloat(conn, "summerhouse", 0.6)
        @fact_throws incrbyfloat(conn, "summerhouse", -2.0)
        @fact decr(conn, "temperature") => "OK"
        @fact decrby(conn, "temperature", 15) => "OK"
        @fact incr(conn, "temperature") => "OK"
        @fact incrby(conn, "temperature", 84) => "OK"
        @fact incrbyfloat(conn, "temperature", 0.6) => "OK"
        @fact incrbyfloat(conn, "temperature", -2.0) => "OK"
        @fact setbit(conn, "hawks", 12, true) => "OK"
        # \\  Hashes  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
        @fact hset(conn, "empowering", "bonks", "129") => "OK"
        @fact hmset(conn, "backlog", "boss", "bigotry") => "OK"
        @fact hmset(conn, "dds", [("hyperactivity", "goutier")
                                  ("reclining", "omissions")
                                  ("syllabus", "surface")]) => "OK"
        @fact hsetnx(conn, "backlog", "boss", "sensationalized") => 0
        @fact hsetnx(conn, "shinnying", "begotten", "entente") => "OK"
        @fact hsetnx(conn, "shinnying", "copula", "shell") => "OK"
        @fact hincrby(conn, "empowering", "bonks", 5) => "OK"
        @fact hincrbyfloat(conn, "empowering", "bonks", 722.91) => "OK"
        # \\  Lists  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
        @fact lpush(conn, key, value) => "OK"
        @fact lpush{T<:String}(conn, key, values::Array{T}) => "OK"
        @fact lpushx(conn, key, value) => "OK"
        @fact lpushx{T<:String}(conn, key, values::Array{T}) => "OK"
        @fact lset(conn, key, index::Integer, value) => "OK"
        @fact rpush(conn, key, value) => "OK"
        @fact rpush{T<:String}(conn, key, values::Array{T}) => "OK"
        @fact rpushx(conn, key, value) => "OK"
        @fact linsert(conn, key, rel::Bool, pivot, value) => "OK"
        # \\  Sets  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
        @fact sadd(conn, key, member) => "OK"
        @fact sadd{T<:String}(conn, key, members::Array{T}) => "OK"
        # \\  Sorted Sets  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
        @fact zadd(conn, key, score::Integer, member) => "OK"
        @fact zadd(conn, key, ssmm::Array{(Integer, String)}) => "OK"
        @fact zincrby(conn, key, incr::Integer, member) => "OK"
    end
    @fact_throws shutdown(conn)
    close(conn)
    blacklisted_ports = vcat(blacklisted_ports, port)
end

FactCheck.exitstatus()
