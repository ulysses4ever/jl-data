
import Base.show

typealias Concordance Dict{String, Array{Int,1}}

# Call `concordance` with a string of text you'd like to analyze.
# It will output a dictionary of words mapped to arrays of sentence
# numbers where those words appear: [ "word" => {1,1,3,4} ]
function concordance(content::String)
    sentences = split_sentences(content)

    concordance_data = Concordance()
    for s in 1:length(sentences)
        sentence = rstrip(sentences[s])

        # Strip trailing punctuation - to make it easier to parse words
        # To make this more concise, I've submitted a pull request here:
        # https://github.com/JuliaLang/julia/pull/6779
        if endswith(sentence, '.') ||
           endswith(sentence, '?') ||
           endswith(sentence, '!')

            sentence = chop(sentence)
        end

        # As with parsing sentences (see below), regular expressions may not
        # be the perfect tool for parsing words. Potentially some more
        # validation could be done here (checking against a dictionary, etc)
        words = eachmatch(r"\w[\'\w.-]*", sentence)
        for word in words
            push!(get!(concordance_data, lowercase(word.match), Int[]), s)
        end
    end

    concordance_data
end

function split_sentences(sentences)
    # A fairly complicated regex is used here to split sentences. Regular expressions
    # are far from my favorite tools, however, they're more approachable than
    # hand-rolled parsing code and more concise than possible NLP solutions.
    split(sentences, r"((?<=[a-z0-9\)][.?!])|(?<=[a-z0-9][.?!]\"))(\s|\r\n)(?=\"?[A-Z])")
end

# `show(concordance)` will do some pretty printing to make the concordance
# data easier to read
function show(c::Concordance)
    c_flat = collect(c)
    sort!(c_flat, lt = (lhs, rhs) -> lhs[1] < rhs[1])

    for word_data in c_flat
        println("$(word_data[1])\t$(length(word_data[2])): $(word_data[2])")
    end
end
