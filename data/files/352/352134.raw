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

function FO(s)
  cost = 0.;
  prize = 0.;
  custos = Float32[];
  premios = Float32[];
  percents = Float32[];
  global gMinCusto;

  prize = sum(prizes[s]);

  if size(setdiff([1:quantNos], s))[1] > 0
    cost = sum(penalties[setdiff([1:quantNos], s)]);
  end

  for i = 1:(size(s)[1]-1)
    cost += matrix[s[i], s[i+1]];
  end

  if prize > limPrizes
    if gMinCusto > cost
      gMinCusto = cost;
    end
  end

  return prize, cost;
end

function BuscaTabu(BTmax, maxIter, s)
  sAtual = s[:];
  iter = 0;
  melhorIter = 0;
  Tabu = Array((Int, Int), 0);
  melhorS =[];
  minFO = Inf;
  mov = tuple();

  while iter - melhorIter <= BTmax && iter < maxIter
    s = sAtual[:];
    vizinhos = setdiff([1:quantNos], s);
    costAtual = FO(sAtual)[2];

    for i in 2:size(s)[1]

      deleteat!(s, i);
      prize, cost = FO(s);
      if cost < minFO && prize > limPrizes
        minFO = cost;
        melhorS = s[:];
      end

      s = sAtual[:];
      for v in vizinhos

        if !(tuple(s[i-1], v) in Tabu)
          s[i] = v;
          prize, cost = FO(s);
          if cost < minFO && prize > limPrizes
            mov = tuple(v, s[i-1]);
            minFO = cost;
            melhorS = s[:];
          end

        end

        s = sAtual[:];
        if !(tuple(s[i], v) in Tabu)
          insert!(s, i, v);
          prize, cost = FO(s);
          if cost < minFO && prize > limPrizes
            mov = tuple(v, s[i]);
            minFO = cost;
            melhorS = s[:];
          end

        end
        s = sAtual[:];
      end

    end

    push!(Tabu, mov);
    prize, cost = FO(melhorS);
    if prize > limPrizes && cost < costAtual
      sAtual = melhorS[:];
      melhorIter = iter;
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
BTmax = 10;

s = inicial(quantNos);

solucao = BuscaTabu(BTmax, maxIter, s)

println(s, " - ", gMinCusto);
