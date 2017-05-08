facts("Float split") do
  context("Float32") do
    x, y = fsplit(2.3f-2)
    @fact 2.3f-2 => x + y
    @fact abs(x) => greater_than(abs(y))
    # TODO: non overlapping
  end

  context("Float64") do
    x, y = fsplit(-3.1)
    @fact -3.1 => x + y
    @fact abs(x) => greater_than(abs(y))
    # TODO: non overlapping
  end
end

facts("Error-free multiply") do
  x, y = err_mul(2.1, .3)
  @fact BigFloat(x+y) => BigFloat(2.1*.3)
end

facts("Fast error-free multiply") do
  @fact err_fast_mul(2.1, .3) => err_mul(2.1, .3)
end
