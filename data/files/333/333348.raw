#=
Função que calcula a distância euclidiana entre dois pontos.

Entradas:

ponto1 e ponto2  -> Array de tamanho n. As dimensões com o valor 0 serão descartadas.

Saída:

euclidiana          -> Distância euclidiana entre os dois pontos levando em conta apenas as dimensões diferentes de 0 dos dois pontos.
=#

function euclidiana(ponto1,ponto2)
  # Busca todos os índices das posições que são diferentes de 0 nos dois pontos
  ind_p1 = find(x->x>0,ponto1)
  ind_p2 = find(x->x>0,ponto2)

  # Busca a intereseção entre os dois conjuntos de índices
  ind = intersect(ind_p1,ind_p2)

  # Verifica se o tamanho da interseção é menor do que 1
  if length(ind) < 1
    return Inf
  end

  # Calcula a distância euclidiana entre os dois pontos nas dimensões encontradas
  return sqrt(sum((ponto1[ind] - ponto2[ind]) .^ 2))
end
