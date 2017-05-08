#!/usr/bin/env julia
# **********************************************************************
#   redis.jl -- A redis client library for the Julia language.
#
#   Copyright © 2014 by Matt Gushee
#   This is open source software, released under the terms of the BSD
#   license. See the accompanying LICENSE file for details.
# **********************************************************************

module Redis
using Match
import Base.connect
import Base.string

export and, or, xor, not, LOCALHOST, EX, PX, XX, NX, BEFORE, AFTER,
connect, append, auth, bgrewriteaof, bgsave, bitcount, bitop, bitpos,
blpop, brpop, brpoplpush, client_getname, client_list, client_pause,
client_setname, cluster_slots, command, command_count, command_info,
config_get, config_resetstat, config_rewrite, config_set, dbsize,
debug_object, debug_segfault, decr, decrby, del, discard, dump, echo,
exec, exists, expire, expireat, flushall, flushdb, get, getbit, getrange,
getset, hdel, hexists, hget, hgetall, hincrby, hincrbyfloat, hkeys, hlen,
hmget, hmset, hscan, hset, hsetnx, hvals, incr, incrby, incrbyfloat, info,
keys, lastsave, lindex, linsert, llen, lpop, lpush, lpushx, lrange, lrem,
lset, ltrim, mget, monitor, move, mset, msetnx, multi, persist, pexpire,
pexpireat, pfadd, pfcount, pfmerge, ping, psetex, psubscribe, pttl,
publish, pubsub_channels, pubsub_numpat, pubsub_numsub, punsubscribe,
quit, randomkey, rename, renamenx, restore, role, rpop, rpoplpush, rpush,
rpushx, sadd, save, scard, sdiff, sdiffstore, select, set, setbit, setex,
setnx, setrange, shutdown, sinter, sinterstore, sismember, slaveof,
smembers, smove, spop, srandmember, srem, sscan, strlen, subscribe,
sunion, sunionstore, sync, time, ttl, unsubscribe, unwatch, value_type,
watch, zadd, zcard, zcount, zincrby, zrange, zrank, zrem, zremrangebyrank,
zremrangebyscore, zrevrange, zrevrank, zscan, zscore 

########################################################################
##  TYPES & CONSTANTS  #################################################
# \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

RSocket = Union(Base.TcpSocket, Base.Pipe)

type And
end
type Or
end
type XOr
end
type Not
end
BitOp = Union(And, Or, XOr, Not)
and = And()
or = Or()
xor = XOr()
not = Not()
string(::And) = "AND"
string(::Or) = "OR"
string(::XOr) = "XOR"
string(::Not) = "NOT"

const CRLF = "\r\n"
# For some reason this causes trouble for multiple connection attempts
const LOCALHOST = ip"127.0.0.1"
const EX = true
const PX = false
const XX = true
const NX = false
const BEFORE = true
const AFTER = false

# \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
########################################################################
##  UTILITY FUNCTIONS  #################################################
# \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

function connect()
    Base.connect(LOCALHOST, 6379)
end

function prepare_bulk_string(prev::String, word::Any)
    line = string(word)
    len = length(line)
    string(prev, "\$", len, CRLF, line, CRLF)
end

function prepare_command(words::Array)
    n = length(words)
    body = foldl(prepare_bulk_string, "", words) 
    string("*", n, CRLF, body)
end

function parse_error(chr::Char)
    throw(string("Invalid prefix character: '", chr, "'"))
end

function read_array(conn::RSocket)
    nargs = read_int(conn)
    map(_ -> read_dispatch(conn), [1:nargs])
end

function read_error(conn::RSocket)
    message = read_simple_string(conn)
    throw(message)
end

function read_simple_string(conn::RSocket)
    strip(readline(conn))
end

function read_int(conn::RSocket)
    int(strip(readline(conn)))
end

function read_bulk_string(conn::RSocket)
    len = read_int(conn)
    body = readbytes(conn, len)
    tail = readbytes(conn, 2)
    assert(ascii(tail) == CRLF)
    try
        utf8(body)
    catch
        body
    end
end

function read_dispatch(conn)
    # @match read(conn, Char) begin
    c = read(conn, Char)
    @match c begin
        '*' => read_array(conn)
        '-' => read_error(conn)
        '+' => read_simple_string(conn)
        ':' => read_int(conn)
        '$' => read_bulk_string(conn)
        chr => parse_error(chr)
    end
end

function redis_command(conn::RSocket, cmd::String, args::Array)
    cmdstring = prepare_command(vcat([cmd], args))
    write(conn, cmdstring)
    read_dispatch(conn)
end

function redis_command(conn::RSocket, cmd::String)
    redis_command(conn, cmd, [])
end

# \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
########################################################################
##  REDIS COMMANDS  ####################################################
# \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
# \\  Connection  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

# AUTH password Authenticate to the server
function auth(conn::RSocket, password::String)
    redis_command(conn, "AUTH", [password])
end

# ECHO message Echo the given string
function echo(conn::RSocket, message::String)
    redis_command(conn, "ECHO", [message])
end

# PING Ping the server
function ping(conn::RSocket)
    redis_command(conn, "PING")
end

# QUIT Close the connection
function quit(conn::RSocket)
    redis_command(conn, "QUIT")
    close(conn)
end

# SELECT index Change the selected database for the current connection 
function select(conn::RSocket, dbid::Integer)
    redis_command(conn, "SELECT", [dbid])
end


# \\  Server  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

# BGREWRITEAOF Asynchronously rewrite the append-only file
function bgrewriteaof(conn::RSocket)
    redis_command(conn, "BGREWRITEAOF")
end

# BGSAVE Asynchronously save the dataset to disk
function bgsave(conn::RSocket)
    redis_command(conn, "BGSAVE")
end

# CLIENT KILL [ip:port] [ID client-id] [TYPE normal|slave|pubsub] [ADDR ip:port] [SKIPME yes/no] Kill the connection of a client
#function client_kill(conn::RSocket)
#    redis_command(conn, "CLIENT", ["KILL"])
#end

# CLIENT LIST Get the list of client connections
function client_list(conn::RSocket)
    redis_command(conn, "CLIENT", ["LIST"])
end

# CLIENT GETNAME Get the current connection name
function client_getname(conn::RSocket)
    redis_command(conn, "CLIENT", ["GETNAME"])
end

# CLIENT PAUSE timeout Stop processing commands from clients for some time
function client_pause(conn::RSocket, timeout::Integer)
    redis_command(conn, "CLIENT", ["PAUSE", timeout])
end

# CLIENT SETNAME connection-name Set the current connection name
function client_setname(conn::RSocket, name::String)
    redis_command(conn, "CLIENT", ["SETNAME", name])
end

# CLUSTER SLOTS Get array of Cluster slot to node mappings
function cluster_slots(conn::RSocket)
    redis_command(conn, "CLUSTER", ["SLOTS"])
end

# COMMAND Get array of Redis command details
function command(conn::RSocket)
    redis_command(conn, "COMMAND")
end

# COMMAND COUNT Get total number of Redis commands
function command_count(conn::RSocket)
    redis_command(conn, "COMMAND", ["COUNT"])
end

# COMMAND GETKEYS Extract keys given a full Redis command
#function command_getkeys(conn::RSocket)
    #redis_command(conn, "COMMAND", ["GETKEYS"])
#end

# COMMAND INFO command-name [command-name ...] Get array of specific Redis command details
# PROBLEM: Is there a way to make this type-safe?
function command_info(conn::RSocket, names...)
    redis_command(conn, "COMMAND", ["INFO"], [names...])
end

# CONFIG GET parameter Get the value of a configuration parameter
function config_get(conn::RSocket, param::String="*")
    redis_command(conn, "CONFIG", ["GET", param])
end

# CONFIG REWRITE Rewrite the configuration file with the in memory configuration
function config_rewrite(conn::RSocket)
    redis_command(conn, "CONFIG", ["REWRITE"])
end

# CONFIG SET parameter value Set a configuration parameter to the given value
function config_set(conn::RSocket, param::String, value::String)
    redis_command(conn, "CONFIG", ["SET", param, value])
end

# CONFIG RESETSTAT Reset the stats returned by INFO
function config_resetstat(conn::RSocket)
    redis_command(conn, "CONFIG", ["RESETSTAT"])
end

# DBSIZE Return the number of keys in the selected database
function dbsize(conn::RSocket)
    redis_command(conn, "DBSIZE")
end

# DEBUG OBJECT key Get debugging information about a key
function debug_object(conn::RSocket, key::String)
    redis_command(conn, "DEBUG", ["OBJECT", key])
end

# DEBUG SEGFAULT Make the server crash
function debug_segfault(conn::RSocket)
    redis_command(conn, "DEBUG", ["SEGFAULT"])
end

# FLUSHALL Remove all keys from all databases
function flushall(conn::RSocket)
    redis_command(conn, "FLUSHALL")
end

# FLUSHDB Remove all keys from the current database
function flushdb(conn::RSocket)
    redis_command(conn, "FLUSHDB")
end

# INFO [section] Get information and statistics about the server
function info(conn::RSocket, section::String)
    redis_command(conn, "INFO", [section])
end

# LASTSAVE Get the UNIX time stamp of the last successful save to disk
function lastsave(conn::RSocket)
    redis_command(conn, "LASTSAVE")
end

# MONITOR Listen for all requests received by the server in real time
function monitor(conn::RSocket)
    redis_command(conn, "MONITOR")
end

# ROLE Return the role of the instance in the context of replication
function role(conn::RSocket)
    redis_command(conn, "ROLE")
end

# SAVE Synchronously save the dataset to disk
function save(conn::RSocket)
    redis_command(conn, "SAVE")
end

# SHUTDOWN [NOSAVE] [SAVE] Synchronously save the dataset to disk and then shut down the server
function shutdown(conn::RSocket, save::Bool)
    redis_command(conn, "SHUTDOWN", [save ? "SAVE" : "NOSAVE"])
end
function shutdown(conn::RSocket)
    redis_command(conn, "SHUTDOWN")
end

# SLAVEOF host port Make the server a slave of another instance, or promote it as master
function slaveof(conn::RSocket, host::String, port::Integer)
    redis_command(conn, "SLAVEOF", [host, port])
end
function slaveof(conn::RSocket, noone::Nothing)
    redis_command(conn, "SLAVEOF", ["NO ONE"])
end

# SLOWLOG subcommand [argument] Manages the Redis slow queries log
# function slowlog(conn::RSocket)
#     redis_command(conn, "SLOWLOG")
# end

# SYNC Internal command used for replication
function sync(conn::RSocket)
    redis_command(conn, "SYNC")
end

# TIME Return the current server time 
function time(conn::RSocket)
    redis_command(conn, "TIME")
end


# \\  Keys  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

# DEL key [key ...] Delete a key
# PROBLEM: typesafe?
function del(conn::RSocket, key...)
    redis_command(conn, "DEL", [key...])
end

# DUMP key Return a serialized version of the value stored at the specified key.
function dump(conn::RSocket, key::String)
    redis_command(conn, "DUMP", [key])
end

# EXISTS key Determine if a key exists
function exists(conn::RSocket, key::String)
    redis_command(conn, "EXISTS", [key])
end

# EXPIRE key seconds Set a key's time to live in seconds
function expire(conn::RSocket, key::String, ttl::Integer)
    redis_command(conn, "EXPIRE", [key, ttl])
end

# EXPIREAT key timestamp Set the expiration for a key as a UNIX timestamp
function expireat(conn::RSocket, key::String, time::Integer)
    redis_command(conn, "EXPIREAT", [key, time])
end

# KEYS pattern Find all keys matching the given pattern
function keys(conn::RSocket, pattern::String="*")
    redis_command(conn, "KEYS", [pattern])
end

# MIGRATE host port key destination-db timeout [COPY] [REPLACE] Atomically transfer a key from a Redis instance to another one.
#function migrate(conn::RSocket)
    #redis_command(conn, "MIGRATE")
#end

# MOVE key db Move a key to another database
function move(conn::RSocket, key::String, db::Integer)
    redis_command(conn, "MOVE", [key, db])
end

# OBJECT subcommand [arguments [arguments ...]] Inspect the internals of Redis objects
#function object(conn::RSocket)
    #redis_command(conn, "OBJECT")
#end

# PERSIST key Remove the expiration from a key
function persist(conn::RSocket, key::String)
    redis_command(conn, "PERSIST", [key])
end

# PEXPIRE key milliseconds Set a key's time to live in milliseconds
function pexpire(conn::RSocket, key::String, ttl::Integer)
    redis_command(conn, "PEXPIRE", [key, ttl])
end

# PEXPIREAT key milliseconds-timestamp Set the expiration for a key as a UNIX timestamp specified in milliseconds
function pexpireat(conn::RSocket, key::String, time::Integer)
    redis_command(conn, "PEXPIREAT", [key, time])
end

# PTTL key Get the time to live for a key in milliseconds
function pttl(conn::RSocket, key::String)
    redis_command(conn, "PTTL", [key])
end

# RANDOMKEY Return a random key from the keyspace
function randomkey(conn::RSocket)
    redis_command(conn, "RANDOMKEY")
end

# RENAME key newkey Rename a key
function rename(conn::RSocket, key::String, newname::String)
    redis_command(conn, "RENAME", [key, newname])
end

# RENAMENX key newkey Rename a key, only if the new key does not exist
function renamenx(conn::RSocket, key::String, newname::String)
    redis_command(conn, "RENAMENX", [key, newname])
end

# RESTORE key ttl serialized-value Create a key using the provided serialized value, previously obtained using DUMP.
function restore(conn::RSocket, key::String, value::String)
    redis_command(conn, "RESTORE", [key, "0", value])
end
function restore(conn::RSocket, key::String, ttl::Integer, value::String)
    redis_command(conn, "RESTORE", [key, ttl, value])
end

# SORT key [BY pattern] [LIMIT offset count] [GET pattern [GET pattern ...]] [ASC|DESC] [ALPHA] [STORE destination] Sort the elements in a list, set or sorted set
#function sort(conn::RSocket)
    #redis_command(conn, "SORT")
#end

# TTL key Get the time to live for a key
function ttl(conn::RSocket, key::String)
    redis_command(conn, "TTL", [key])
end

# TYPE key Determine the type stored at key
# NAME_CONFLICT: type => value_type
function value_type(conn::RSocket, key::String)
    redis_command(conn, "TYPE", [key])
end

# SCAN cursor [MATCH pattern] [COUNT count] Incrementally iterate the keys space 
#function scan(conn::RSocket)
    #redis_command(conn, "SCAN")
#end


# \\  Strings  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

# APPEND key value Append a value to a key
function append(conn::RSocket, key::String, value::String)
    redis_command(conn, "APPEND", [key, value])
end

# BITCOUNT key [start end] Count set bits in a string
function bitcount(conn::RSocket, key::String, start::Integer, end_::Integer)
    redis_command(conn, "BITCOUNT", [key, start, end_])
end
function bitcount(conn::RSocket, key::String)
    redis_command(conn, "BITCOUNT", [key])
end

# BITOP operation destkey key [key ...] Perform bitwise operations between strings
function bitop(conn::RSocket, op::BitOp, destkey::String, srckey::String, srckeys...)
    redis_command(conn, "BITOP", op, [destkey, srckey, srckeys...])
end

# BITPOS key bit [start] [end] Find first bit set or clear in a string
function bitpos(conn::RSocket, key::String, value::Bool, start::Integer, end_::Integer)
    redis_command(conn, "BITPOS", [key, value, start, end_])
end
function bitpos(conn::RSocket, key::String, value::Bool, start::Integer)
    redis_command(conn, "BITPOS", [key, value, start])
end
function bitpos(conn::RSocket, key::String, value::Bool)
    redis_command(conn, "BITPOS", [key, value])
end

# DECR key Decrement the integer value of a key by one
function decr(conn::RSocket, key::String)
    redis_command(conn, "DECR", [key])
end

# DECRBY key decrement Decrement the integer value of a key by the given number
function decrby(conn::RSocket, key::String, n::Integer)
    redis_command(conn, "DECRBY", [key, n])
end

# GET key Get the value of a key
function get(conn::RSocket, key::String)
    redis_command(conn, "GET", [key])
end

# GETBIT key offset Returns the bit value at offset in the string value stored at key
function getbit(conn::RSocket, key::String, offset::Integer)
    redis_command(conn, "GETBIT", [key, offset])
end

# GETRANGE key start end Get a substring of the string stored at a key
function getrange(conn::RSocket, key::String, start::Integer, end_::Integer)
    redis_command(conn, "GETRANGE", [key, start, end_])
end

# GETSET key value Set the string value of a key and return its old value
function getset(conn::RSocket, key::String, value::String)
    redis_command(conn, "GETSET", [key, value])
end

# INCR key Increment the integer value of a key by one
function incr(conn::RSocket, key::String)
    redis_command(conn, "INCR", [key])
end

# INCRBY key increment Increment the integer value of a key by the given amount
function incrby(conn::RSocket, key::String, n::Integer)
    redis_command(conn, "INCRBY", [key, n])
end

# INCRBYFLOAT key increment Increment the float value of a key by the given amount
function incrbyfloat(conn::RSocket, key::String, x::FloatingPoint)
    redis_command(conn, "INCRBYFLOAT", [key, x])
end

# MGET key [key ...] Get the values of all the given keys
function mget(conn::RSocket, key::String, keys...)
    redis_command(conn, "MGET", [key, keys...])
end

# MSET key value [key value ...] Set multiple keys to multiple values
function mset(conn::RSocket, key::String, val::String)
    redis_command(conn, "MSET", [key, val])
end
function mset{T<:String}(conn::RSocket, kkvv::Array{(T, T)})
    args = foldl((prev, pair) -> vcat(prev, pair[1], pair[2]), [], kkvv) 
    redis_command(conn, "MSET", args)
end

# MSETNX key value [key value ...] Set multiple keys to multiple values, only if none of the keys exist
function mset(conn::RSocket, key::String, val::String)
    redis_command(conn, "MSETNX", [key, val])
end
function msetnx{T<:String}(conn::RSocket, kkvv::Array{(T, T)})
    args = foldl((prev, pair) -> vcat(prev, pair[1], pair[2]), [], kkvv) 
    redis_command(conn, "MSETNX", args)
end

# PSETEX key milliseconds value Set the value and expiration in milliseconds of a key
function psetex(conn::RSocket, key::String, ms::Integer, value::String)
    redis_command(conn, "PSETEX", [key, ms, value])
end

# SET key value [EX seconds] [PX milliseconds] [NX|XX] Set the string value of a key
function set(conn::RSocket, key::String, value::String)
    redis_command(conn, "SET", [key, value])
end
function set(conn::RSocket, key::String, value::String,
             expires::Integer, unit::Bool, condition::Bool)
    ex_px = "$(unit ? "EX" : "PX")"
    nx_xx = "$(condition ? "XX" : "NX")"
    redis_command(conn, "SET", [key, value, ex_px, expires, nx_xx])
end
function set(conn::RSocket, key::String, value::String, expires::Integer, unit::Bool)
    ex_px = "$(unit ? "EX" : "PX")"
    redis_command(conn, "SET", [key, value, ex_px, expires])
end
function set(conn::RSocket, key::String, value::String, condition::Bool)
    nx_xx = "$(condition ? "XX" : "NX")"
    redis_command(conn, "SET", [key, value, nx_xx])
end

# SETBIT key offset value Sets or clears the bit at offset in the string value stored at key
function setbit(conn::RSocket, key::String, offset::Integer, value::Bool)
    redis_command(conn, "SETBIT", [key, offset, int(value)])
end

# SETEX key seconds value Set the value and expiration of a key
function setex(conn::RSocket, key::String, sec::Integer, value::String)
    redis_command(conn, "SETEX", [key, sec, value])
end

# SETNX key value Set the value of a key, only if the key does not exist
function setnx(conn::RSocket, key::String, value::String)
    redis_command(conn, "SETNX", [key, value])
end

# SETRANGE key offset value Overwrite part of a string at key starting at the specified offset
function setrange(conn::RSocket, key::String, offset::Integer, value::String)
    redis_command(conn, "SETRANGE", [key, offset, value])
end

# STRLEN key Get the length of the value stored in a key 
function strlen(conn::RSocket, key::String)
    redis_command(conn, "STRLEN", [key])
end

# \\  Hashes  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

# HDEL key field [field ...] Delete one or more hash fields
function hdel(conn::RSocket, key::String, field::String, fields...)
    redis_command(conn, "HDEL", [key, field, fields...])
end

# HEXISTS key field Determine if a hash field exists
function hexists(conn::RSocket, key::String, field::String)
    redis_command(conn, "HEXISTS", [key, field])
end

# HGET key field Get the value of a hash field
function hget(conn::RSocket, key::String, field::String)
    redis_command(conn, "HGET", [key, field])
end

# HGETALL key Get all the fields and values in a hash
function hgetall(conn::RSocket, key::String)
    redis_command(conn, "HGETALL", [key])
end

# HINCRBY key field increment Increment the integer value of a hash field by the given number
function hincrby(conn::RSocket, key::String, field::String, incr::Integer)
    redis_command(conn, "HINCRBY", [key, field, incr])
end

# HINCRBYFLOAT key field increment Increment the float value of a hash field by the given amount
function hincrbyfloat(conn::RSocket, key::String, field::String, incr::FloatingPoint)
    redis_command(conn, "HINCRBYFLOAT", [key, field, incr])
end

# HKEYS key Get all the fields in a hash
function hkeys(conn::RSocket, key::String)
    redis_command(conn, "HKEYS", [key])
end

# HLEN key Get the number of fields in a hash
function hlen(conn::RSocket, key::String)
    redis_command(conn, "HLEN", [key])
end

# HMGET key field [field ...] Get the values of all the given hash fields
function hmget(conn::RSocket, key::String, field::String, fields...)
    redis_command(conn, "HMGET", [key, field, fields...])
end

# HMSET key field value [field value ...] Set multiple hash fields to multiple values
function hmset(conn::RSocket, key::String, field::String, val::String)
    redis_command(conn, "HMSET", [key, field, val])
end
function hmset{T<:String}(conn::RSocket, key::String, ffvv::Array{(T, T)})
    args = foldl((prev, pair) -> vcat(prev, pair[1], pair[2]), [key], ffvv) 
    redis_command(conn, "HMSET", args)
end

# HSET key field value Set the string value of a hash field
function hset(conn::RSocket, key::String, field::String, value::String)
    redis_command(conn, "HSET", [key, field, value])
end

# HSETNX key field value Set the value of a hash field, only if the field does not exist
function hsetnx(conn::RSocket, key::String, field::String, value::String)
    redis_command(conn, "HSETNX", [key, field, value])
end

# HVALS key Get all the values in a hash
function hvals(conn::RSocket, key::String)
    redis_command(conn, "HVALS", [key])
end

# HSCAN key cursor [MATCH pattern] [COUNT count] Incrementally iterate hash fields and associated values 
function hscan(conn::RSocket, key::String, cursor::Integer)
    redis_command(conn, "HSCAN", [key, cursor])
end
function hscan(conn::RSocket, key::String, cursor::Integer, match::String, count::Integer)
    redis_command(conn, "HSCAN", [key, cursor, "MATCH", match, "COUNT", count])
end
function hscan(conn::RSocket, key::String, cursor::Integer, match::String)
    redis_command(conn, "HSCAN", [key, cursor, "MATCH", match])
end
function hscan(conn::RSocket, key::String, cursor::Integer, count::Integer)
    redis_command(conn, "HSCAN", [key, cursor, "COUNT", count])
end


# \\  Lists  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

# BLPOP key [key ...] timeout Remove and get the first element in a list, or block until one is available
function blpop(conn::RSocket, key::String)
    redis_command(conn, "BLPOP", [key])
end
function blpop{T<:String}(conn::RSocket, keys::Array{T})
    redis_command(conn, "BLPOP", keys)
end

# BRPOP key [key ...] timeout Remove and get the last element in a list, or block until one is available
function brpop(conn::RSocket, key::String, timeout::Integer)
    redis_command(conn, "BRPOP", [key])
end
function brpop{T<:String}(conn::RSocket, keys::Array{T}, timeout::Integer)
    redis_command(conn, "BRPOP", vcat(keys, timeout))
end

# BRPOPLPUSH source destination timeout Pop a value from a list, push it to another list and return it; or block until one is available
function brpoplpush(conn::RSocket, src::String, dest::String, timeout::Integer)
    redis_command(conn, "BRPOPLPUSH", [src, dest, timeout])
end

# LINDEX key index Get an element from a list by its index
function lindex(conn::RSocket, key::String, index::Integer)
    redis_command(conn, "LINDEX", [key, index])
end

# LINSERT key BEFORE|AFTER pivot value Insert an element before or after another element in a list
function linsert(conn::RSocket, key::String, rel::Bool, pivot::String, value::String)
    relstr = "$(pivot ? "BEFORE" : "AFTER")"
    redis_command(conn, "LINSERT", [key, relstr, pivot, value])
end

# LLEN key Get the length of a list
function llen(conn::RSocket, key::String)
    redis_command(conn, "LLEN", [key])
end

# LPOP key Remove and get the first element in a list
function lpop(conn::RSocket, key::String)
    redis_command(conn, "LPOP", [key])
end

# LPUSH key value [value ...] Prepend one or multiple values to a list
function lpush(conn::RSocket, key::String, value::String)
    redis_command(conn, "LPUSH", [key, value])
end
function lpush{T<:String}(conn::RSocket, key::String, values::Array{T})
    redis_command(conn, "LPUSH", vcat(key, values))
end

# LPUSHX key value Prepend a value to a list, only if the list exists
function lpushx(conn::RSocket, key::String, value::String)
    redis_command(conn, "LPUSHX", [key, value])
end
function lpushx{T<:String}(conn::RSocket, key::String, values::Array{T})
    redis_command(conn, "LPUSHX", vcat(key, values))
end

# LRANGE key start stop Get a range of elements from a list
function lrange(conn::RSocket, key::String, start::Integer, end_::Integer)
    redis_command(conn, "LRANGE", [key, start, end_])
end

# LREM key count value Remove elements from a list
function lrem(conn::RSocket, key::String, count::Integer, value::String)
    redis_command(conn, "LREM", [key, count, value])
end

# LSET key index value Set the value of an element in a list by its index
function lset(conn::RSocket, key::String, index::Integer, value::String)
    redis_command(conn, "LSET", [key, index, value])
end

# LTRIM key start stop Trim a list to the specified range
function ltrim(conn::RSocket, key::String, start::Integer, end_::Integer)
    redis_command(conn, "LTRIM", [key, start, end_])
end

# RPOP key Remove and get the last element in a list
function rpop(conn::RSocket, key::String)
    redis_command(conn, "RPOP", [key])
end

# RPOPLPUSH source destination Remove the last element in a list, append it to another list and return it
function rpoplpush(conn::RSocket, src::String, dest::String)
    redis_command(conn, "RPOPLPUSH", [src, dest])
end

# RPUSH key value [value ...] Append one or multiple values to a list
function rpush(conn::RSocket, key::String, value::String)
    redis_command(conn, "RPUSH", [key, value])
end
function rpush{T<:String}(conn::RSocket, key::String, values::Array{T})
    redis_command(conn, "RPUSH", vcat(key, values))
end

# RPUSHX key value Append a value to a list, only if the list exists 
function rpushx(conn::RSocket, key::String, value::String)
    redis_command(conn, "RPUSHX", [key, value])
end


# \\  Sets  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

# SADD key member [member ...] Add one or more members to a set
function sadd(conn::RSocket, key::String, member::String)
    redis_command(conn, "SADD", [key, member])
end
function sadd{T<:String}(conn::RSocket, key::String, members::Array{T})
    redis_command(conn, "SADD", vcat(key, members))
end

# SCARD key Get the number of members in a set
function scard(conn::RSocket, key::String)
    redis_command(conn, "SCARD", [key])
end

# SDIFF key [key ...] Subtract multiple sets
function sdiff(conn::RSocket, key::String)
    redis_command(conn, "SDIFF", [key])
end
function sdiff{T<:String}(conn::RSocket, keys::Array{T})
    redis_command(conn, "SDIFF", keys)
end

# SDIFFSTORE destination key [key ...] Subtract multiple sets and store the resulting set in a key
function sdiffstore(conn::RSocket, dest::String, key::String)
    redis_command(conn, "SDIFFSTORE", [dest, key])
end
function sdiffstore{T<:String}(conn::RSocket, dest::String, keys::Array{T})
    redis_command(conn, "SDIFFSTORE", vcat(dest, keys))
end

# SINTER key [key ...] Intersect multiple sets
function sinter(conn::RSocket, key::String)
    redis_command(conn, "SINTER", [key])
end
function sinter{T<:String}(conn::RSocket, keys::Array{T})
    redis_command(conn, "SINTER", keys)
end

# SINTERSTORE destination key [key ...] Intersect multiple sets and store the resulting set in a key
function sinterstore(conn::RSocket, dest::String, key::String)
    redis_command(conn, "SINTERSTORE", [dest, key])
end
function sinterstore{T<:String}(conn::RSocket, dest::String, keys::Array{T})
    redis_command(conn, "SINTERSTORE", vcat(dest, keys))
end

# SISMEMBER key member Determine if a given value is a member of a set
function sismember(conn::RSocket, key::String, member::String)
    redis_command(conn, "SISMEMBER", [key, member])
end

# SMEMBERS key Get all the members in a set
function smembers(conn::RSocket, key::String)
    redis_command(conn, "SMEMBERS", [key])
end

# SMOVE source destination member Move a member from one set to another
function smove(conn::RSocket, src::String, dest::String, member::String)
    redis_command(conn, "SMOVE", [src, dest, member])
end

# SPOP key Remove and return a random member from a set
function spop(conn::RSocket, key::String)
    redis_command(conn, "SPOP", [key])
end

# SRANDMEMBER key [count] Get one or multiple random members from a set
function srandmember(conn::RSocket, key::String, count::Integer)
    redis_command(conn, "SRANDMEMBER", [key, count])
end
function srandmember(conn::RSocket, key::String)
    redis_command(conn, "SRANDMEMBER", [key])
end

# SREM key member [member ...] Remove one or more members from a set
function srem(conn::RSocket, key::String, member::String)
    redis_command(conn, "SREM", [key, member])
end
function srem{T<:String}(conn::RSocket, key::String, members::Array{T})
    redis_command(conn, "SREM", vcat(key, members))
end

# SUNION key [key ...] Add multiple sets
function sunion(conn::RSocket, key::String)
    redis_command(conn, "SUNION", [key])
end
function sunion{T<:String}(conn::RSocket, keys::Array{T})
    redis_command(conn, "SUNION", keys)
end

# SUNIONSTORE destination key [key ...] Add multiple sets and store the resulting set in a key
function sunionstore(conn::RSocket, dest::String, key::String)
    redis_command(conn, "SUNIONSTORE", [dest, key])
end
function sunionstore{T<:String}(conn::RSocket, dest::String, keys::Array{T})
    redis_command(conn, "SUNIONSTORE", vcat(dest, keys))
end

# SSCAN key cursor [MATCH pattern] [COUNT count] Incrementally iterate Set elements 
function sscan(conn::RSocket, key::String, cursor::Integer)
    redis_command(conn, "SSCAN", [key, cursor])
end
function sscan(conn::RSocket, key::String, cursor::Integer, match::String, count::Integer)
    redis_command(conn, "SSCAN", [key, cursor, "MATCH", match, "COUNT", count])
end
function sscan(conn::RSocket, key::String, cursor::Integer, match::String)
    redis_command(conn, "SSCAN", [key, cursor, "MATCH", match])
end
function sscan(conn::RSocket, key::String, cursor::Integer, count::Integer)
    redis_command(conn, "SSCAN", [key, cursor, "COUNT", count])
end


# \\  Sorted Sets  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

# ZADD key score member [score member ...] Add one or more members to a sorted set, or update its score if it already exists
function zadd(conn::RSocket, key::String, score::Integer, member::String)
    redis_command(conn, "ZADD", [key, score, member])
end
function zadd(conn::RSocket, key::String, ssmm::Array{(Integer, String)})
    args = foldl((prev, pair) -> vcat(prev, pair[1], pair[2]), [key], ssmm) 
    redis_command(conn, "ZADD", args)
end

# ZCARD key Get the number of members in a sorted set
function zcard(conn::RSocket, key::String)
    redis_command(conn, "ZCARD", [key])
end

# ZCOUNT key min max Count the members in a sorted set with scores within the given values
function zcount(conn::RSocket, key::String, min::Integer, max::Integer)
    redis_command(conn, "ZCOUNT", [key, min, max])
end

# ZINCRBY key increment member Increment the score of a member in a sorted set
function zincrby(conn::RSocket, key::String, incr::Integer, member::String)
    redis_command(conn, "ZINCRBY", [key, incr, member])
end

# ZINTERSTORE destination numkeys key [key ...] [WEIGHTS weight [weight ...]] [AGGREGATE SUM|MIN|MAX] Intersect multiple sorted sets and store the resulting sorted set in a new key
#function zinterstore(conn::RSocket)
    #redis_command(conn, "ZINTERSTORE")
#end

# ZLEXCOUNT key min max Count the number of members in a sorted set between a given lexicographical range
#function zlexcount(conn::RSocket, key::String, min::Integer, max::Integer)
    #redis_command(conn, "ZLEXCOUNT", [key])
#end

# ZRANGE key start stop [WITHSCORES] Return a range of members in a sorted set, by index
function zrange(conn::RSocket, key::String, start::Integer, end_::Integer,
                withscores::Bool=false)
    if withscores
        args = [key, start, end_, "WITHSCORES"]
    else
        args = [key, start, end_]
    end
    redis_command(conn, "ZRANGE", args)
end

# ZRANGEBYLEX key min max [LIMIT offset count] Return a range of members in a sorted set, by lexicographical range
#function zrangebylex(conn::RSocket, key::String)
    #redis_command(conn, "ZRANGEBYLEX", [key])
#end

# ZREVRANGEBYLEX key max min [LIMIT offset count] Return a range of members in a sorted set, by lexicographical range, ordered from higher to lower strings.
#function zrevrangebylex(conn::RSocket, key::String)
    #redis_command(conn, "ZREVRANGEBYLEX", [key])
#end

# ZRANGEBYSCORE key min max [WITHSCORES] [LIMIT offset count] Return a range of members in a sorted set, by score
#function zrangebyscore(conn::RSocket, key::String)
    #redis_command(conn, "ZRANGEBYSCORE", [key])
#end

# ZRANK key member Determine the index of a member in a sorted set
function zrank(conn::RSocket, key::String, member::String)
    redis_command(conn, "ZRANK", [key, member])
end

# ZREM key member [member ...] Remove one or more members from a sorted set
function zrem(conn::RSocket, key::String, member::String)
    redis_command(conn, "ZREM", [key, member])
end
function zrem{T<:String}(conn::RSocket, key::String, members::Array{T})
    redis_command(conn, "ZREM", vcat(key, members))
end

# ZREMRANGEBYLEX key min max Remove all members in a sorted set between the given lexicographical range
#function zremrangebylex(conn::RSocket, key::String)
    #redis_command(conn, "ZREMRANGEBYLEX", [key])
#end

# ZREMRANGEBYRANK key start stop Remove all members in a sorted set within the given indexes
function zremrangebyrank(conn::RSocket, key::String, start::Integer, end_::Integer)
    redis_command(conn, "ZREMRANGEBYRANK", [key, start, end_])
end

# ZREMRANGEBYSCORE key min max Remove all members in a sorted set within the given scores
function zremrangebyscore(conn::RSocket, key::String, min::Integer, max::Integer)
    redis_command(conn, "ZREMRANGEBYSCORE", [key, min, max])
end

# ZREVRANGE key start stop [WITHSCORES] Return a range of members in a sorted set, by index, with scores ordered from high to low
function zrevrange(conn::RSocket, key::String, start::Integer, end_::Integer,
                   withscores::Bool=false)
    if withscores
        args = [key, start, end_, "WITHSCORES"]
    else
        args = [key, start, end_]
    end
    redis_command(conn, "ZREVRANGE", args)
end

# ZREVRANGEBYSCORE key max min [WITHSCORES] [LIMIT offset count] Return a range of members in a sorted set, by score, with scores ordered from high to low
#function zrevrangebyscore(conn::RSocket, key::String)
    #redis_command(conn, "ZREVRANGEBYSCORE", [key])
#end

# ZREVRANK key member Determine the index of a member in a sorted set, with scores ordered from high to low
function zrevrank(conn::RSocket, key::String, member::String)
    redis_command(conn, "ZREVRANK", [key, member])
end

# ZSCORE key member Get the score associated with the given member in a sorted set
function zscore(conn::RSocket, key::String, member::String)
    redis_command(conn, "ZSCORE", [key, member])
end

# ZUNIONSTORE destination numkeys key [key ...] [WEIGHTS weight [weight ...]] [AGGREGATE SUM|MIN|MAX] Add multiple sorted sets and store the resulting sorted set in a new key
#function zunionstore(conn::RSocket)
    #redis_command(conn, "ZUNIONSTORE")
#end

# ZSCAN key cursor [MATCH pattern] [COUNT count] Incrementally iterate sorted sets elements and associated scores 
function zscan(conn::RSocket, key::String, cursor::Integer)
    redis_command(conn, "ZSCAN", [key, cursor])
end
function zscan(conn::RSocket, key::String, cursor::Integer, match::String, count::Integer)
    redis_command(conn, "ZSCAN", [key, cursor, "MATCH", match, "COUNT", count])
end
function zscan(conn::RSocket, key::String, cursor::Integer, match::String)
    redis_command(conn, "ZSCAN", [key, cursor, "MATCH", match])
end
function zscan(conn::RSocket, key::String, cursor::Integer, count::Integer)
    redis_command(conn, "ZSCAN", [key, cursor, "COUNT", count])
end


# \\  HyperLogLog  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

# PFADD key element [element ...] Adds the specified elements to the specified HyperLogLog.
function pfadd(conn::RSocket, key::String, element::String)
    redis_command(conn, "PFADD", [key, element])
end
function pfadd{T<:String}(conn::RSocket, key::String, elements::Array{T})
    redis_command(conn, "PFADD", vcat(key, elements))
end

# PFCOUNT key [key ...] Return the approximated cardinality of the set(s) observed by the HyperLogLog at key(s).
function pfcount(conn::RSocket, key::String)
    redis_command(conn, "PFCOUNT", [key])
end
function pfcount{T<:String}(conn::RSocket, keys::Array{T})
    redis_command(conn, "PFCOUNT", keys)
end

# PFMERGE destkey sourcekey [sourcekey ...] Merge N different HyperLogLogs into a single one.
function pfmerge(conn::RSocket, dest::String, src::String)
    redis_command(conn, "PFMERGE", [dest, src])
end
function pfmerge{T<:String}(conn::RSocket, dest::String, srcs::Array{T})
    redis_command(conn, "PFMERGE", vcat(dest, srcs))
end


# \\  Pub/Sub  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

# PSUBSCRIBE pattern [pattern ...] Listen for messages published to channels matching the given patterns
function psubscribe(conn::RSocket, pattern::String)
    redis_command(conn, "PSUBSCRIBE", [pattern])
end
function psubscribe{T<:String}(conn::RSocket, patterns::Array{T})
    redis_command(conn, "PSUBSCRIBE", patterns)
end

# PUBSUB subcommand [argument [argument ...]] Inspect the state of the Pub/Sub subsystem
function pubsub_channels(conn::RSocket, pattern::String)
    redis_command(conn, "PUBSUB", ["CHANNELS", pattern])
end
function pubsub_channels(conn::RSocket)
    redis_command(conn, "PUBSUB", ["CHANNELS"])
end
function pubsub_numsub(conn::RSocket, channel::String)
    redis_command(conn, "PUBSUB", ["NUMSUB", channel])
end
function pubsub_numsub{T<:String}(conn::RSocket, channels::Array{T})
    redis_command(conn, "PUBSUB", vcat("NUMSUB", channels))
end
function pubsub_numpat(conn::RSocket)
    redis_command(conn, "PUBSUB", ["NUMPAT"])
end

# PUBLISH channel message Post a message to a channel
function publish(conn::RSocket, channel::String, message::String)
    redis_command(conn, "PUBLISH", [channel, message])
end

# PUNSUBSCRIBE [pattern [pattern ...]] Stop listening for messages posted to channels matching the given patterns
function punsubscribe(conn::RSocket)
    redis_command(conn, "PUNSUBSCRIBE")
end
function punsubscribe(conn::RSocket, pattern::String)
    redis_command(conn, "PUNSUBSCRIBE", [pattern])
end
function punsubscribe{T<:String}(conn::RSocket, patterns::Array{T})
    redis_command(conn, "PUNSUBSCRIBE", patterns)
end

# SUBSCRIBE channel [channel ...] Listen for messages published to the given channels
function subscribe(conn::RSocket, channel::String)
    redis_command(conn, "SUBSCRIBE", [channel])
end
function subscribe{T<:String}(conn::RSocket, channels::Array{T})
    redis_command(conn, "SUBSCRIBE", channels)
end

# UNSUBSCRIBE [channel [channel ...]] Stop listening for messages posted to the given channels
function unsubscribe(conn::RSocket)
    redis_command(conn, "UNSUBSCRIBE")
end
function unsubscribe(conn::RSocket, pattern::String)
    redis_command(conn, "UNSUBSCRIBE", [pattern])
end
function unsubscribe{T<:String}(conn::RSocket, patterns::Array{T})
    redis_command(conn, "UNSUBSCRIBE", patterns)
end


# \\  Transactions  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

# DISCARD Discard all commands issued after MULTI
function discard(conn::RSocket)
    redis_command(conn, "DISCARD")
end

# EXEC Execute all commands issued after MULTI
function exec(conn::RSocket)
    redis_command(conn, "EXEC")
end

# MULTI Mark the start of a transaction block
function multi(conn::RSocket)
    redis_command(conn, "MULTI")
end

# UNWATCH Forget about all watched keys
function unwatch(conn::RSocket)
    redis_command(conn, "UNWATCH")
end

# WATCH key [key ...] Watch the given keys to determine execution of the MULTI/EXEC block 
function watch(conn::RSocket, key::String)
    redis_command(conn, "WATCH", [key])
end
function watch{T<:String}(conn::RSocket, keys::Array{T})
    redis_command(conn, "WATCH", keys)
end


# \\  Scripting  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

# # EVAL script numkeys key [key ...] arg [arg ...] Execute a Lua script server side
# function eval(conn::RSocket)
#     redis_command(conn, "EVAL")
# end

# # EVALSHA sha1 numkeys key [key ...] arg [arg ...] Execute a Lua script server side
# function evalsha(conn::RSocket)
#     redis_command(conn, "EVALSHA")
# end

# # SCRIPT EXISTS script [script ...] Check existence of scripts in the script cache.
# function script_exists(conn::RSocket)
#     redis_command(conn, "SCRIPT", ["EXISTS"])
# end

# # SCRIPT FLUSH Remove all the scripts from the script cache.
# function script_flush(conn::RSocket)
#     redis_command(conn, "SCRIPT", ["FLUSH"])
# end

# # SCRIPT KILL Kill the script currently in execution.
# function script_kill(conn::RSocket)
#     redis_command(conn, "SCRIPT", ["KILL"])
# end

# # SCRIPT LOAD script Load the specified Lua script into the script cache. 
# function script_load(conn::RSocket)
#     redis_command(conn, "SCRIPT", ["LOAD"])
# end

end
