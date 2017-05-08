function get_first_item(items)
    try
        items[1]
    catch e
        if isa(e, BoundsError)
            println("Error: Empty collection")
        elseif isa(e, KeyError)
            println("Error: Key not found")
        else
            println("Error: $e")
        end
    end
end

get_first_item(["a", "b", "c"]) # "a"
get_first_item([]) # Error: Empty collection (error message)
get_first_item(Dict(:a=>1, :b=>2)) # Error: KeyError(1) (error message)

f = open("sample.txt")
try
    for line in readlines(f)[1:5]
        println("line: $line")
    end
finally
    close(f)
end
