
module temper

using DataFrames


function dotempo(filename::String)
    println("file: ", filename)
    data = read_table(filename)

    println("data: ", data)
end

end

println("args: ", ARGS)
if length(ARGS) > 0
    temper.dotempo(ARGS[1])
end
