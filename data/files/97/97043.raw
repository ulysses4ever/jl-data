using FactCheck

import CDLasso

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