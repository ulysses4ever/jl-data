# sampling: randomly selecting DMUs to build a small model with predefined lp size of lpUB
function sampling(lpUB::Int, fullsizeConstMatrix::SparseMatrixCSC, thetaIdx::Int, targetDMUIdx::Int)
  # parameter
  # input
  # lpUB: the limit size of LP
  # fullsizeConstMatrix: the constraint matrix of full-size model
  # thetaIdx: the index of theta w.r.t the variable vector
  # targetDMUIdx: target DMU, which is the index w.r.t the variable vector
  # output
  # set: the selected DMUs, which are the indices w.r.t the variable vector
  # notset: the unselected DMUs, which are the indices w.r.t the variable vector
  # smallConstMatrix: the constraint matrix of small model

  # definition and initialization
  dimension, scale = size(fullsizeConstMatrix)
  sampleSize = lpUB - 2 #saving spaces for theta and target DMU

  set = Array(Int, sampleSize)
  candidate = collect(1:scale) # candidate of DMUs which will be selected
  randNum = 0
  smallConstMatrix = fullsizeConstMatrix[:, 1:lpUB]

  # removing the indices of theta and target DMU from candidate
  candidate[thetaIdx] = candidate[scale]
  candidate[targetDMUIdx] = candidate[scale-1]

  # randomly sampling without replacement
  for i = 1:sampleSize
    randNum = rand(1:scale-i-1)
    set[i] = candidate[randNum]
    candidate[randNum] = candidate[scale-i-1]
  end

  candidate = candidate[1:scale-sampleSize-1]

  # inserting data into constraint matix of small model
  smallConstMatrix[:, 1:sampleSize] = fullsizeConstMatrix[:, set]
  smallConstMatrix[:, sampleSize+1] = fullsizeConstMatrix[:, targetDMUIdx]
  smallConstMatrix[:, sampleSize+2] = fullsizeConstMatrix[:, thetaIdx]

  notset = candidate #the unselected DMUs, which are the indices w.r.t the variable vector

  return set, notset, smallConstMatrix
end

# checkOpt: cheking the solution is optimal or not, if not, recording the most infeasible DMU which is the index w.r.t. notset
function checkOpt(constDuals::Vector{Float64}, notset::Vector{Int}, fullsizeConstMatrix::SparseMatrixCSC, sense::Symbol)
  # parameter
  # input
  # constDuals: the dual values of small model
  # notset: the unselected DMUs, which are the indices w.r.t the variable vector
  # fullsizeConstMatrix: the constraint matrix of full-size model
  # output
  # optimal: status of solution, if solution is optimal return ture, if not, return false
  # overNum: the most infeasible DMU, which is the index w.r.t. notset

  optimal = true
  overNum = 0
  checkValue = 0.0

  checkResult = constDuals.'*fullsizeConstMatrix
  #println(checkResult)

  if sense == :Min
    checkValue, overNum = findmax(checkResult[notset])
    optimal = checkValue <= 10.0^-5
  else
    checkValue, overNum = findmin(checkResult[notset])
    optimal = checkValue >= -10.0^-5
  end

  optimal, overNum[1]
end

# reSampling: deleting a DMUs from set and adding the most infeasible DMUs to set
function reSampling(overNum::Int, iterations::Int, set::Vector{Int}, notset::Vector{Int},
                    smallConstMatrix::SparseMatrixCSC, smallVarLB::Vector{Float64}, smallVarUB::Vector{Float64}, smallObjCoeff::Vector{Float64},
                    fullsizeConstMatrix::SparseMatrixCSC, fullsizeVarLB::Vector{Float64}, fullsizeVarUB::Vector{Float64}, fullsizeObjCoeff::Vector{Float64})

  # parameter
  # input
  # overNum: the most infeasible DMU, which is the index w.r.t. notset
  # iterations: iterations that algorithm has run
  # set: the selected DMUs, which are the indices w.r.t the collumn of variable vector
  # notset: the unselected DMUs, which are the indices w.r.t the collumn of variable vector
  # small model: smallConstMatrix, smallVarLB, smallVarUB, smallObjCoeff
  # full-size model: fullsizeConstMatrix, fullsizeVarLB, fullsizeVarUB, fullsizeObjCoeff

  deleteIdx = mod(iterations, length(set))
  if deleteIdx == 0
    deleteIdx = length(set)
  end

  smallConstMatrix[:, deleteIdx] = fullsizeConstMatrix[:, notset[overNum]]
  smallVarLB[deleteIdx] = fullsizeVarLB[notset[overNum]]
  smallVarUB[deleteIdx] = fullsizeVarUB[notset[overNum]]
  smallObjCoeff[deleteIdx] = fullsizeObjCoeff[notset[overNum]]

  temp = set[deleteIdx]
  set[deleteIdx] = notset[overNum]
  notset[overNum] = temp
end
