abstract F{f}
abstract C{c}

type Cursor{S, Co<:Tuple, Fi<:Tuple} <: IO
    ncols::Int
    fields::Type{Fi}
    coltypes::Type{Co}
    io::S
    status::Int
    row::Int
end

# primitives

ncols(curs::Cursor) = curs.ncols
Base.read(curs::Cursor) = nothing
step!(curs::Cursor) = nothing
reset!(curs::Cursor) = nothing
Base.close(curs::Cursor) = nothing


# out utilities

function materialize!(curs::Cursor, restype::DataType)
    Co = typeof(curs).parameters[2]
    Fi = typeof(curs).parameters[3]
    n = ncols(curs)
    columns, nrows = _materialize(curs, restype)
    return columns, Fi, nrows
end

# show

function Base.summary(curs::Cursor)
    fieldnames = gen_fieldnames(collect(curs.fields.parameters))
    res = "Cursor with columns $fieldnames"
end

function gen_fieldnames(fields)
    # fieldnames = fields.parameters
    n = length(fields)
    res = "("
    for i in eachindex(fields)
        i == n ? res = res * "$(fields[i]))" :
                 res = res * "$(fields[i]), "
    end
    return res
end
