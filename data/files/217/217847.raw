#module Testowanie
  using Base.Test
  using Transformator

  custom_handler(r::Test.Success) = println("Test zakończony powodzeniem dla: $(r.expr)")
  custom_handler(r::Test.Failure) = error("Test zakończony niepowodzeniem dla: $(r.expr)")
  custom_handler(r::Test.Error) = rethrow(r)

  @test_approx_eq przekladnia(200,100) 2

  Test.with_handler(custom_handler) do
         @test przekladnia(200,100) == 2
         @test 1 == 1
  end

  Test.with_handler(custom_handler) do
         @test 12 == 123
         @test 2 == 2
  end


#end
