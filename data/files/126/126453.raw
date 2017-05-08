function vector_of_offsets(i_max_char::Int)
    vcat(i_max_char:-1:0,1:i_max_char)
end

function vector_of_characters(max_char::Char)
    vcat('A':max_char,max_char-1:-1:'A')
end

function line_to_print(i_max_char::Int)
    (offset::Int, letter::Char) ->
    if(letter == 'A')
        return (repeat(" ", offset), 'A')
    else
        return (repeat(" ", offset), letter, repeat(" ",2*(i_max_char - offset - 1)-1), letter)
    end
end

function print_error(message::String)
    println(message)
    println("Usage: julia diamond.jl <single-letter>")
end

function args_are_valid()
    if(length(ARGS) > 1)
        print_error("too many arguments")
        return false
    elseif(length(ARGS) < 1)
        print_error("please specify the letter you want to print to")
        return false
    elseif((length(ARGS[1]) > 1) ||
           (search(ascii('A':'Z'), uppercase(ARGS[1])[1]) == 0))
        print_error("please specify a single upper or lower case letter")
        return false
    end
    return true
end

if(args_are_valid())
    let letter_to_print = uppercase(ARGS[1])[1], 
        index_of_letter = search(ascii('A':'Z'), letter_to_print)
        lines_to_print = map(line_to_print(index_of_letter), 
                             vector_of_offsets(index_of_letter-1), 
                             vector_of_characters(letter_to_print))
        for l in lines_to_print
            println(l...)
        end
    end
end

   


