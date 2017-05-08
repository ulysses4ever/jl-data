include("SimpleTok.jl")
include("CorpusTools.jl")

import SimpleTokenizer.detag
import SimpleTokenizer.tokenize
import CorpusTools.Files
import CorpusTools.load_files
import CorpusTools.grep_count


file = Files("/home/matias/Documentos/Program/julia/Ling/corpw/brown/")


println(length(tokenize(load_files(file))))

println(grep_count("apple pies", detag(load_files(file))))
println(grep_count("apple trees", detag(load_files(file))))
println(grep_count("pies", detag(load_files(file))))
println(grep_count("trees", detag(load_files(file))))
println(grep_count("apple", detag(load_files(file))))
