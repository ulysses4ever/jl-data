
import Base.show

typealias Concordance Dict{String, Array{Int,1}}

function concordance(content::String)
    sentences = split_sentences(content)

    concordance_data = Concordance()
    for s in 1:length(sentences)
        sentence = sentences[s]

        # strip trailing punctuation - to make it easier to parse words
        # To make this more concise, I've submitted a pull request here:
        # https://github.com/JuliaLang/julia/pull/6779
        if endswith(sentence, '.') ||
           endswith(sentence, '?') ||
           endswith(sentence, '!')

            sentence = chop(sentence)
        end

        words = eachmatch(r"\w[\'\w.-]*", sentence)
        for word in words
            push!(get!(concordance_data, lowercase(word.match), Int[]), s)
        end
    end

    concordance_data
end

function split_sentences(sentences)
    split(sentences, r"((?<=[a-z0-9\)][.?!])|(?<=[a-z0-9][.?!]\"))(\s|\r\n)(?=\"?[A-Z])")
end

function show(c::Concordance)
    c_flat = collect(c)
    sort!(c_flat, lt = (lhs, rhs) -> lhs[1] < rhs[1])

    for word_data in c_flat
        println("$(word_data[1])\t$(length(word_data[2])): $(word_data[2])")
    end
end
