# functions to preprocess the data and classify some information of model that algorithm needed
include("modelPreprocessing.jl")
# functions of algorithm
include("algorithm.jl")

# solveDEA: solving dea problems by a smart algorithm
function solveDEA(m::JuMP.Model; lpUB=300)
  # parameters
  # input
  # m: model variable of JuMP which is entered by JuMP's scripts
  # lpUB: the limit size of LP

  # data preprocessing
  # getting the data of full-size model which is entered by users
  fullsizeObjSense, fullsizeObjCoeff, fullsizeConstLB, fullsizeConstUB, fullsizeConstMatrix, fullsizeVarLB, fullsizeVarUB, fullsizeNumVar, fullsizeNumConst = getFullsizeModelData(m)

  # checking the formulation of model is envelopment form or mutiplier form
  # envelopment form and mutiplier form are dual relationships
  modelForm = identifyModelForm(fullsizeObjCoeff)

  # if model is mutiplier form, the model has to transform to envelopment form
  if modelForm == :Multiplier
    # tranforming model to envelopment form
    fullsizeObjSense, fullsizeObjCoeff, fullsizeConstLB, fullsizeConstUB, fullsizeConstMatrix, fullsizeVarLB, fullsizeVarUB, fullsizeNumVar, fullsizeNumConst = modelTransform(fullsizeObjSense, fullsizeObjCoeff, fullsizeConstLB, fullsizeConstUB, fullsizeConstMatrix, fullsizeVarLB, fullsizeVarUB, fullsizeNumVar, fullsizeNumConst)
  end

  # finding the index of theta w.r.t the variable vector
  thetaIdx = findThetaIdx(fullsizeObjCoeff)
  # getting the target DMU by rhs and the coefficients of theta in constraints
  targetDMU = getTargetDMU(fullsizeConstLB, fullsizeConstUB, fullsizeConstMatrix, thetaIdx)
  # finding the index of target DMU w.r.t the variable vector
  targetDMUIdx = findTargetDMUIdx(fullsizeConstMatrix, targetDMU)
  # end data preprocessing

  # randomly selecting DMUs to build a small model with predefined lp size of lpUB
  set, notset, smallConstMatrix = sampling(lpUB, fullsizeConstMatrix, thetaIdx, targetDMUIdx)

  #generating the data of small model by set
  smallVarLB = generateSmallV(fullsizeVarLB, lpUB, set, targetDMUIdx, thetaIdx)
  smallVarUB = generateSmallV(fullsizeVarUB, lpUB, set, targetDMUIdx, thetaIdx)
  smallObjCoeff = generateSmallV(fullsizeObjCoeff, lpUB, set, targetDMUIdx, thetaIdx)
  smallConstLB = fullsizeConstLB
  smallConstUB = fullsizeConstUB
  smallSense = fullsizeObjSense

  # definition and initialization
  optStatus = false   # the optimality status of model
  iterations = 0      # the iterations that algorithm uses to solve model
  overNum = 0         # the most infeasible DMU, which is the indices w.r.t. notset

  lm = MathProgBase.LinearQuadraticModel(m.solver)  # model variable of MathProgBase, we use this to build small model
  stat = :Default     # model status
  m.objVal = NaN      # objective value of full-size model
  m.colVal = fill(NaN, fullsizeNumVar)    # values of all variables of full-size model
  m.linconstrDuals = Array(Float64, 0)    # dual values of full-size model

  # loop until model being solved to optimal or algorithm processing over 1000 iterations
  while optStatus == false
    iterations = iterations + 1
    if iterations > 1000
      warn("Iterations > 1000")
      stat = :Unsolved
      break
    end
    optStatus = true

    lm = MathProgBase.LinearQuadraticModel(m.solver)
    # loading model information
    MathProgBase.loadproblem!(lm, smallConstMatrix, smallVarLB, smallVarUB, smallObjCoeff, smallConstLB, smallConstUB, smallSense)
    # solving model
    MathProgBase.optimize!(lm)

    stat = MathProgBase.status(lm)
    # getting dual values of small model
    constDuals = MathProgBase.getconstrduals(lm)

    # checking optimality and getting the most infeasible DMU which will be added to set
    optStatus, overNum = checkOpt(constDuals, notset, fullsizeConstMatrix, smallSense)

    # redefining set if the model is not optimal
    if optStatus == false
      # adding the most infeasible DMU to set and deleting a DMU from set by the randomly selecting order
      # updating model
      reSampling(overNum, iterations, set, notset, smallConstMatrix, smallVarLB, smallVarUB, smallObjCoeff,
                 fullsizeConstMatrix, fullsizeVarLB, fullsizeVarUB, fullsizeObjCoeff)
    end
  end

  # Extracting solution
  if stat == :Optimal
    # recording objective value
    m.objVal = MathProgBase.getobjval(lm) + m.obj.aff.constant

    if modelForm == :Multiplier
      m.linconstrDuals = fill(0.0, fullsizeNumVar)
      solution = MathProgBase.getsolution(lm)

      # recording dual value
      m.linconstrDuals[set] = solution[1:length(set)]
      m.linconstrDuals[targetDMUIdx] = solution[length(set)+1]
      m.linconstrDuals[thetaIdx] = solution[length(set)+2]

      # recording value of variables
      m.colVal = try
          MathProgBase.getconstrduals(lm)[1:fullsizeNumConst]
      catch
          fill(NaN, fullsizeNumConst)
      end
    else
      m.colVal = fill(0.0, fullsizeNumVar)
      solution = MathProgBase.getsolution(lm)

      # recording value of variables
      m.colVal[set] = solution[1:length(set)]
      m.colVal[targetDMUIdx] = solution[length(set)+1]
      m.colVal[thetaIdx] = solution[length(set)+2]

      # recording dual value
      m.linconstrDuals = try
          MathProgBase.getconstrduals(lm)[1:fullsizeNumConst]
      catch
          fill(NaN, fullsizeNumConst)
      end
    end
  end

  return stat, iterations
end
