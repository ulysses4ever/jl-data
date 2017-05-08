# ==========================================================================
# @desc Calcula a aptidão
# ==========================================================================
function aptidao(populacao)
    # Calcular o f(x) de cada entrada
    f = size(populacao)[1]
    for i=1:size(populacao)[1]
       f[i] = dec(populacao[i])^2;
    end

    # Calcular a aptidao
    pi = (f / sum(f)) * 100;

    # Retorno da funcao
    return pi;
end

# ==========================================================================
# @desc Fazer o cruzamento com ponte de corte
#
# @param pai1           - Pai em formato decimal
# @param pai2           - Pai em formato decimal
# @param nFilhos        - Numeros de filhos a serem gerados [1 ou 2]
# @param tamCromossomo  - Numero de bits maximo de um cromossomo
# @param taxaCross      - Taxa de crossover
# ==========================================================================

function crossover(pai1,pai2, nFilhos, tamCromossomo, taxaCross)

    # Transformar em binario
  for i = 1:size(pai1)
    pai1[i] = bin(pai1[i])
    pai2[i] = bin(pai2[2])
  end

    # Aplicar o crossover?
    crossover = roleta([taxaCross 100-taxaCross], 1);

    if crossover(1,1) == 1

        # Cortar o cromossomo em algum lugar
        corte = floor(tamCromossomo * rand(1,1))+1;

        # Primeiro Filho
        filhos[1, 1:corte] = pai1[1, 1:corte];
        filhos[1, corte+1:tamCromossomo] = pai2[1, corte+1:tamCromossomo];

        if nFilhos == 2
            # Segundo Filho
            filhos[2, 1:corte] = pai2[1, 1:corte];
            filhos[2, corte+1:tamCromossomo] = pai1[1, corte+1:tamCromossomo];
        end

    # Nao aconteceu o crossover, entao os filhos serao iguais aos pais
    else
        filhos[1,:] = pai1[1,:];
        filhos[2,:] = pai2[1,:];
    end

    # Transformar de binario para decimal
    filhos = dec(filhos);
    # Retorno da funcao
    return filhos;
end

# ==========================================================================
# @desc Fazer a mutacao de algum dos filhos
#
# @param filhos         - Filhos gerados em decimal, vetor LINHA
# @param tamCromossomo  - Numero de bits maximo de um cromossomo
# @param taxaMutacao    - Taxa de mutacao
# ==========================================================================
function mutacao(filhos, tamCromossomo, taxaMutacao)

    mutacao = roleta([taxaMutacao 100-taxaMutacao], 1);
    (nFilhos, nJ) = size(filhos);
    filhos = dec2bin(filhos,tamCromossomo);

    #% Aplicar a mutacao?
    if mutacao(1,1) == 1
        # Escolher um filho para ser mutado
        mutante = floor(nFilhos * rand(1,1))+1;
        nBit = floor(tamCromossomo * rand(1,1))+1;
        bitAtual = filhos[mutante, nBit];

        # Fazer a mutacao em apenas um bit
        if bitAtual == dec2bin(1)
            bitMutante = dec2bin(0);
        else
            bitMutante = dec2bin(1);
        end

        # Alterando um bit no filho escolhido
        filhos[mutante, nBit] = bitMutante;
    end

    # Transformar de binario para decimal
    filhos = dec(filhos);

    # Retorno da funcao
    return filhos;
end

# =========================================================================
#
# @desc Criar uma roleta viciada, para sorteio de numeros
#	As areas que sao passadas como entrada define a probabilidade
#	de uma certa area ser sorteada.
#
# @param area       - Vetor coluna com o percentual de cada area
#                     ex.: [20 30 50]
# @param nJogadas   - numero de jogadas a serem simuladas
# @param result     - vetor com o numero de ocorrencias de sorteio em cada
#                     area
#
# Paulo Eduardo Camboim de Brito
# 14/10/2010
# =========================================================================

function roleta(area, nJogadas)

  # if ( (sum(area) > 100) || (sum(area)<100) )
  #     disp('O total da soma das entradas deve ser 100')
  #     erro = 1;
  #     result = erro;
  #     return
  # end

  # Intervalo de cada area
  (lin, nArea) = size(area);
  mini = zeros(lin,nArea);
  maxi = zeros(lin,nArea);

  # Frequencia dos resultados em cada area
  y = zeros(lin,nArea);

  for i=1:nArea
      if(i == 1)
          mini[i] = 1;
          maxi[i] = area[i];
      else
          mini[i] = maxi[i-1] +1;
          maxi[i] = mini[i]+area[i] -1;
      end
  end

  # Deixar apenas a parte inteira
  mini = ceil(mini);
  maxi = ceil(maxi);

  # Numero de jogadas a realizar
  for i=1:nJogadas
      rodada = ceil(rand() * 100.0);

      # procurar no vetor de minimos
      for k=1:nArea
          if ( (rodada >= mini[k]) && (rodada <= maxi[k]))
              y[k] = y[k]+1;
          end
      end

  end

  # Mostrando o resultado
  return y;
end

# ==========================================================================
# @desc Faz a selecao do individuo mais apto
#
# @param individuos - Individuos de uma populacao em um vetor LINHA
# @param pi         - Probabilidadde de selecao proporcional a aptidao
# @obs              - Caso usar pi=0 indicia o uso de selecao por torneio
# ==========================================================================
function selecao(populacao, probSelecao)

    # Selecao por Torneio
    if pi == 0

    # Selecao por Roleta
    else
        resp = roleta(probSelecao',1);
        selecionado = find(resp);

    end

    # Retorna o resultado
    return populacao[selecionado,1];

end

# =========================================================================
# @desc Algoritmo genetico para encontrar um maximo de uma funcao
#
#
# floor(N * rand(4,1))+1 = rand de 1 até N
# =========================================================================


# =====================================================================
# Configuracoes iniciais
tamCromossomo = 5;

taxaCross   = 80;
taxaMutacao = 1;

iteracaoAtual = 1;
iteracaoTotal = 100;
tamPopulacao = 10;
# PASSO 1 - GERAR A POPULACAO INICIAL
# =====================================================================
# Inicializar populacao e transformar em binario (cromossomo com 5 bits)
populacao = {}
for i = 1:tamPopulacao
  push!(populacao, bin(int(tamCromossomo*10*rand()), tamCromossomo));
end

# PASSO 2 - AVALIAR CADA INDIVIDUO DA POPULACAO
# =====================================================================
# Avaliar populacao
probSelecao = aptidao(populacao);
println(probSelecao)
# PASSO 3 - ENQUANTO O CRITERIO DE PARADA NAO FOR SATISFEITO FAZER
# =====================================================================
#while iteracaoAtual < iteracaoTotal

  # PASSO 3.1 - SELECIONAR OS INDIVIDUOS MAIS APTOS
  # =================================================================

  # Gerar o numero de filhos igual a populacao anterior
  k = 1;
  #while k <= iPopulacao
    # Selecionar o casal
    pai1 = selecao(populacao,probSelecao);
    pai2 = selecao(populacao,probSelecao);

    # PASSO 3.1 - CROSSOVER
    # =============================================================
    nFilhos = 2;
    filhos[k:k+1,:] = crossover(pai1, pai2, nFilhos, tamCromossomo, taxaCross);

    # Contar dois, pois cada casal tem dois filhos
    k = k+2;
  #end

  # PASSO 3.1 - MUTACAO
  # =================================================================

  filhos = mutacao(filhos, tamCromossomo, taxaMutacao);

  # FIM DE PASSO 3.1
  # =================================================================

  # ELITISMO
  # =================================================================
  elitePopulacao  = indmax(populacao);
  eliteFilhos     = indmax(filhos);
  if elitePopulacao > eliteFilhos
    iMenor   = minimum(filhos);
    filhos[iMenor, 1]  = elitePopulacao;
  end

  # FIM DE ELITISMO
  # =================================================================

  # A nova populacao eh igual aos filhos gerados
  populacao = filhos;

  # Incrementar o numero de iteracao ateh chegar ao total
  iteracaoAtual = iteracaoAtual + 1;

#end
println(filhos);

bin([10, 2, 5])
