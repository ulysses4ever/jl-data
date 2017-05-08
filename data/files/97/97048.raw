using FactCheck

import CDLasso


##############################################
#
#  Groups Lasso
#
##############################################


facts("Group Active set") do

  numGroups = 3
  groupToIndex = Array(typeof(1:2), numGroups)
  for i=1:numGroups
    groupToIndex[i] = UnitRange((i-1)*2+1, i*2)
  end

  as = CDLasso.GroupActiveSet(zeros(6), groupToIndex)
  @fact as.numActive => 0

  x = [1., 0., 0., 0., 1., 2.]
  as = CDLasso.GroupActiveSet(x, groupToIndex)
  @fact as.numActive => 2

  @fact CDLasso._group_norm(x, as, 3) => roughly(sqrt(5))
  @fact CDLasso._group_norm(x, as, 2) => roughly(0.)

  CDLasso._fill_zero!(x, as, 1)
  @fact x[1:2] => zeros(2)

  A = eye(6)
  b = [1., 0., 0., 0., 1., 2.]
  x = zeros(6)
  as = CDLasso.GroupActiveSet(x, groupToIndex)
  λ = [0.9, 0., 3]

  CDLasso._add_violator!(as, x, A, b, λ)
  @fact as.numActive => 1
  @fact as.groups[1] => 1

  A = eye(6)
  b = [1., 0., 0., 0., 1., 2.]
  x = zeros(6)
  as = CDLasso.GroupActiveSet(x, groupToIndex)
  λ = [1.9, 0., 1.]

  CDLasso._add_violator!(as, x, A, b, λ)
  @fact as.numActive => 1
  @fact as.groups[1] => 3
end

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
