
import Base.show

typealias Concordance Dict{String, Array{Int,1}}

# Call `concordance` with a string of text you'd like to analyze.
# It will output a dictionary of words mapped to arrays of sentence
# numbers where those words appear: [ "word" => {1,1,3,4} ]
function concordance(content::String)
    sentences = split_sentences(content)

    concordance_data = Concordance()
    for s in 1:length(sentences)
        sentence = normalize_sentence(sentences[s])
        words = split_words(sentence)

        for word in words
            # record the sentence number where this word was found
            push!(get!(concordance_data, normalize_word(word.match), Int[]), s)
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

function normalize_sentence(sentence)
    sentence = rstrip(sentence)
    endswith(sentence, ['.','?','!']) ? chop(sentence) : sentence
end

function split_words(sentence)
    # As with parsing sentences (see above), regular expressions may not
    # be the perfect tool for parsing words. Potentially some more
    # validation could be done here (checking against a dictionary, etc)
    collect(eachmatch(r"\w[\'\w.-]*", sentence))
end

function normalize_word(word)
    lowercase(word)
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
