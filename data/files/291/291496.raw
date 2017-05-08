path = "/home/jones/Documentos/TEO/instâncias/v10.txt"

text = readdlm(path, ' ')[4, :]

prizes = text[find(r -> isa(r, Float64), text)]

text = readdlm(path, ' ')[7, :]

penalties = text[find(r -> isa(r, Float64), text)]

matrix = readdlm(path)[10:end, :]

println(prizes, "\n", penalties)

