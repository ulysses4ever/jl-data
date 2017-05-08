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


  @test_throws ArgumentError campoMinado("asndnasdasddkj")
  @test campoMinado("O \n") == "O \n"
end
