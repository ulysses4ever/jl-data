function table_reader(filename, variable_name)
    assignment = expr(:global,
                      Any[expr(:(=),
                               Any[symbol(variable_name),
                                   DataFrames.read_table(filename)])])
    to_top = expr(:toplevel,
                  Any[assignment,
                      expr(:export,
                           Any[symbol(variable_name)])])
    eval(to_top)
end
