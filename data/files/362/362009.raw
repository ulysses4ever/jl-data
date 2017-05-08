#      #
#      #
#      #

# A função calcula um vetor ortogonal ao vetor passado como parametro #
function orto(vector::Array{Float64,1})
  # Assert para checar se o vetor vector não é o vetor zero!! #
  #TODO#

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

# A função recebe uma matriz A e um vetor B #
# .... e retornar o resultado da operação   #
function solve(matrix::Array{Float64,2}, rhs::Array{Float64,1})
  # Assert para checar se primeiro matriz é não singular #
  # Segundo Assert checar se o matrix e rhs tem o mesmo número de linhas #
  #TODO#

  tmp = inv(matrix)

  result = tmp*rhs
end

#      Recebe a matriz A e o vetor b e tenta reproduzir um sistema com condicinamento melhor        #
#      trocando a linha(line) por sua ortogonal, e retornando um sistema identico, de mesma solução #
function improve(matrix::Array{Float64,2}, rhs::Array{Float64,1}, line::Int64)
  # Assert para checar se a linha está dentro do esperado!!!! #
  #TODO#

  A_rows, A_cols = size(matrix)
  # Criamos uma nova matrix que iremos trocar a linha #line #
  new_line = zeros(A_cols)
  new_matrix = matrix'

  # Copiando vetor que será trocado #
  for i = 1:A_cols
    new_line[i] = new_matrix[(line - 1)*A_cols + i]
  end

  # Achando vetor ortogonal #
  new_line = orto(new_line)

  # Copiando vetor mudado #
  for i = 1:A_cols
    new_matrix[(line - 1)*A_cols + i]= new_line[i]
  end

  new_matrix = new_matrix'

  # Recalculando RHS(Right-hand-side) #
  new_rhs = new_matrix*inv(matrix)*rhs

  # Retornando resultados #
  return new_matrix, new_rhs
end
