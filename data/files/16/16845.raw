function table_reader(filename::String, variable_name::String)
    assignment = Expr(:global,
                      Expr(:(=),
                           symbol(variable_name),
                           DataFrames.readtable(filename)))
    to_top = Expr(:toplevel,
                  assignment,
                  Expr(:export, symbol(variable_name)))
    eval(to_top)
end
