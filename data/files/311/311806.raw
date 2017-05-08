facts("Fused multiply-add") do
  context("Float32") do
    @fact fma(9.982642f2, 1.0018032f-3, -1f0) => 6.4295644f-5
    # The correct result is 6.432965f-5
  end

  context("Float64") do
    @fact fma(9.9826421385793060e2, 1.0018032458425164e-3, -1e0) => 6.432965130279311e-5
    # The correct results is 6.432965130281577e-5
  end
end
