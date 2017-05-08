include("Instancia.jl")

function aptidao(populacao::Array)
  cost = 0.;
  prize = 0.;
  custos = Float32[];
  premios = Float32[];
  percents = Float32[];
  minCusto = Inf;
  global gMinCusto;

  for cromossomo in populacao
    prize = sum(prizes[cromossomo]);

    if size(setdiff([1:quantNos], cromossomo))[1] > 0
      cost = sum(penalties[setdiff([1:quantNos], cromossomo)]);
    end

    for i = 1:(size(cromossomo)[1]-1)
      cost += matrix[cromossomo[i], cromossomo[i+1]];
    end

    if prize > limPrizes
      if gMinCusto > cost
        gMinCusto = cost;
      end
      if minCusto > cost
        minCusto = cost;
      end
    end

    push!(premios, prize);
    push!(custos, cost);
    push!(percents, prize < limPrizes ? 0 : 1 / cost);
  end
  percents = percents ./ sum(1 ./ custos);
  percents = percents .* 100;
  return premios, custos, percents;
end

function mutacao(filhos::Array)
  global quantFilhos;
  i = rand(1:quantFilhos);
  no = rand(1:20);

  if no in filhos[i]
    deleteat!(filhos[i], findfirst(filhos[i], no))
  else
    insert!(filhos[i], rand(1:size(filhos[i])[1]), no)
  end

  return filhos;
end

function cruzamento(populacao::Array)
  global quantFilhos;
  premios, custos, percents = aptidao(populacao);
  index = sortperm(percents);
  percents = percents[index];
  populacao = populacao[index];

  for i = 1:quantCruzamento

    individuo1 = roleta(percents);

    individuo2 = roleta(percents);
    tam = min(size(populacao[individuo1])[1], size(populacao[individuo2])[1])
    x = rand(2:(tam-1));
    while ((individuo1 == individuo2) || (populacao[individuo1][1:x] == populacao[individuo2][1:x]) ||
          (populacao[individuo2][x+1:end] == populacao[individuo1][x+1:end]) ||
          (!isempty(intersect(populacao[individuo1][1:x], populacao[individuo2][x+1:end]))))

      individuo2 = roleta(percents)
      tam = min(size(populacao[individuo1])[1], size(populacao[individuo2])[1])
      x = rand(2:(tam-1));
    end

    filhos[quantFilhos += 1] = union(populacao[individuo1][1:x], populacao[individuo2][x+1:end]);
    filhos[quantFilhos += 1] = union(populacao[individuo2][1:x], populacao[individuo1][x+1:end]);
  end

  return filhos;
end

function roleta(percents::Array)
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

function substituicao(populacao, filhos)
  global quantFilhos
  populacao[1:quantFilhos] = filhos[1:quantFilhos]
  quantFilhos = 0;

  return populacao;
end

prizes, penalties, matrix = Instancia("/home/jones/Documentos/TEEO/instâncias/problem_40_100_100_1000.pctsp");

quantNos = size(prizes)[1];
tamPopulacao = 100;
limPrizes = 0.2 * sum(prizes);
maxIter = 2000;
quantCruzamento = tamPopulacao * 0.2;
quantFilhos = 0;
gMinCusto = Inf;
populacao = Array(Vector{Int}, tamPopulacao);
filhos = Array(Vector{Int}, tamPopulacao);

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

  filhos = cruzamento(populacao);

  if rand() < 0.1
    filhos = mutacao(filhos);
  end

  populacao = substituicao(populacao, filhos);
  println(iter);
end

p, c, f = aptidao(populacao)
println(gMinCusto)
