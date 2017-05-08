# Token types
const PERIOD = 1
const QUESTION = 2
const EXCLAMATION = 3

function lex(s::String)
    tokens = Array(Int, 0)

    i = nextind(s, 0)

    line, character = 1, 0

    while i <= endof(s)
        chr = s[i]
        character += 1

        while isspace(chr)
            if chr == '\n'
                line += 1
                character = 0
            end
            i = nextind(s, i)
            if i <= endof(s)
                chr = s[i]
                character += 1
            else
                return tokens
            end
        end

        if chr != 'O'
            msg = @sprintf(
                "Invalid token found at line %d, character %d",
                line,
                character
            )
            throw(ArgumentError(msg))
        end
            
        i = nextind(s, i)
        if i <= endof(s)
            chr = s[i]
            character += 1
        else
            msg = @sprintf(
                "Premature end of input at line %d, character %d",
                line,
                character
            )
            throw(ArgumentError(msg))
        end
        if chr != 'o'
            msg = @sprintf(
                "Invalid token found at line %d, character %d",
                line,
                character
            )
            throw(ArgumentError(msg))
        end

        i = nextind(s, i)
        if i <= endof(s)
            chr = s[i]
            character += 1
        else
            msg = @sprintf(
                "Premature end of input at line %d, character %d",
                line,
                character
            )
            throw(ArgumentError(msg))
        end
        if chr != 'k'
            msg = @sprintf(
                "Invalid token found at line %d, character %d",
                line,
                character
            )
            throw(ArgumentError(msg))
        end

        i = nextind(s, i)
        if i <= endof(s)
            chr = s[i]
            character += 1
        else
            msg = @sprintf(
                "Premature end of input at line %d, character %d",
                line,
                character
            )
            throw(ArgumentError(msg))
        end
        if chr == '.'
            push!(tokens, PERIOD)
        elseif chr == '?'
            push!(tokens, QUESTION)
        elseif chr == '!'
            push!(tokens, EXCLAMATION)
        else
            msg = @sprintf(
                "Invalid token found at line %d, character %d",
                line,
                character
            )
            throw(ArgumentError(msg))
        end

        i = nextind(s, i)
    end

    return tokens
end
