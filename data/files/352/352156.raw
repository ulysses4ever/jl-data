include("Instancia.jl")

function aptidao(populacao::Array)
  cost = 0.;
  prize = 0.;
  custos = Float32[];
  premios = Float32[];

  for cromossomo in populacao
    prize = sum(prizes[cromossomo]);

    if size(setdiff([1:quantNos], cromossomo))[1] > 0
      cost = sum(penalties[setdiff([1:quantNos], cromossomo)]);
    end

    for i = 1:(size(cromossomo)[1]-1)
      cost += matrix[cromossomo[i], cromossomo[i+1]];
    end

    push!(premios, prize);
    push!(custos, cost);
  end
  percents = custos .* 100.0 ./ sum(custos);
  return premios, custos, percents;
end

function mutacao(populacao::Array)
  i = rand(1:size(populacao)[1]);
  x = rand(2:size(populacao[i])[1]);
  y = rand(2:size(populacao[i])[1]);
  while y == x
    y = rand(2:size(populacao[i])[1]);
  end
  aux = populacao[i][x];
  populacao[i][x] = populacao[i][y];
  populacao[i][y] = aux;

  return populacao;
end

function cruzamento(populacao::Array)
  premios, custos, percents = aptidao(populacao);

  index = sortperm(percents);
  percents = percents[index];
  premios = premios[index];
  custos = custos[index];
  populacao = populacao[index];

  individuo1 = roleta(populacao, percents);
  while sum(prizes[populacao[individuo1]]) < limPrizes
    individuo1 = roleta(populacao, percents);
  end

  individuo2 = roleta(populacao, percents);
  tam = min(size(populacao[individuo1])[1], size(populacao[individuo2])[1])
  x = rand(2:tam);
  while (sum(prizes[populacao[individuo2]]) < limPrizes) || (individuo1 == individuo2) ||
      (populacao[individuo1][1:x] == populacao[individuo2][1:x]) || (populacao[individuo2][x+1:end] == populacao[individuo1][x+1:end]) ||
      (!isempty(intersect(populacao[individuo1][1:x], populacao[individuo2][x+1:end])))

    individuo2 = roleta(populacao, percents)
    tam = min(size(populacao[individuo1])[1], size(populacao[individuo2])[1])
    x = rand(2:tam);
  end

  filho1 = union(populacao[individuo1][1:x], populacao[individuo2][x+1:end]);
  filho2 = union(populacao[individuo2][1:x], populacao[individuo1][x+1:end]);

  pop = populacao[:,:];
  pop[individuo1] = filho1;
  pop[individuo2] = filho2;

  p, c, f = aptidao(pop);
  if sum(c) < sum(custos)
    return pop;
  end

  return populacao;
end

function roleta(populacao::Array, percents::Array)
  x = rand(1:100);
  soma = 0.;

  for i = 1:size(percents)[1]
    soma += percents[i];

    if round(soma) >= x
      return i;
    end
  end
  return size(percents)[1]
end


include("Instancia.jl")
prizes, penalties, matrix = Instancia("/home/jones/Documentos/TEEO/instâncias/v100a.txt");

quantNos = size(prizes)[1];
tamPopulacao = 100;
limPrizes = 300;
maxIter = 1000;
populacao = Array(Vector{Int}, tamPopulacao);

for i in 1:tamPopulacao
  populacao[i] = [];
  populacao[i] = insert!(shuffle([2:quantNos]), 1, 1);
  j = 2
  while j < size(populacao[i])[1]
    if randbool()
      splice!(populacao[i], j);
      j -= 1;
    end
    j += 1;
  end
end

for iter = 1:maxIter
  populacao = cruzamento(populacao);

  if rand() < 0.05
    populacao = mutacao(populacao)
  end

  p, c, f = aptidao(populacao);
  println(iter, " - ", minimum(c), " ", sum(p[indmin(c)]))
end
