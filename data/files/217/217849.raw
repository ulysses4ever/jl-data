using Base.Test
using Transformator

const e1 = 200 #siły elektromotoryczne
const e2 = 100 #
const R2 = 200 # w omach
const X2 = 300 # w omach
const i1 = 5
const i2 = 10

custom_handler(r::Test.Success) = println("Test zakończony powodzeniem dla: $(r.expr)")
custom_handler(r::Test.Failure) = error("Test zakończony niepowodzeniem dla: $(r.expr)")
custom_handler(r::Test.Error) = rethrow(r)

@test_approx_eq x = przekladnia(200,100) 2

@assert rez_2_prim(x, R2) == 800

Test.with_handler(custom_handler) do
  @test przekladnia(200,100) == 2
  @test 1 == 1
end
