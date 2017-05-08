type Instancia
  function Instancia(path::String)
    file = open(path)
    text = readlines(file)
    close(file)

    prizes = readdlm(IOBuffer(text[4,1]))';

    penalties = readdlm(IOBuffer(text[7, 1]))';

    matrix = readdlm(path)[10:end, :]

    return prizes, penalties, matrix;
  end
end

