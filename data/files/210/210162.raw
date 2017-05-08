# getFullsizeModelData: getting the data of full-size model which is entered by users
function getFullsizeModelData(m::JuMP.Model)
  # parameter
  # input:
  # m: the model entered by users using JuMP
  # output:
  # fullsizeObjSense: the objective sense of full-size model (Max or Min)
  # fullsizeObjCoeff: the coefficients of objective function of full-size model
  # fullsizeConstLB: the lower bound of each constraint of full-size model, which is a vector
  # fullsizeConstUB: the upper bound of each constraint of full-size model, which is a vector
  # fullsizeConstMatrix: the constraint matrix of full-size model
  # fullsizeVarLB: the lower bound of each varible of full-size model, which is a vector
  # fullsizeVarUB: the upper bound of each varible of full-size model, which is a vector
  # fullsizeNumVar: number of variables of full-size model
  # fullsizeNumConst: number of constraints of full-size model

  fullsizeObjSense = m.objSense
  fullsizeObjCoeff, fullsizeConstLB, fullsizeConstUB = JuMP.prepProblemBounds(m)
  fullsizeConstMatrix = JuMP.prepConstrMatrix(m)
  fullsizeVarLB = m.colLower
  fullsizeVarUB = m.colUpper

  fullsizeNumVar = m.numCols
  fullsizeNumConst = length(fullsizeConstLB)

  return fullsizeObjSense, fullsizeObjCoeff, fullsizeConstLB, fullsizeConstUB, fullsizeConstMatrix, fullsizeVarLB, fullsizeVarUB, fullsizeNumVar, fullsizeNumConst
end

# identifying formulation of model, which is envelopment form or multiplier form
function identifyModelForm(fullsizeObjCoeff::Vector{Float64})
  # parameters
  # input
  # fullsizeObjCoeff: the coefficients of objective function of full-size model
  # output
  # modelForm: formulation of model, which is envelopment form or multiplier form
  modelForm = :Envelopment
  objSum = sum(fullsizeObjCoeff)

  # if summatiom of coefficients of objective function is 1 or -1, the model is envelopment form
  if objSum == 1 || objSum == -1
    modelForm = :Envelopment
  else
    modelForm = :Multiplier
  end

  return modelForm
end

# getting the right hand side of model by its constraints lower and upper bound
function getRHS(constLB::Vector{Float64}, constUB::Vector{Float64})
  # parameters
  # input
  # constLB: the lower bound of each constraint of  model, which is a vector
  # constUB: the upper bound of each constraint of  model, which is a vector
  # output
  # rhs: right hand side of model, which is a vector

  numConst = length(constLB)
  rhs = Array(Float64, numConst)

  # if the lower bound of constraint is -Inf, the constraint is "<=" its rhs and its rhs is its upper bound
  lb = find(x -> x != -Inf, constLB)
  rhs[lb] = constLB[lb]
  # if the upper bound of constraint is Inf, the constraint is ">=" its rhs and its rhs is its lower bound
  ub = find(x -> x != Inf, constUB)
  rhs[ub] = constUB[ub]

  return rhs
end

# transforming model from mutiplier form to envelopment form
function modelTransform(fullsizeObjSense::Symbol, fullsizeObjCoeff::Vector{Float64}, fullsizeConstLB::Vector{Float64}, fullsizeConstUB::Vector{Float64},
                        fullsizeConstMatrix::SparseMatrixCSC, fullsizeVarLB::Vector{Float64}, fullsizeVarUB::Vector{Float64}, fullsizeNumVar::Int, fullsizeNumConstr::Int)
  # parameter
  # input
  # data of model which is multiplier form
  # output
  # data of model which is transformed to envelopment form

  # transforming coefficients of objective function
  newObjCoeff = getRHS(fullsizeConstLB, fullsizeConstUB)
  # transforming constraint matrix
  newMatrix = transpose(fullsizeConstMatrix)
  newNumConst, newNumVar = size(newMatrix)

  # initialization
  newVarLB = fill(NaN, newNumVar)
  newVarUB = fill(NaN, newNumVar)
  newConstLB = fill(NaN, newNumConst)
  newConstUB = fill(NaN, newNumConst)

  # transforming objective sense
  newObjSense = :Min

  # the rule of tranforming is different by objective sense
  if fullsizeObjSense == :Max
    newObjSense = :Min

    # transforming lower bound and upper bound of variables
    # finding the indices of constraints whose senses are ">="
    constSenseMore = find(x -> x == Inf, fullsizeConstUB)
    newVarLB[constSenseMore] = -Inf
    newVarUB[constSenseMore] = 0

    # finding the indices of constraints whose senses are "<="
    constSenseLess = find(x -> x == -Inf, fullsizeConstLB)
    newVarLB[constSenseLess] = 0
    newVarUB[constSenseLess] = Inf

    # finding the indices of constraints whose senses are "=="
    constSenseEqual = find(x -> isnan(x), newVarLB)
    newVarLB[constSenseEqual] = -Inf
    newVarUB[constSenseEqual] = Inf

    # transforming lower bound and upper bound of variables
    # finding the indices of variables which are ">= 0"
    varSenseMore = find(x -> x == 0, fullsizeVarLB)
    newConstLB[varSenseMore] = fullsizeObjCoeff[varSenseMore]
    newConstUB[varSenseMore] = Inf

    # finding the indices of variables which are "<= 0"
    varSenseLess = find(x -> x == 0, fullsizeVarUB)
    newConstLB[varSenseLess] = -Inf
    newConstUB[varSenseLess] = fullsizeObjCoeff[varSenseLess]

    # finding the indices of variables which are unbounded
    vrsUnbounded = find(x -> isnan(x), newConstLB)
    newConstLB[vrsUnbounded] = fullsizeObjCoeff[vrsUnbounded]
    newConstUB[vrsUnbounded] = fullsizeObjCoeff[vrsUnbounded]

  else
    newObjSense = :Max

    # transforming lower bound and upper bound of variables
    # finding the indices of constraints whose senses are ">="
    constSenseMore = find(x -> x == Inf, fullsizeConstUB)
    newVarLB[constSenseMore] = 0
    newVarUB[constSenseMore] = Inf

    # finding the indices of constraints whose senses are "<="
    constSenseLess = find(x -> x == -Inf, fullsizeConstLB)
    newVarLB[constSenseLess] = -Inf
    newVarUB[constSenseLess] = 0

    # finding the indices of constraints whose senses are "=="
    constSenseEqual = find(x -> isnan(x), newVarLB)
    newVarLB[constSenseEqual] = -Inf
    newVarUB[constSenseEqual] = Inf

    # transforming lower bound and upper bound of variables
    # finding the indices of variables which are ">= 0"
    varSenseMore = find(x -> x == 0, fullsizeVarLB)
    newConstLB[varSenseMore] = -Inf
    newConstUB[varSenseMore] = fullsizeObjCoeff[varSenseMore]

    # finding the indices of variables which are "<= 0"
    varSenseLess = find(x -> x == 0, fullsizeVarUB)
    newConstLB[varSenseLess] = fullsizeObjCoeff[varSenseLess]
    newConstUB[varSenseLess] = Inf

    # finding the indices of variables which are unbounded
    vrsUnbounded = find(x -> isnan(x), newConstLB)
    newConstLB[vrsUnbounded] = fullsizeObjCoeff[vrsUnbounded]
    newConstUB[vrsUnbounded] = fullsizeObjCoeff[vrsUnbounded]
  end

  return newObjSense, newObjCoeff, newConstLB, newConstUB, newMatrix, newVarLB, newVarUB, newNumVar, newNumConst
end

# finding theta, which is the index w.r.t variable vector
# parameters
# input
# fullsizeObjCoeff: the coefficients of objective function of full-size model
# output: the index of theta w.r.t variable vector
findThetaIdx(fullsizeObjCoeff::Vector{Float64}) = find(x -> x != 0, fullsizeObjCoeff)[1]

# getting the coefficients of constraints of target DMU
function getTargetDMU(fullsizeConstLB::Vector{Float64}, fullsizeConstUB::Vector{Float64}, fullsizeConstMatrix::SparseMatrixCSC, thetaIdx::Int)
  # parameters
  # input
  # fullsizeConstLB: the lower bound of each constraint of full-size model, which is a vector
  # fullsizeConstUB: the upper bound of each constraint of full-size model, which is a vector
  # fullsizeConstMatrix: the constraint matrix of full-size model
  # thetaIdx: the index of theta w.r.t variable vector
  # output
  # targetDMU: the coefficients of constraints of target DMU, which is a vector

  # the coefficients of output constraints of target DMU is equal to the rhs of output constraints
  rhs = getRHS(fullsizeConstLB, fullsizeConstUB)
  # the coefficients of input constraints of target DMU is equal to the coefficients of theta
  coeffOfTheta = full(fullsizeConstMatrix[:, thetaIdx])

  targetDMU = rhs-coeffOfTheta
  return targetDMU[:, 1]
end

# finding the index of target DMU w.r.t variable vector by finding the vector from constraint matrix which is same as target DMU
function findTargetDMUIdx(constMatrix::SparseMatrixCSC, targetDMU::Vector{Float64})
  # parameters
  # input
  # constMatrix: the constraint matrix of model
  # targetDMU: the coefficients of constraints of target DMU, which is a vector
  # output
  # targetDMUIdx: the index of target DMU w.r.t variable vector

  dimension, scale = size(constMatrix)
  targetDMUIdx = 0
  numSame = scale
  colmn = 1
  check = collect(1:scale)
  idxOfSame = collect(1:scale)

  while colmn <= dimension && numSame != 0
    idxOfSame = find(x -> x == targetDMU[colmn], constMatrix[colmn, check])
    check = check[idxOfSame]
    numSame = length(idxOfSame)

    colmn = colmn + 1
  end

  if numSame != 0
    targetDMUIdx = check[1]
  else
    error("couldn't find target DMU in constraint matrix")
  end

  return targetDMUIdx
end

# generating the coefficients of objective function, lower and upper bound of varibles of small model by set, targetDMUIdx and thetaIdx
function generateSmallV(v::Vector{Float64}, lpUB::Int, set::Vector{Int}, targetDMUIdx::Int, thetaIdx::Int)
  # parameters
  # input
  # v: vector of full-size model, which may be coefficients of objective function, lower or upper bound of varibles
  # lpUB: the limit size of LP
  # set: the selected DMUs, which are the indices w.r.t the variable vector
  # targetDMUIdx: the index of target DMU w.r.t variable vector
  # thetaIdx: the index of theta w.r.t variable vector 
  # output
  # smallV: vector of small model, which may be coefficients of objective function, lower or upper bound of varibles

  smallV = Array(Float64, lpUB)
  smallV[1:lpUB-2] = v[set]
  smallV[lpUB-1] = v[targetDMUIdx]
  smallV[lpUB] = v[thetaIdx]

  return smallV
end
