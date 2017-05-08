#!/usr/bin/env julia
#
# A POSIX echo implementation
#


count = length(ARGS)

if count == 0
        println()
        exit()
end

specials = [
        'a' => '\a',
        'b' => '\b',
        'f' => '\f',
        'n' => '\n',
        'r' => '\r',
        't' => '\t',
        'v' => '\v',
        '\\' => '\\'
]

function simple(ch)
        if ch == '\\'
                return "\\"
        end

        print(ch)
        return ""
end

function special(ch)
        if ch == 'c'
                exit()
        elseif ch == '0'
                return "\\0"
        end

        try
                print(specials[ch])
        catch
                print('\\', ch)
        end

        return ""
end

function octal_plus_simple(token)
        try
                v = parseint(Uint8, token[2:end], 8)
                write(STDOUT, v)
                return ""
        catch
                v = parseint(Uint8, token[2:end-1], 8)
                write(STDOUT, v)
                return(simple(token[end]))
        end
end

for i = 1:count
        token = ""
        for ch in ARGS[i]
                if token == ""
                        token = simple(ch)
                elseif token == "\\"
                        token = special(ch)
                else
                        token = "$token$ch"
                        if length(token) == 5 || ch < '0' || ch > '7'
                                token = octal_plus_simple(token)
                        end
                end

        end

        if token == "\\"
                print("\\")
        elseif token != ""
                octal_plus_simple(token)
        end
        print(i == count ? '\n' : ' ')
end
