import ..Units; u = Units
using Base.Test

custom_handler(r::Test.Success) = print('.')
custom_handler(r::Test.Failure) = println("\nError on custom handler: $(r.expr)")
custom_handler(r::Test.Error) = rethrow(r)

Test.with_handler(custom_handler) do
    q1 = u.Quantity(1, u.Meter)
    q2 = 1 * u.Meter
    @test isa(q1, u.Quantity)
    @test isa(q2, u.Quantity)
    @test isequal(q1, q2)
    @test q1.mag == q2.mag == 1

    q1 = 1 * u.Meter
    q2 = 1 * u.Second
    @test_throws u.UnitError q1 + q2
end
