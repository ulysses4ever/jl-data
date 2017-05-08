module JuMP4DEA

import JuMP
import MathProgBase

export solveDEA, solveDEAM

#type deaModel
#  m::JuMP.Model

#  iteration::Int
#end

function solveDEA(m::JuMP.Model; limitSize=300)
  # get original model data
  originalConstrMatrix = JuMP.prepConstrMatrix(m)
  originalObjCoeff, originalConstrLB, originalConstrUB = JuMP.prepProblemBounds(m)
  originalVarLB = m.colLower
  originalVarUB = m.colUpper
  originalSense = m.objSense

  originalVarNum = m.numCols
  originalConstrNum = length(originalConstrLB)

  thetaPosition = findTheta(originalVarLB)

  # check orientation
  orientation, sumPosition = checkOrientation(originalConstrLB, originalConstrUB)

  # random sampling
  # 隨機挑選在變數並將該變數的index儲存於set中
  # 未被挑選的變數則存則儲存於pns中
  # 其中smallConstrMatrix為小問題的constraint matrix
  fullOriginalConstrMatrix = full(originalConstrMatrix)
  transOriginalConstrMatrix = transpose(fullOriginalConstrMatrix)
  set, pns, smallConstrMatrix = sampling(limitSize, thetaPosition, originalConstrMatrix)

  # build data of small sizes model
  # 將model的資訊轉換為小問題的model資訊
  smallVarLB = reCreatV(originalVarLB, limitSize, thetaPosition)
  smallVarUB = reCreatV(originalVarUB, limitSize, thetaPosition)
  smallConstrLB = originalConstrLB
  smallConstrUB = originalConstrUB
  smallObjCoeff = reCreatV(originalObjCoeff, limitSize, thetaPosition)
  smallSense = m.objSense

  ########################  loop  ########################
  optStatus = false
  iterations = 0
  overNum = 0
  lm = MathProgBase.model(m.solver)
  stat = :Default

  while optStatus == false
    iterations = iterations + 1
    if iterations > 300
      warn("Iterations > 300")
      stat = :Unsolved
      break
    end
    optStatus = true

    lm = MathProgBase.model(m.solver)
    MathProgBase.loadproblem!(lm, smallConstrMatrix, smallVarLB, smallVarUB, smallObjCoeff, smallConstrLB, smallConstrUB, smallSense)
    MathProgBase.updatemodel!(lm)
    MathProgBase.optimize!(lm)

    stat = MathProgBase.status(lm)
    constrDuals = MathProgBase.getconstrduals(lm)

    #if sumPosition != 0 && orientation == "output"
    #  constrDuals[sumPosition] = -constrDuals[sumPosition]
    #end

    #optStatus, overNum = checkOpt(constrDuals, pns, transOriginalConstrMatrix, smallSense, orientation)
    optStatus, overNum = checkOpt(constrDuals, pns, transOriginalConstrMatrix, smallSense)

    if optStatus == false
      reSampling(overNum, iterations, set, pns, smallConstrMatrix, originalConstrMatrix)
    end
  end

  # store solution values in model
  if stat == :Optimal
    m.objVal = MathProgBase.getobjval(lm)
    m.objVal += m.obj.aff.constant
    m.linconstrDuals = MathProgBase.getconstrduals(lm)
    #m.redCosts = MathProgBase.getreducedcosts(lm)

    m.colVal = fill(0.0, originalVarNum)
    colVal = MathProgBase.getsolution(lm)
    for i = 1:limitSize-1
      m.colVal[set[i]] = colVal[i]
    end
    m.colVal[thetaPosition] = colVal[limitSize]
    #m.colVal
  else
    m.objVal = NaN
    m.linconstrDuals = fill(NaN, originalConstrNum)
    #m.redCosts = fill(NaN, originalConstrNum)
    m.colVal = fill(NaN, originalVarNum)
  end

  return stat, iterations
end

# function: check orientation
function checkOrientation(constrLB::Vector{Float64}, constrUB::Vector{Float64})
  orientation = ""
  sumPosition = 0

  for i = 1:length(constrLB)
    if constrLB[i] != 0 && constrUB[i] != 0
      if constrLB[i]*constrUB[i] <　0
        orientation = "output"
      elseif constrLB[i] == 1 && constrUB[i] == 1
        sumPosition = i
      else
        orientation = "input"
      end
    end
  end

  return orientation, sumPosition
end

function solveDEAM(m::JuMP.Model; limitSize=300, multiplier=1000)
  # get original model data
  originalConstrMatrix = JuMP.prepConstrMatrix(m)
  originalObjCoeff, originalConstrLB, originalConstrUB = JuMP.prepProblemBounds(m)
  originalVarLB = m.colLower
  originalVarUB = m.colUpper
  originalSense = m.objSense

  originalVarNum = m.numCols
  originalConstrNum = length(originalConstrLB)

  thetaPosition = findTheta(originalVarLB)

  # check orientation
  orientation, sumPosition = checkOrientation(originalConstrLB, originalConstrUB)

  # 紀錄k，並將原本的k縮小m倍
  k = ones(Float64, originalConstrNum)
  num = convert(Int, (originalConstrNum-1)/2)
  #num = convert(Int, num)
  k[1:num] = -originalConstrMatrix[1:num, thetaPosition]
  k[(num + 1):originalConstrNum-1] = originalConstrLB[(num + 1):originalConstrNum-1]
  k = transpose(k)
  originalConstrMatrix[1:num, thetaPosition] = originalConstrMatrix[1:num, thetaPosition]*multiplier

  # random sampling
  # 隨機挑選在變數並將該變數的index儲存於set中
  # 未被挑選的變數則存則儲存於pns中
  # 其中smallConstrMatrix為小問題的constraint matrix
  fullOriginalConstrMatrix = full(originalConstrMatrix)
  transOriginalConstrMatrix = transpose(fullOriginalConstrMatrix)
  set, pns, smallConstrMatrix = sampling(limitSize, thetaPosition, originalConstrMatrix)

  # build data of small sizes model
  # 將model的資訊轉換為小問題的model資訊
  smallVarLB = reCreatV(originalVarLB, limitSize, thetaPosition)
  smallVarUB = reCreatV(originalVarUB, limitSize, thetaPosition)
  smallConstrLB = originalConstrLB
  smallConstrUB = originalConstrUB
  smallObjCoeff = reCreatV(originalObjCoeff, limitSize, thetaPosition)
  smallSense = m.objSense

  ########################  loop  ########################
  optStatus = false
  iterations = 0
  overNum = 0
  lm = MathProgBase.model(m.solver)
  stat = :Default

  while optStatus == false
    iterations = iterations + 1
    if iterations > 300
      warn("Iterations > 300")
      stat = :Unsolved
      break
    end
    optStatus = true

    lm = MathProgBase.model(m.solver)
    MathProgBase.loadproblem!(lm, smallConstrMatrix, smallVarLB, smallVarUB, smallObjCoeff, smallConstrLB, smallConstrUB, smallSense)
    MathProgBase.updatemodel!(lm)
    MathProgBase.optimize!(lm)

    stat = MathProgBase.status(lm)

    if stat == :Infeasible
      constrDuals = MathProgBase.getinfeasibilityray(lm)
    else
      constrDuals = MathProgBase.getconstrduals(lm)
    end

    #if sumPosition != 0 && orientation == "output"
    #  constrDuals[sumPosition] = -constrDuals[sumPosition]
    #end

    #optStatus, overNum = checkOpt(constrDuals, pns, transOriginalConstrMatrix, smallSense, orientation)
    optStatus, overNum = checkOpt(constrDuals, pns, transOriginalConstrMatrix, smallSense)

    if optStatus == true
      kKKT = k*constrDuals
      optStatus = kKKT[1] <= 0
    end

    if optStatus == false
      reSampling(overNum, iterations, set, pns, smallConstrMatrix, originalConstrMatrix)
    end
  end

  # store solution values in model
  if stat == :Optimal
    m.objVal = MathProgBase.getobjval(lm)
    m.objVal += m.obj.aff.constant
    m.linconstrDuals = MathProgBase.getconstrduals(lm)
    #m.redCosts = MathProgBase.getreducedcosts(lm)

    m.colVal = fill(0.0, originalVarNum)
    colVal = MathProgBase.getsolution(lm)
    for i = 1:limitSize-1
      m.colVal[set[i]] = colVal[i]
    end
    m.colVal[thetaPosition] = colVal[limitSize]
    #m.colVal
  else
    m.objVal = NaN
    m.linconstrDuals = fill(NaN, originalConstrNum)
    #m.redCosts = fill(NaN, originalConstrNum)
    m.colVal = fill(NaN, originalVarNum)
  end

  return stat, iterations
end

# function: check orientation
function checkOrientation(constrLB::Vector{Float64}, constrUB::Vector{Float64})
  orientation = ""
  sumPosition = 0

  for i = 1:length(constrLB)
    if constrLB[i] != 0 && constrUB[i] != 0
      if constrLB[i]*constrUB[i] <　0
        orientation = "output"
      elseif constrLB[i] == 1 && constrUB[i] == 1
        sumPosition = i
      else
        orientation = "input"
      end
    end
  end

  return orientation, sumPosition
end

# function: sampling
function sampling(subsetSize::Int, thetaPosition::Int, originConsMatrix::SparseMatrixCSC)
  rowNum = size(originConsMatrix)[1] # number of constraints
  colNum = size(originConsMatrix)[2] # number of variables

  # initialize small constraint matrix, set, and peer not set
  smallConsMatrix = originConsMatrix[1:rowNum, 1:subsetSize]
  set = Array(Int, subsetSize-1)
  pns = Array(Int, colNum-1)
  if thetaPosition == 1
    pns = [2:colNum]
  elseif thetaPosition == colNum
    pns = [1:colNum-1]
  else
    pns[1:thetaPosition-1] = [1:thetaPosition-1]
    pns[thetaPosition:colNum-1] = [thetaPosition+1:colNum]
  end

  randNum = 0
  temp = 0.0

  smallConsMatrix[1:rowNum ,subsetSize] = originConsMatrix[1:rowNum,thetaPosition]

  for i = 1:subsetSize-1
    randNum = rand(1:colNum-i)
    set[i] = pns[randNum]
    temp = pns[randNum]
    pns[randNum] = pns[colNum-i]
    pns[colNum-i] = temp

    smallConsMatrix[1:rowNum, i] = originConsMatrix[1:rowNum, set[i]]
  end

  pns = pns[1:colNum-subsetSize]

  return set, pns, smallConsMatrix
end

######  function: recreat varLB, varUB, objCoeff  ######
function reCreatV(v::Vector{Float64}, subsetSize::Int, thetaPosition::Int)
  newV = Array(Float64, subsetSize)
  if thetaPosition == 1
    newV = fill(v[2], subsetSize)
  else
    newV = fill(v[1], subsetSize)
  end

  newV[subsetSize] = v[thetaPosition]

  return newV
end

# function: check optimality
#function checkOpt(uv::Vector{Float64}, pns::Vector{Int}, data::Matrix{Float64}, sense::Symbol, orientation::String)
function checkOpt(uv::Vector{Float64}, pns::Vector{Int}, data::Matrix{Float64}, sense::Symbol)
  optimal = true
  overNum = 0
  checkValue = 0.0

  #if orientation == "input"
  if sense == :Min
    checkValue, overNum = findmax(data[pns, :]*uv)
    optimal = checkValue <= 0
  else
    checkValue, overNum = findmin(data[pns, :]*uv)
    optimal = checkValue >= 0
  end
  #else
  #  if sense == :Max
  #    checkValue, overNum = findmin(data[pns, :]*uv)
  #    optimal = checkValue >= 0
  #  else

  optimal, overNum
end

# function: reSampling
function reSampling(overNum::Int, iterations::Int, set::Vector{Int}, pns::Vector{Int},
                    smallConsMatrix::SparseMatrixCSC, originConsMatrix::SparseMatrixCSC)
  iterations = mod(iterations, length(set))
  if iterations == 0
    iterations = length(set)
  end

  for i = 1:size(smallConsMatrix)[1]
    smallConsMatrix[i, iterations] = originConsMatrix[i, pns[overNum]]
  end

  temp = set[iterations]
  set[iterations] = pns[overNum]
  pns[overNum] = temp
end

# find the index of theta
function findTheta(originalVarLB::Vector{Float64})
  numVar = length(originalVarLB)
  thetaPosition = 0

  for i=1:numVar
    if originalVarLB[i] == -Inf
      thetaPosition = i
    end
  end

  return thetaPosition
end

# fuction: find dominated DMUs
#function findDominated(data::Matrix{Float64})

#end

end
