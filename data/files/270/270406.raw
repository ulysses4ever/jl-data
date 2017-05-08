#=
Função que calcula a distânca do cosseno entre dois vetores.

Entradas:

vetor1 e vetor2  -> Array de tamanho n. As dimensões com o valor 0 serão descartadas.

Saída:

cosseno          -> Distância do cosseno entre os dois vetores levando em conta apenas as dimensões diferentes de 0 dos dois vetores.
=#

function cosseno(vetor1,vetor2)
  # Busca todos os índices das posições que são diferentes de 0 nos dois vetores
  ind_v1 = find(x->x>0,vetor1)
  ind_v2 = find(x->x>0,vetor2)

  # Busca a intereseção entre os dois conjuntos de índices
  ind = intersect(ind_v1,ind_v2)

  # Verifica se o tamanho da interseção é menor ou igual a 1
  if length(ind) <= 1
    return Inf
  end

  # Calcula o cosseno entre os dois vetores nas dimensões encontradas
  return 1 - dot(vec(vetor1[ind]),vec(vetor2[ind]))/(norm(vec(vetor1[ind]))*norm(vec(vetor2[ind])))
end
