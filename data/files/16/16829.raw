function table_reader(filename, variable_name)
  @eval begin
    global $(symbol(variable_name)) = DataFrames.read_table($filename)
  end
end
