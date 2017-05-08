module LoadCsv

export readOne, readLine

stripchars = ['"', '\'']

function readOne(stream, callback; dlm=',', nl='\n')

    let word = Char[], char = Char

        while true
            char = read(stream, Char)

            if char == dlm || char == nl
                break
            end

            push!(word, char)
        end

        callback(strip(join(word), stripchars), char)
    end
end

function readLine(stream, callback; dlm=',', nl='\n')

    let line = ASCIIString[], word = String, char = Char, res = Bool

        function assign(w,c)
            word,char = w,c
        end

        while true

            readOne(stream, assign, dlm=dlm, nl=nl)

            if char == nl
                break
            end

            try
                push!(line, word)
            catch e
                push!(line, "nil") # Igoring utf8, cause i know the rows i need dont have it
            end
        end

        callback(line)
    end
end

end
