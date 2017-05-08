include("Instancia.jl")

function inicial(quantNos)
  s = Int16[];
  s = insert!(shuffle([2:quantNos]), 1, 1);
  j = 2
  while j < size(s)[1]
    if randbool()
      splice!(s, j);
      j -= 1;
    end
    j += 1;
  end

  while(FO(s)[1] < limPrizes)
    s = Int16[];
    s = insert!(shuffle([2:quantNos]), 1, 1);
    j = 2
    while j < size(s)[1]
      if randbool()
        splice!(s, j);
        j -= 1;
      end
      j += 1;
    end
  end

  return s;
end

function buscaLocal(s, Tabu)
  sAtual = s[:]
  minFO = Inf;
  vizinhos = setdiff([1:quantNos], s);
  mov = tuple();
  melhorS = []

  for i in 2:size(s)[1]
    for v in vizinhos

      if !(tuple(s[i-1], v) in Tabu)
        s[i] = v;
        prize, cost = FO(s);
        if cost + max(0, limPrizes-prize) < minFO
          mov = tuple(v, s[i-1]);
          minFO = cost + max(0, limPrizes-prize)
          melhorS = s[:];
        end
      end

      s = sAtual[:];
      if !(tuple(s[i], v) in Tabu)
        insert!(s, i, v);
        prize, cost = FO(s);
        if cost + max(0, limPrizes-prize) < minFO
          mov = tuple(v, s[i]);
          minFO = cost + max(0, limPrizes-prize)
          melhorS = s[:];
        end
      end

      s = sAtual[:];

    end

    deleteat!(s, i);
    prize, cost = FO(s);
    if cost + max(0, limPrizes-prize) < minFO
      minFO = cost + max(0, limPrizes-prize)
      melhorS = s[:];
    end
    s = sAtual[:]

  end

  return melhorS, mov;
end

function FO(s)
  cost = 0.;
  prize = 0.;
  custos = Float32[];
  premios = Float32[];
  percents = Float32[];

  prize = sum(prizes[s]);

  if size(setdiff([1:quantNos], s))[1] > 0
    cost = sum(penalties[setdiff([1:quantNos], s)]);
  end

  for i = 1:(size(s)[1]-1)
    cost += matrix[s[i], s[i+1]];
  end

  return prize, cost;
end

function BuscaTabu(BTmax, maxIter, s)
  global gMinCusto

  sAtual = s[:];
  iter = 0;
  melhorIter = 0;
  Tabu = Array((Int, Int), 0);
  melhorS = [];
  minFO = Inf;

  while abs(iter - melhorIter) < BTmax && iter < maxIter
    s = sAtual[:];

    melhorS, mov = buscaLocal(s, Tabu);

    prize, cost = FO(melhorS);
    if cost < gMinCusto && limPrizes < prize
      sAtual = melhorS[:];
      melhorIter = iter;
      gMinCusto = cost;
    end

    if abs(iter - melhorIter) > 0
      push!(Tabu, mov);
      sAtual = melhorS[:];
    end

    iter += 1;
    println(iter)
  end

  return sAtual;
end

prizes, penalties, matrix = Instancia("/home/jones/Documentos/TEEO/instâncias/problem_40_100_100_1000.pctsp")

quantNos = size(prizes)[1];
limPrizes = 0.2 * sum(prizes);
maxIter = 2000;
gMinCusto = Inf;
BTmax = 50;

s = inicial(quantNos);

solucao = BuscaTabu(BTmax, maxIter, s)
prize, cost = FO(solucao)
println(gMinCusto, cost)
