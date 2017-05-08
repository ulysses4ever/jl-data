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

  as = CDLasso.GroupLassoData(zeros(6), groupToIndex)
  @fact as.numActive --> 0

  x = [1., 0., 0., 0., 1., 2.]
  as = CDLasso.GroupLassoData(x, groupToIndex)
  @fact as.numActive --> 2

  @fact CDLasso._group_norm(x, as, 3) --> roughly(sqrt(5))
  @fact CDLasso._group_norm(x, as, 2) --> roughly(0.)

  CDLasso._fill_zero!(x, as, 1)
  @fact x[1:2] --> zeros(2)

  A = eye(6)
  b = [1., 0., 0., 0., 1., 2.]
  x = zeros(6)
  as = CDLasso.GroupLassoData(x, groupToIndex)
  λ = [0.9, 0., 3]

  CDLasso._add_violator!(as, x, A, b, λ)
  @fact as.numActive --> 1
  @fact as.groups[1] --> 1

  A = eye(6)
  b = [1., 0., 0., 0., 1., 2.]
  x = zeros(6)
  as = CDLasso.GroupLassoData(x, groupToIndex)
  λ = [1.9, 0., 1.]

  CDLasso._add_violator!(as, x, A, b, λ)
  @fact as.numActive --> 1
  @fact as.groups[1] --> 3
end

facts("Minimize one group") do
  numGroups = 1
  groupToIndex = Array(typeof(1:2), numGroups)
  for i=1:numGroups
    groupToIndex[i] = UnitRange((i-1)*3+1, i*3)
  end

  b = [1., 1., 1.]
  A = eye(3)
  Asvd = svdfact(A)
  λ = 1.
  x = zeros(3)

  as = CDLasso.GroupLassoData(x, groupToIndex)
  CDLasso._add_violator!(as, x, A, b, fill(λ, 3))
  CDLasso._min_one_group!(x, Asvd, b, as, 1, λ)

  @fact A*x+b+(λ/norm(x))*x --> roughly(zeros(3); atol=1e-5)

  ##

  A = randn(100, 3)
  A = A'A/100
  Asvd = svdfact(A)
  b = [1., 1., 1.]
  λ = 1.
  x = zeros(3)

  as = CDLasso.GroupLassoData(x, groupToIndex)
  CDLasso._add_violator!(as, x, A, b, fill(λ, 3))
  CDLasso._min_one_group!(x, Asvd, b, as, 1, λ)

  @fact A*x+b+(λ/norm(x))*x --> roughly(zeros(3); atol=1e-5)

  ##
  numGroups = 1
  groupToIndex = Array(typeof(1:2), numGroups)
  for i=1:numGroups
    groupToIndex[i] = UnitRange((i-1)*10+1, i*10)
  end

  A = randn(100, 10)
  A = A'A/100
  Asvd = svdfact(A)
  b = randn(10)
  λ = 0.5
  x = zeros(10)

  as = CDLasso.GroupLassoData(x, groupToIndex)
  CDLasso._add_violator!(as, x, A, b, fill(λ, 10))
  CDLasso._min_one_group!(x, Asvd, b, as, 1, λ)

  @fact A*x+b+(λ/norm(x))*x --> roughly(zeros(10); atol=1e-5)

end

facts("Minimize active set") do
  numGroups = 2
  groupToIndex = Array(typeof(1:2), numGroups)
  for i=1:numGroups
    groupToIndex[i] = UnitRange((i-1)*3+1, i*3)
  end

  b = ones(6)
  A = eye(6)
  λ = [1., 0.5]

  x = ones(6)
  as = CDLasso.GroupLassoData(x, groupToIndex)
  CDLasso._add_violator!(as, x, A, b, λ)

  CDLasso._group_lasso!(x, A, b, λ, as)

  for i=1:numGroups
    @fact A[groupToIndex[i], :]*x + b[groupToIndex[i]] + (λ[i]/norm(x[groupToIndex[i]]))*x[groupToIndex[i]]  --> roughly(zeros(length(groupToIndex[i])); atol=1e-5)
  end


  ##

  numGroups = 2
  groupToIndex = Array(typeof(1:2), numGroups)
  for i=1:numGroups
    groupToIndex[i] = UnitRange((i-1)*3+1, i*3)
  end

  b = randn(6)
  A = randn(100, 6)
  A = A'A/100
  λ = [1., 0.5]

  x = ones(6)
  as = CDLasso.GroupLassoData(x, groupToIndex)
  CDLasso._add_violator!(as, x, A, b, λ)

  CDLasso._group_lasso!(x, A, b, λ, as)

  for i=1:numGroups
    @fact A[groupToIndex[i], :]*x + b[groupToIndex[i]] + (λ[i]/norm(x[groupToIndex[i]]))*x[groupToIndex[i]]  --> roughly(zeros(length(groupToIndex[i])); atol=1e-5)
  end

  ##

  numGroups = 2
  groupToIndex = Array(typeof(1:2), numGroups)
  for i=1:numGroups
    groupToIndex[i] = UnitRange((i-1)*3+1, i*3)
  end

  b = randn(6)
  A = randn(100, 6)
  A = A'A/100
  λ = [100., 0.1]

  x = ones(6)
  as = CDLasso.GroupLassoData(x, groupToIndex)
  CDLasso._add_violator!(as, x, A, b, λ)

  CDLasso._group_lasso!(x, A, b, λ, as)

  i = 1
  @fact norm(A[groupToIndex[i], :]*x + b[groupToIndex[i]]) <= λ[i]  --> true
  i = 2
  @fact A[groupToIndex[i], :]*x + b[groupToIndex[i]] + (λ[i]/norm(x[groupToIndex[i]]))*x[groupToIndex[i]]  --> roughly(zeros(length(groupToIndex[i])); atol=1e-4)
end


facts("Group Lasso") do
  numGroups = 200
  groupToIndex = Array(typeof(1:2), numGroups)
  for i=1:numGroups
    groupToIndex[i] = UnitRange((i-1)*5+1, i*5)
  end

  n = 400
  p = 1000
  X = randn(n, p)
  Y = X[:,1:50] * ones(50) + 0.1 * randn(n)
  XX = X' * X / n
  Xyn = -X' * Y / n

  λ = 0.4 .* ones(numGroups)
  x = zeros(p)
  CDLasso.group_lasso!(x, XX, Xyn, λ, groupToIndex)

  for i=1:200
    if norm(x[groupToIndex[i]]) < 1e-6
      @fact norm(XX[groupToIndex[i], :]*x + Xyn[groupToIndex[i]]) <= λ[i] + 1e-4  --> true
    else
      @fact XX[groupToIndex[i], :]*x + Xyn[groupToIndex[i]] + (λ[i]/norm(x[groupToIndex[i]]))*x[groupToIndex[i]] --> roughly(zeros(length(groupToIndex[i])); atol=1e-4)
    end
  end


  λ = 0.01 .* ones(numGroups)
  x = zeros(p)
  CDLasso.group_lasso!(x, XX, Xyn, λ, groupToIndex)

  for i=1:200
    if norm(x[groupToIndex[i]]) < 1e-6
      @fact norm(XX[groupToIndex[i], :]*x + Xyn[groupToIndex[i]]) <= λ[i] + 1e-4  --> true
    else
      @fact XX[groupToIndex[i], :]*x + Xyn[groupToIndex[i]] + (λ[i]/norm(x[groupToIndex[i]]))*x[groupToIndex[i]] --> roughly(zeros(length(groupToIndex[i])); atol=1e-4)
    end
  end


  λ = 40 .* ones(numGroups)
  x = zeros(p)
  CDLasso.group_lasso!(x, XX, Xyn, λ, groupToIndex)

  for i=1:200
    if norm(x[groupToIndex[i]]) < 1e-6
      @fact norm(XX[groupToIndex[i], :]*x + Xyn[groupToIndex[i]]) <= λ[i] + 1e-4  --> true
    else
      @fact XX[groupToIndex[i], :]*x + Xyn[groupToIndex[i]] + (λ[i]/norm(x[groupToIndex[i]]))*x[groupToIndex[i]] --> roughly(zeros(length(groupToIndex[i])); atol=1e-4)
    end
  end


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
  @fact x --> roughly([0, -0.5, -1.5])

  λ = [0.9, 2.1, 3.1]
  x = zeros(3)
  CDLasso.lasso!(x, A, b, λ)
  @fact x --> roughly([-0.1, 0, 0])
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
  @fact beta --> roughly(zeros(p))
end


##############################################
#
#  Other
#
##############################################

facts("SoftThreshold") do

  @fact CDLasso.shrink(5., 3.) --> 2.
  @fact CDLasso.shrink(-2., 3.) --> 0.
  @fact CDLasso.shrink(-1.,1.) --> 0.
  @fact CDLasso.shrink(-1.,0.9) --> roughly(-0.1, 1e-5)

end

FactCheck.exitstatus()
