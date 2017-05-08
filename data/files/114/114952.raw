

function detag(text::String, reg=r"/.*? ", rep= "")
    replace(text, reg, rep)
end

function detag(texts::Array{}, reg= r"/.*? ", rep= "")
    #remove tags
    strings= String[]
    for text in texts
        push!(strings, detag(text, reg, rep))
    end
    return strings
end

function tokenize(text::String; lang="es", punct=false)
    #Simple tokenizer
    if lang=="es"
        return(tokenizeEs(text, punct))
    end
end

function tokenizeEs(text::String, punct=false)
    if punct
        str = strip(text)
        str = split(str, r"((?<=[,\.;:'\"!¡?¿_\n/\t\(\)\{\}\[\]\- ]) *)|((?=[,\.;:'\"!¡?¿_\n/\t\(\)\{\}\[\]\- ]) ?)")

    else
        str = strip(text)
        str = replace(str, r"[,\.;:'\"!¡?¿_\n/\t\(\)\{\}\[\]\- ]+", "<!%")
        str = split(str,"<!%")
    end
    return str
end

function tokenize(texts::Array{}; lang="es", punct=false)
    tokens = Array{String}[]
    for text in texts
        push!(tokens,tokenize(text, lang=lang, punct = punct))
    end
    return tokens
end


#Count words in text

function word_count(text::String)
    return(length(tokenize(text)))
end

function word_count(texts::Array{})
    N = Int64[]
    for text in texts
        push!(N, length(tokenize(text)))
    end
    return N
end


function word_count(files::Files; verbose = false)
    N = Int64[]
    for name in files.names
        if verbose
            println(string("Reading: ", name))
        end
        push!(N, word_count(readall(open(name))))
    end
    return N
end
