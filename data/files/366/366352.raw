module DBI2DBAPI

using DBI
using DBAPI

type DBIDriver <: AbstractDatabaseInterface
end

type DBICursor <: AbstractDatabaseCursor{DBIDriver}
    handle::DatabaseHandle
end

type DBIConnection <: AbstractDatabaseConnection{DBIDriver}
    cursors::Tuple{DBICursor}
    dbargs::Tuple{Any}
end


@doc """
The first argument needs to be 

Passes the trailing args list on directly

kwargs are completely ignored but included for completeness
""" ->
function connect(::Type{DBIDriver}, drv::Type{T}, args...; kwargs...)
    return DBIConnection(drv, args)
end

@doc """
Internally, closes all open cursors
""" ->
function close(conn::DBIConnection)
    map(close, conn.cursors)
end

@doc """
Does nothing since DBI is not transactional.
""" ->
function commit(conn::DBIConnection)
end

@doc """
Does nothing since DBI is not transactional
""" ->
function rollback(conn::DBIConnection)
end

@doc """
Emulates cursors by using seperate connections for each cursor
""" ->
function cursor(conn::DBIConnection)
    cur = DBICursor(connect(typeof(conn.handle), conn.dbargs...)
    push!(cursors, cur)
    return cur
end

# callproc is left unimplemented

@doc """
Internally closes the connection the cursor contains
""" ->
function close(cur::DBICursor)
    disconnect(cur.handle)
end

@doc """
Similar to MySQLdb from Python the string is used to format the data in the
tuple preventing SQL injection attacks
""" ->
function execute(cur::DBICursor, sql::String; parameters::Tuple{String})
    prepare(cur.handle, sql)
end

@doc """
Similar to MySQLdb from Python the string is used to format the data in the
tuple preventing SQL injection attacks

TODO, implement parameter 
""" ->
function executemany(cur::DBICursor, sql::String, seq_of_parameters::Tuple{String})
    stmt = prepare(cur.handle, sql)
    map(pars -> execute(stmt), seq_of_parameters)
end

end # module
