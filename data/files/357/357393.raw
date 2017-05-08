#=Descrição

Imprimir na saída padrão uma mesa de xadrez de tamanho N,M onde N é o número de colunas e M é o número de linhas.
Você tem que imprimir 0 quando na mesa for branco e 1 quando  não for.
Índice(0,0) é branco e está na céluado do topo no lado esquesdo na saída produzida.

Entrada de Exemplo:
7,4

Saída de Exemplo:
0101010
1010101
0101010
1010101
=#

include("..\\src\\xadrez.jl")

module XadrezTeste
  include("error_handler_pt_br.jl")
end

using Base.Test

import Xadrez

Test.with_handler(custom_handler) do
  @test xadrez(0,0) == ""
end
