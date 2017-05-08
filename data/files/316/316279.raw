function materialize!(curs::Cursor, restype::DataType)
    Co = typeof(curs).parameters[2]
    Fi = typeof(curs).parameters[3]
    n = ncols(curs)
    columns, nrows = _materialize(curs, restype)
    return columns, Fi, nrows
end
