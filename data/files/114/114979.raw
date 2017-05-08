include ("CorpusTools.jl")

files = CorpusTools.Files("/home/matias/Documentos/Program/julia/temp/")

#@time st = CorpusTools.grep_context(r"navegante", files, 6)

println("\nSin regex sin cargar: \n\n")


@time println(CorpusTools.grep_count("navegar", files))

println("\nSin regex cargando: \n\n")

@time println(CorpusTools.grep_count("navegar", CorpusTools.load_files(files)))


println("\nSin cargar: \n\n")

@time println(CorpusTools.grep_count(r"naveg.*? ", files))

println("\nCargando: \n\n")

@time println(CorpusTools.grep_count(r"naveg.*? ",CorpusTools.load_files(files)))

#CorpusTools.to_file("test.txt",st)
