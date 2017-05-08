type Instancia
  function Instancia(path::String)
    file = open(path)
    text = readlines(file)
    close(file)

    prizes = readdlm(IOBuffer(text[2,1]))';

    penalties = readdlm(IOBuffer(text[5, 1]))';

    matrix = readdlm(path)[8:end, :];

    return prizes, penalties, matrix;
  end
end

