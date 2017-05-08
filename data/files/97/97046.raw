using FactCheck

import CDLasso


##############################################
#
#  Lasso
#
##############################################

facts("Orthogonal design") do
  b = [1.0, 2.0, 3.0]
  A = eye(3)

  λ = 1.5
  x = zeros(3)
  CDLasso.lasso!(x, A, b, λ)
  @fact x => roughly([0, -0.5, -1.5])

  λ = [0.9, 2.1, 3.1]
  x = zeros(3)
  CDLasso.lasso!(x, A, b, λ)
  @fact x => roughly([-0.1, 0, 0])
end

facts("Lasso shrink to zero") do
  n = 100
  p = 10

  X = randn(n, p)
  Y = X * ones(p) + 0.1 * randn(n)
  A = X' * X / n
  b = -X' * Y / n

  beta = ones(p)
  λ = maximum(abs(b)) + 0.1
  CDLasso.lasso!(beta, A, b, λ)
  @fact beta => roughly(zeros(p))
end


##############################################
#
#  Other
#
##############################################

facts("SoftThreshold") do

  @fact CDLasso.shrink(5., 3.) => 2.
  @fact CDLasso.shrink(-2., 3.) => 0.
  @fact CDLasso.shrink(-1.,1.) => 0.
  @fact CDLasso.shrink(-1.,0.9) => roughly(-0.1, 1e-5)

end

FactCheck.exitstatus()
