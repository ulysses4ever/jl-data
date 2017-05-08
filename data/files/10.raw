using Gumbo

include("résumé.jl")
include("tex-export.jl")
include("parser.jl")

TEST_PATH = """
/home/fengyang/Documents/Programming/totalverb.github.io/resume/index.html"""

htmlrésumé = readall(TEST_PATH) |> parsehtml

arésumé = Résumé("", "", "", Organization(""), [], Dict([]))
for elem in children(htmlrésumé.root)
    parse!(ParseState([]), arésumé, elem)
end

openpdf(texify(arésumé))

println(arésumé)
