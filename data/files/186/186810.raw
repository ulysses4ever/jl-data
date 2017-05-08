#!/usr/bin/env julia

module Redis
export connect, command
import Base.connect

const CRLF = "\r\n"
CmdArgs = Union(Array{String}, Array{None})

function connect()
    Base.connect(6379)
end

function prepare_line(prev::String, line::String)
    len = length(line)
    string(prev, "\$", len, CRLF, line, CRLF)
end

# function prepare_command{T<:String}(words::Array{T})
function prepare_command{T<:String}(words::Array{T})
    n = length(words)
    body = foldl(prepare_line, "", words) 
    string("*", n, CRLF,  body)
end

function command(conn::Base.AsyncStream, cmd::String, args::CmdArgs)
    cmdstring = prepare_command(vcat([cmd], args))
    write(conn, cmdstring)
    resp = ""
    read(conn, String)
end

function command(conn::Base.AsyncStream, cmd::String)
    command(conn, cmd, [])
end


end
