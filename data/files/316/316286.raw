module Sequoia

using Compat, NullableArrays


export  # modules
        CSV, SQLite3,

        # types
        C, F, Cursor, Table, NullableTable,

        # consts
        sqlite3_lib,

        # methods
        ncols,
        reset!,
        step!


include("../deps/deps.jl")
include("cursor.jl")
# in
include("in/sqlite3.jl"); # using SQLite3
include("in/csv.jl")
# out
include("out/table.jl")
include("out/nullabletable.jl")
# include("out/matrix.jl")




end # module
