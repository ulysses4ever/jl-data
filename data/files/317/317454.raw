#
# 辞書ファイルに A-Z の単語が入っているので、アナグラムのグループを見つける
#
module Anagram

function sign(words::Array{ASCIIString,1})
    n = length(words)
    signs = Array(Tuple{ASCIIString, ASCIIString}, n)
    for i in 1:n
        signs[i] = (words[i], Base.sort(collect(words[i])))
    end
    return signs
end

function sort(signs)
    return Base.sort(signs, by=(pair -> pair[2]))
end

function reduce(signs)
    groups    = []
    group     = None
    last_sign = None

    for (w, s) in signs
        if s != last_sign
            if group != None
                push!(groups, group)
            end
            group     = [w]
            last_sign = s
        else
            push!(group, w)
        end
    end
    push!(groups, group)

    return groups
end

function load_dictionary(file)
    dictionary = Array(ASCIIString, 0)
    open(file) do io
        for l in eachline(io)
            push!(dictionary, chomp(l))
        end
    end
    return dictionary
end


function main()
    dictionary = load_dictionary("data/dictionary.dat")
    println(dictionary)

    signs = sign(dictionary)
    println(signs)

    sorted = sort(signs)
    println(sorted)

    groups = reduce(sorted)
    println("====================================")
    for g in groups
        println(g)
    end
end

end
