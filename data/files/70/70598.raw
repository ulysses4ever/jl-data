module Tests

using NumericSuffixes
using Base.Test

@suffix I8 Int8
@suffix t16 x -> trunc(Int16, x)

@test 0I8 == Int8(0)
@test 8t16 == trunc(Int16, 8)

for (k, v) in NumericSuffixes.suffixes
    suffix = getfield(NumericSuffixes, k)
    totype = getfield(Base, v)
    @test 5suffix == totype(5)
end

@test_throws ErrorException NumericSuffixes.gentype(:(x + y))
@test_throws ErrorException NumericSuffixes.genfunc(:x, :(x + y))
@test_throws ErrorException NumericSuffixes.genfunc(:x, :((x, y) -> ()))
@test_throws ErrorException NumericSuffixes.genfunc(:x, 0)

end
