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
        @fact - append(conn::RSocket, key::String, value::String) =>
        @fact - decr(conn::RSocket, key::String) =>
        @fact - decrby(conn::RSocket, key::String, n::Integer) =>
        @fact - incr(conn::RSocket, key::String) =>
        @fact - incrby(conn::RSocket, key::String, n::Integer) =>
        @fact - incrbyfloat(conn::RSocket, key::String, x::FloatingPoint) =>
        @fact - mset(conn::RSocket, key::String, val::String) =>
        @fact - mset{T<:String}(conn::RSocket, kkvv::Array{(T, T)}) =>
        @fact - mset(conn::RSocket, key::String, val::String) =>
        @fact - msetnx{T<:String}(conn::RSocket, kkvv::Array{(T, T)}) =>
        @fact - psetex(conn::RSocket, key::String, ms::Integer, value::String) =>
        O set(conn::RSocket, key::String, value::String)
        @fact - set(conn::RSocket, key::String, value::String, expires::Integer, =>
    unit::Bool, condition::Bool)
        @fact - set(conn::RSocket, key::String, value::String, expires::Integer, unit::Bool) =>
        @fact - set(conn::RSocket, key::String, value::String, condition::Bool) =>
        @fact - setbit(conn::RSocket, key::String, offset::Integer, value::Bool) =>
        @fact - setex(conn::RSocket, key::String, sec::Integer, value::String) =>
        @fact - setnx(conn::RSocket, key::String, value::String) =>
        @fact - setrange(conn::RSocket, key::String, offset::Integer, value::String) =>

        # \\  Hashes  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
        @fact - hincrby(conn::RSocket, key::String, field::String, incr::Integer) =>
        @fact - hincrbyfloat(conn::RSocket, key::String, field::String, incr::FloatingPoint) =>
        @fact - hmset(conn::RSocket, key::String, field::String, val::String) =>
        @fact - hmset{T<:String}(conn::RSocket, key::String, ffvv::Array{(T, T)}) =>
        @fact - hset(conn::RSocket, key::String, field::String, value::String) =>
        @fact - hsetnx(conn::RSocket, key::String, field::String, value::String) =>

        # \\  Lists  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
        @fact - linsert(conn::RSocket, key::String, rel::Bool, pivot::String, value::String) =>
        @fact - lpush(conn::RSocket, key::String, value::String) =>
        @fact - lpush{T<:String}(conn::RSocket, key::String, values::Array{T}) =>
        @fact - lpushx(conn::RSocket, key::String, value::String) =>
        @fact - lpushx{T<:String}(conn::RSocket, key::String, values::Array{T}) =>
        @fact - lset(conn::RSocket, key::String, index::Integer, value::String) =>
        @fact - rpush(conn::RSocket, key::String, value::String) =>
        @fact - rpush{T<:String}(conn::RSocket, key::String, values::Array{T}) =>
        @fact - rpushx(conn::RSocket, key::String, value::String) =>

        # \\  Sets  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
        @fact - sadd(conn::RSocket, key::String, member::String) =>
        @fact - sadd{T<:String}(conn::RSocket, key::String, members::Array{T}) =>

        # \\  Sorted Sets  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
        @fact - zadd(conn::RSocket, key::String, score::Integer, member::String) =>
        @fact - zadd(conn::RSocket, key::String, ssmm::Array{(Integer, String)}) =>
        @fact - zincrby(conn::RSocket, key::String, incr::Integer, member::String) =>
    end
    @fact_throws shutdown(conn)
    close(conn)
    blacklisted_ports = vcat(blacklisted_ports, port)
end

FactCheck.exitstatus()
