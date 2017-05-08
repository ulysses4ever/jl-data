using CorpusTools
using DataFrames

files = load_files(Files("/home/matias/Documentos/Corpora/Inglés/brown/raw2/"));
files2 = load_files(Files("/home/matias/Documentos/Corpora/Inglés/brown/raw2/ca01.txt"));

#dir_out = "/home/matias/Documentos/Corpora/Inglés/brown/raw2/";

collos = collocations("house", files);
println(head(collos))

writetable("/home/matias/Documentos/temp/collos1.txt", collos, separator='\t', header=true);
