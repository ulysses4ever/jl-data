#=
Função que calcula a previsão da nota para um usuário em um item utilizando o algoritmo do k-NN.

Entradas:

x              -> Tupla no formato (id_item,id_usuario);
dados          -> Matriz IxU contendo os ratings conhecidos - 0 para ratings desconhecidos;
k              -> Quantidade de vizinhos;
simmilaridade  -> Nome da função de similaridade que deverá ser utilizada ('euclidiana' ou 'cosseno').

Saída:

nota           -> Rating previsto para o par x = (id_usuario,id_item).

=#
function knn (x,dados,k,distancia::Function)
  # Testa se a nota já é conhecida
  if dados[x[1],x[2]] != 0
    return dados[x[1],x[2]]
  end

  print("x = ")
  println(x)

  # Encontra os índices dos itens que foram avaliados pelo usuário id_usuario
  ind_itens = find(x->x!=0,dados[:,x[2]])

  # Testa se k é maior do que a quantidade de itens encontrados
  if k > length(ind_itens)
    k = length(ind_itens)
    print("Novo k = ")
    println(k)
  end

  # Calcula a distância entre o item id_item e todos os itens com índice ind_item
  distancias = zeros(1,length(ind_itens))
  for i=1:length(ind_itens)
    distancias[i] = distancia(dados[x[1],:],dados[ind_itens[i],:])
  end

  # Criando uma coleção de tuplas com as distâncias e o índice do elemento ordenado pela distância
  dicionario = sort(collect(zip(distancias,ind_itens)))

  # Calculando a soma dos rating e a quantidade de vizinhos encontrados
  rating = 0
  qtd_vizinhos = 0
  for i = 1:k
    if(dicionario[i][1] != Inf)
      rating += dados[dicionario[i][2],x[2]]
      print("Rating do vizinho ")
      print(i)
      print(" - ")
      println(dados[dicionario[i][2],x[2]])
      print("Distancia do vizinho ")
      print(i)
      print(" - ")
      println(dicionario[i][1])
      qtd_vizinhos += 1
    end
  end

  # Retornando o rating previsto
  print("Soma dos ratings = ")
  print(rating)
  print(" e quantidade de vizinhos = ")
  println(qtd_vizinhos)
  return rating/qtd_vizinhos
end
