module CSV

using Sequoia

include("csv/utils.jl")

# Cursor

function Sequoia.Cursor(filepath)
    file = CSV.File(filepath)
    ncols = file.cols
    header = file.header
    io = open(file)
    seek(io, io.file.datapos + 1)
    coltypes = Tuple{file.types...}
    fields = Symbol[]
    # fix issue where newline char is currently captured into name of last field
    for i in 1:length(header)-1
        push!(fields, header[i])
    end
    push!(fields, header[end][1:end-1])
    fields = Tuple{fields...}
    return Sequoia.Cursor(ncols, fields, coltypes, io, 100, 0)
end

function Base.show(io::IO, curs::Sequoia.Cursor{CSV.Stream})
    println(io, summary(curs))
    row = read(curs)
    print(io, "CURRENT: ")
    for (i, val) in enumerate(row)
        isnull(val) ? print(io, "#NULL") : print(io, val.value)
        i < length(row) && print(", ")
    end
    print('\n')
    info("status: ", curs.status)
end

function Base.read(curs::Sequoia.Cursor{CSV.Stream})
    io = curs.stmt
    types = collect(typeof(curs).parameters[2].parameters)
    startpos = curs.stmt.pos
    res = Array(Any, length(types))
    for (i, typ) in enumerate(types)
        v = CSV.readfield(io, typ, curs.row, i)
        res[i] = Nullable(v[1], v[2])
    end
    curs.stmt.pos = startpos
    return tuple(res...)
end

function Sequoia.reset!(curs::Sequoia.Cursor{CSV.Stream})
    curs.io.pos = curs.io.file.datapos + 1
    curs.row = 0
end

function Sequoia.step!(curs::Sequoia.Cursor{CSV.Stream})
    io = curs.stmt
    CSV.skipn!(io, 1, io.file.quotechar, io.file.escapechar)
    curs.row += 1
    return curs
end

end # module CSV
