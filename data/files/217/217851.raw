using Base.Test
using Transformator

const e1 = 200 #siły elektromotoryczne
const e2 = 100 #
const R2 = 200 # w omach
const X2 = 300 # w omach
const i1 = 5
const i2 = 10
const rfe = 50

 c = 1 / rfe

custom_handler(r::Test.Success) = println("Test zakończony powodzeniem dla: $(r.expr)")
custom_handler(r::Test.Failure) = error("Test zakończony niepowodzeniem dla: $(r.expr)")
custom_handler(r::Test.Error) = rethrow(r)

@test_approx_eq x = przekladnia(200,100) 2

@assert (R2_prim = rez_2_prim(x, R2)) == 800

@test reak_2_prim(x, X2) == 1200

Test.with_handler(custom_handler) do
  @test straty_uzwojen(i1,i2, R2, R2_prim) == 85000

  sprawnosc =  moc_pierwotna(i1, e1) / moc_wtorna(i2, e2)
  oczekiwana_sprawnosc = 1

  @test sprawnosc == oczekiwana_sprawnosc

  @test_approx_eq_eps straty_w_rdzeniu(e1, c) 7929.99 10e-2
end
