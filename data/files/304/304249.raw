# A função calcula um vetor ortogonal ao vetor passado como parametro #
  function teste(vector::Array{Float64,1})
    # Geramos um novo vetor Y com valores aleatorios#
    tam = size(vector)
    y = rand(tam)*mean(vector)

    tmp = 0.0
    for i = 1:tam[1] - 1
      tmp = tmp + vector[i]*y[i]
    end

    # Retornando Y #
    y[tam[1]] = - tmp/vector[tam[1]]
    return y
  end


