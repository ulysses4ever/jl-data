#=
Campo Minado

Calcular o número de minas das células
em volta para todas as células do campo.

Fomato de entrada:

  - Colunas são separadas por espaços
  - Linhas são separadas por("\n")
  - "X" marca uma mina,
    "O"(ó maiúsculo) marca um campo livre de minas

Formato de saída:

  - Campo com "X" são deixados como eles são.
  - Para cada campo contendo "O",
    deve-se calcular o número de minas em volta daquele campo.

    Calculate the number of mines in the surrounding cells for every cell in the field.

Entrada de Exemplo:
O O O O X O O O O O
X X O O O O O O X O
O O O O O O O O O O
O O O O O O O O O O
O O O O O X O O O O

Saída de Exemplo:
2 2 1 1 X 1 0 1 1 1
X X 1 1 1 1 0 1 X 1
2 2 1 0 0 0 0 1 1 1
0 0 0 0 1 1 1 0 0 0
0 0 0 0 1 X 1 0 0 0

=#
include("..\\src\\campo_minado.jl")
include("error_handler_pt_br.jl")

module CampoMinadoTeste
end

using Base.Test

import CampoMinado

Test.with_handler(custom_handler) do
  @test ehValido("O\n") == false
  @test ehValido("X\n") == false
  @test ehValido("O \n") == true
  @test ehValido("X \n") == true
  @test ehValido("")  == true
  @test ehValido("O \nX \n") == true
  @test ehValido("O O O\nX X\n") == false
  @test ehValido("zcakjsfajbsclkak") == false
  @test ehValido("O OOXXXX") == false

  @test paraArray("O X \n") == Vector[Char['O','X']];
  @test paraArray("O \nX \n") == Vector[Char['O'],Char['X']];

  @test_throws ArgumentError campoMinado("asndnasdasddkj")
  @test campoMinado("O \n") == "0 \n"
  @test campoMinado("O X \n") == "1 X \n"
end
