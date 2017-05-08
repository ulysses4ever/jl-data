module SQLite3

using Sequoia

export  # types
        DB,

        # methods
        query

include("sqlite3/consts.jl")
include("sqlite3/utils.jl")
include("sqlite3/c_api.jl")
include("sqlite3/db.jl")
include("sqlite3/query.jl")

function Sequoia.Cursor(stmt::Stmt)
    status = SQLite3.execute!(stmt)
    ncols::Int = sqlite3_column_count(stmt.handle)
    fields = get_fields(stmt, ncols)
    coltypes = get_coltypes(stmt, ncols)
    return Cursor(ncols, fields, coltypes, stmt, Int(status), 0)
end

# construction utilities

function get_fields(stmt::Stmt, ncols=sqlite3_column_count(stmt.handle))
    fields = [ symbol(bytestring(sqlite3_column_name(stmt.handle, i-1))) for i in 1:ncols ]
    return Tuple{fields...}
end

function get_coltypes(stmt::SQLite3.Stmt, ncols::Int)
    types = Array{DataType, 1}()
    for i in 1:ncols
        typ = sqlite3_types[sqlite3_column_type(stmt.handle, i-1)]
        push!(types, typ)
    end
    return Tuple{types...}
end

# primitives

# Base.close(curs::Cursor{SQLite3.Stmt}) = close(curs.stmt)

reset!(stmt::Stmt) = sqlite3_reset(stmt.handle)
function Sequoia.reset!(curs::Sequoia.Cursor{SQLite3.Stmt})
    reset!(curs.io)
    curs.status = execute!(curs.io)
    return curs
end

function Base.eof(curs::Sequoia.Cursor)
    (curs.status == SQLITE_DONE || curs.status == SQLITE_ROW) || sqliteerror(curs.stmt.db)
    return curs.status == SQLITE_DONE
end

function Base.readline(curs::Sequoia.Cursor, delim::Union{Char,ByteString}=",", buf::IOBuffer=IOBuffer())
    eof(curs) && return ""
    n = ncols(curs)
    for i = 1:n
        val = sqlite3_column_text(curs.io.handle, i-1)
        val != C_NULL && write(buf, bytestring(val))
        write(buf, ifelse(i == n, '\n', delim))
    end
    return takebuf_string(buf)
end

@inline function Sequoia.step!(curs::Sequoia.Cursor)
    curs.status = execute!(curs.io)
    return curs
end

query(db::DB, sql::String) = Sequoia.Cursor(SQLite3.Stmt(db, sql))

# function delim_res(curs::Cursor; delim=',', buf::IOBuffer=IOBuffer())
#     n = ncols(curs)
#     while curs.status == 100
#         for i = 1:n
#             val = sqlite3_column_text(curs.stmt.handle, i-1)
#             val != C_NULL && write(buf, bytestring(val))
#             write(buf, ifelse(i == n, '\n', delim))
#         end
#         step!(curs)
#     end
#     return seekstart(buf)
# end
#
# function results(curs::Sequoia.Cursor)
#     return readdlm(delim_res(curs), ',', '\n')
# end

# show

function Base.show(io::IO, curs::Cursor{SQLite3.Stmt})
    println(io, summary(curs))
    curs.status == 100 ? print(io, "CURRENT: $(readline(curs))") :
    curs.status == 101 && println(io, "No more results to show")
    info("status: ", curs.status)
end


end # module SQLite3
