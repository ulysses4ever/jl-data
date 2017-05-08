facts("Error-free add") do
  x, y = err_add(1.0, 2.0)
  @fact x => 1.0 + 2.0
  @fact y => 0.0

  x, y = err_add(1.0, 2e-50)
  @fact x => 1.0
  @fact y => 2e-50

  x, y = err_add(2e-50, 1.0)
  @fact x => 1.0
  @fact y => 2e-50
end

facts("Fast error-free add") do
  x, y = err_fast_add(2.0, 1.0)
  @fact x => 2.0 + 1.0
  @fact y => 0.0

  x, y = err_fast_add(1.0, 2e-50)
  @fact x => 1.0
  @fact y => 2e-50
end
