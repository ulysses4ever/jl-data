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
        @fact_throws set(conn, "stipulations", "cattiest", 10, EX, XX)
        @fact set(conn, "hefty", "engages", 10, EX, NX) => "OK"
        @fact set(conn, "hefty", "vanquish", 10, EX, NX) => "OK"
        @fact set(conn, "hefty", "glorying", 10, EX, XX) => "OK"
        @fact set(conn, "ducklings", "transmuting", 17, PX) => "OK"
        @fact set(conn, key, value, condition::Bool) => "OK"
        @fact set(conn, key, value) => "OK"
        @fact mset(conn, key, val) => "OK"
        @fact mset{T<:String}(conn, kkvv::Array{(T, T)}) => "OK"
        @fact mset(conn, key, val) => "OK"
        @fact msetnx{T<:String}(conn, kkvv::Array{(T, T)}) => "OK"
        @fact psetex(conn, key, ms::Integer, value) => "OK"
        @fact setex(conn, key, sec::Integer, value) => "OK"
        @fact setnx(conn, key, value) => "OK"
        @fact setrange(conn, key, offset::Integer, value) => "OK"
        @fact append(conn, key, value) => "OK"
        @fact decr(conn, key) => "OK"
        @fact decrby(conn, key, n::Integer) => "OK"
        @fact incr(conn, key) => "OK"
        @fact incrby(conn, key, n::Integer) => "OK"
        @fact incrbyfloat(conn, key, x::FloatingPoint) => "OK"
        @fact setbit(conn, key, offset::Integer, value::Bool) => "OK"

        # \\  Hashes  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
        @fact hset(conn, key, field, value) => "OK"
        @fact hmset(conn, key, field, val) => "OK"
        @fact hmset{T<:String}(conn, key, ffvv::Array{(T, T)}) => "OK"
        @fact hsetnx(conn, key, field, value) => "OK"
        @fact hincrby(conn, key, field, incr::Integer) => "OK"
        @fact hincrbyfloat(conn, key, field, incr::FloatingPoint) => "OK"

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
