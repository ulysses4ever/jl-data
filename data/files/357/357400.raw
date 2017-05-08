include("..\\src\\introducao.jl")

module IntroducaoTeste
  include("error_handler_pt_br.jl")
end

using Base.Test

import Introducao

Test.with_handler(custom_handler) do
  @test soma(1,2) == 2
end
