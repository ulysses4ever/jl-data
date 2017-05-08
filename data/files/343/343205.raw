module JuMPDEA

import JuMP
import MathProgBase

#type DEAModel
#  model::JuMP.Model

#  limitSize::Int#variable size of smaller LP problem
#  #option::Symbol
#  #increase

#  subset::Vector
#  pns::Vector#samples not drawing to subsets

#  originConsMatrix::SparseMatrixCSC#constraint matrix of orignal LP problem (the bogger one)
#  fullOriginConMatrix::Matrix(Float64)
#  transposeOriginMatrix::Matrix(Float64)

#  #data of smaller LP problem
#  smallConsMatrix::SparseMatrixCSC
#  smallVarLB::Vector(Float64)
#  smallVarUB::Vector(Float64)
#  smallConsLB::Vector(Float64)
#  smallConsUB::Vector(Float64)

#  smallObjCoeff::Vector(Float64)
#  smallSense::Symbol

#  optStatus::Bool
#  iterations::Int

#  # DEA data
#  inputNum::Int
#  outputNum::Int
#end

#function DEAModel(m::JuMP.Model; size=300)
#  objCoeff, varLB, varUB = JuMP.prepProblemBounds(m)

#  DEAModel(m, size, )
#end
export solveDEA

function solveDEA(m::JuMP.Model; limitSize=300)
  ##############  get original model data  ##############
  originalConstrMatrix = JuMP.prepConstrMatrix(m)
  originalObjCoeff, originalConstrLB, originalConstrUB = JuMP.prepProblemBounds(m)
  originalVarLB = m.colLower
  originalVarUB = m.colUpper
  originalSense = m.objSense

  originalVarNum = m.numCols

  ###############  Standardize the model  ###############
  thetaPosition = 1
  for i=1:originalVarNum
    if originalVarLB[i] == -Inf
      thetaPosition = i
    end
  end

  tempMatrix = originalConstrMatrix[:, thetaPosition]
  originalConstrMatrix[:, thetaPosition] = originalConstrMatrix[:, originalVarNum]
  originalConstrMatrix[:, originalVarNum] = tempMatrix

  temp = originalVarLB[thetaPosition]
  originalVarLB[thetaPosition] = originalVarLB[originalVarNum]
  originalVarLB[originalVarNum] = temp

  temp = originalVarUB[thetaPosition]
  originalVarUB[thetaPosition] = originalVarUB[originalVarNum]
  originalVarUB[originalVarNum] = temp

  temp = originalObjCoeff[thetaPosition]
  originalObjCoeff[thetaPosition] = originalObjCoeff[originalVarNum]
  originalObjCoeff[originalVarNum] = temp

  ##################  random sampling  ##################
  fullOriginalConstrMatrix = full(originalConstrMatrix)
  transOriginalConstrMatrix = transpose(fullOriginalConstrMatrix)
  set, pns, smallConstrMatrix = sampling(limitSize, originalConstrMatrix)

  ################  build our model data  ################
  smallVarLB = reCreatV(originalVarLB, limitSize)
  smallVarUB = reCreatV(originalVarUB, limitSize)
  smallConstrLB = originalConstrLB
  smallConstrUB = originalConstrUB
  smallObjCoeff = reCreatV(originalObjCoeff, limitSize)
  smallSense = m.objSense

  ########################  loop  ########################
  optStatus = false
  iterations = 0
  overNum = 0
  lm = MathProgBase.model(m.solver)

  while optStatus == false
    iterations = iterations + 1
    optStatus = true

    lm = MathProgBase.model(m.solver)
    MathProgBase.loadproblem!(lm, smallConstrMatrix, smallVarLB, smallVarUB, smallObjCoeff, smallConstrLB, smallConstrUB, smallSense)
    MathProgBase.updatemodel!(lm)
    MathProgBase.optimize!(lm)

    if MathProgBase.status(lm) == :Infeasible
      optStatus, overNum = checkOpt(MathProgBase.getinfeasibilityray(lm), pns, transOriginalConstrMatrix, smallSense)
    else
      optStatus, overNum = checkOpt(MathProgBase.getconstrduals(lm), pns, transOriginalConstrMatrix, smallSense)
    end

    if optStatus == false
      reSampling(overNum, iterations, set, pns, smallConstrMatrix, originalConstrMatrix)
    end
  end

  m.objVal = MathProgBase.getobjval(lm)
  m.objVal += m.obj.aff.constant

end

#################  function: sampling  #################
function sampling(subsetSize::Int, originConsMatrix::SparseMatrixCSC)
  rowNum = size(originConsMatrix)[1]
  colNum = size(originConsMatrix)[2]
  pns = [1:colNum-1]
  set = Array(Int, subsetSize-1)
  randNum = 0
  smallConsMatrix = originConsMatrix[1:rowNum, 1:subsetSize]
  temp = 0.0

  for i = 1:rowNum
    smallConsMatrix[i,subsetSize] = originConsMatrix[i,colNum]
  end

  for i = 1:subsetSize-1
    randNum = rand(1:colNum-i)
    set[i] = pns[randNum]
    temp = pns[randNum]
    pns[randNum] = pns[colNum-i]
    pns[colNum-i] = temp

    for j = 1:rowNum
      smallConsMatrix[j, i] = originConsMatrix[j, set[i]]
    end
  end

  pns = pns[1:colNum-subsetSize]

  return set, pns, smallConsMatrix
end

######  function: recreat varLB, varUB, objCoeff  ######
function reCreatV(v::Vector{Float64}, subsetSize::Int)
  newV = Array(Float64, subsetSize)
  newV[1:subsetSize-1] = v[1:subsetSize-1]
  newV[subsetSize] = v[length(v)]
  return newV
end

#############  function: check optimality  #############
function checkOpt(uv::Vector{Float64}, pns::Vector{Int}, data::Matrix{Float64}, sense::Symbol)
  optimal = true
  overNum = 0
  checkValue = 0.0

  if sense == :Min
    checkValue, overNum = findmax(data[pns, :]*uv)
    optimal = checkValue <= 0
  else
    checkValue, overNum = findmin(data[pns, :]*uv)
    optimal = checkValue >= 0
  end

  optimal, overNum
end

################  function: reSampling  ################
function reSampling(overNum::Int, iteration::Int, set::Vector{Int}, pns::Vector{Int},
                    smallConsMatrix::SparseMatrixCSC, originConsMatrix::SparseMatrixCSC)
  iteration = mod(iteration, length(set))
  if iteration == 0
    iteration = length(set)
  end

  for i = 1:size(smallConsMatrix)[1]
    smallConsMatrix[i, iteration] = originConsMatrix[i, pns[overNum]]
  end

  temp = set[iteration]
  set[iteration] = pns[overNum]
  pns[overNum] = temp
end

end
