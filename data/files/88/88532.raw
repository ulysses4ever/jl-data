using DataFrames
using DataStructures
using NLP

data = readtable(ARGS[1])
c=counter(ASCIIString)

for title=data[:title]
    title = strip(lowercase(title))
    title = replace(title, r"[^a-z\s]", "")
    title = replace(title, r"\s+", " ")
    println(title)
    for word=convert(Vector{ASCIIString}, tokenize(title))
        push!(c, word)
    end
end

words = [w for w=keys(c)]
words_sorted = sort(words, by=w -> -c[w])

for i=1:min(10, length(words_sorted))
    println(words_sorted[i], "\t", c[words_sorted[i]])
end