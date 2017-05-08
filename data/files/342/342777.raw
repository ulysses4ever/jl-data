##  SCRIPT NAME:   utilities.jl
##  DATE:          May 2015
#
#   This script declares the utility functions of each household member.
#   It also declares the marginal utilities.
#
#
##  ALEXANDROS THELOUDIS, UCL

##  ---------------------------------------------------------------------------------------------

##  UTILITIES
#   Utility husband:
function utility1(cH::Float64, Q::Float64)

  # Declare utility parameters:
  aCH 		= 1/2
  aQH 		= 1/2
  gammaCH 	= 3/2
  gammaQH 	= 3/2

  utility = aCH*(cH^(1-gammaCH))/(1-gammaCH) + aQH*(Q^(1-gammaQH))/(1-gammaQH)
end

#   Utility wife:
function utility2(cW::Float64, Q::Float64)

  # Declare utility parameters:
  aCW 		= 1/2
  aQW 		= 1/2
  gammaCW 	= 3/2
  gammaQW 	= 3/2

  utility = aCW*(cW^(1-gammaCW))/(1-gammaCW) + aQW*(Q^(1-gammaQW))/(1-gammaQW)
end

##  ---------------------------------------------------------------------------------------------
##  MARGINAL UTILITIES
#   Marginal utility husband / private good
function mUtil1_c1(cH::Float64, Q::Float64)

  # Declare utility parameters:
  aCH 		= 1/2
  aQH 		= 1/2
  gammaCH 	= 3/2
  gammaQH 	= 3/2

  marginal_utility = aCH * (cH^(-gammaCH))
end

#   Marginal utility wife / private good
function mUtil2_c2(cW::Float64, Q::Float64)

  # Declare utility parameters:
  aCW 		= 1/2
  aQW 		= 1/2
  gammaCW 	= 3/2
  gammaQW 	= 3/2

  marginal_utility = aCW * (cW^(-gammaCW))
end

#   Marginal utility husband / public good
function mUtil1_q(cH::Float64, Q::Float64)

  # Declare utility parameters:
  aCH 		= 1/2
  aQH 		= 1/2
  gammaCH 	= 3/2
  gammaQH 	= 3/2

  marginal_utility = aQH * (Q^(-gammaQH))
end

#   Marginal utility wife / public good:
function mUtil2_q(cW::Float64, Q::Float64)

  # Declare utility parameters:
  aCW 		= 1/2
  aQW 		= 1/2
  gammaCW 	= 3/2
  gammaQW 	= 3/2

  marginal_utility = aQW * (Q^(-gammaQW))
end
