

function detag(text::String, reg=r"/.*? ", rep= " ")
    replace(text, reg, rep)
end

function detag(texts::Array{}, reg= r"/.*? ", rep= " ")
    #remove tags
    strings= String[]
    for text in texts
        push!(strings, detag(text, reg, rep))
    end
    return strings
end

function tokenize(text::String, lang="es", punct=false)
    #Simple tokenizer
    str = replace(text, r"[,.;:.'\"!¡?¿_\n/\t\(\)\{\}\[\]-]", " ")
    str = replace(str, r" +", " ")
    str = replace(str, r" $","")
    str = split(str, " ")
end

function tokenize(texts::Array{}, lang="es", punct=false)
    tokenize(join(texts, " "), lang, punct)
end


#Count words in text

function word_count(text::String)
    return(length(tokenize(text)))
end

function word_count(files::Files; verbose = false)
    counts = Float64[]
    for name in files.names
        if verbose
            println(string("Reading: ", name))
        end
        push!(counts, word_count(readall(open(name))))
    end
    return counts
end

