

function detag(text::String, reg=r"/.*? ", rep= " ")
    replace(text, reg, rep)
end

function detag(texts::Array{String}, reg= r"/.*? ", rep= " ")
    #remove tags
    strings= String[]
    for text in texts
        push!(strings, detag(text, reg, rep))
    end
    return strings
end

function tokenize(text::String, lang="es", punct=false)
    #Simple tokenizer
    str = replace(text, r"[,.;:.'\"!¡?¿_\n/\t\n\(\)\{\}\[\]-]", " ")
    str = replace(str, r" +", " ")
    str = split(str, " ")
end

function tokenize(texts::Array{}, lang="es", punct=false)
    tokenize(join(texts, " "), lang, punct)
end

