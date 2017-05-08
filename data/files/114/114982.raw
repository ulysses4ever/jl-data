using CorpusTools
#import Files

#file = Files("/home/matias/Documentos/Program/julia/temp/eltiempo-1990.txt")
file = load_files(Files("/home/matias/Documentos/Program/julia/Ling/corpw/brown/"))

test="esta es una prueba, a mí me gustan las pruebas porque si uno prueba
    pues las cosas salen mucho mejor. es mejor si uno prueba, y sí es bueno
    y es linod, y es chévere, y es genial, muy es genial, mal genial"

#col =collocations("apple", detag(load_files(file)))

println(collocations("apple", detag(file), test="deltap"))
