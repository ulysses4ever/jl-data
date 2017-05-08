module NonLinearDSGE

using Distributions
using Base.Meta

export  DSGE,
        @parameter,
        @shock,
        @exogenousVariable,
        @endogenousVariable,
        @stateVariable,
        @exogenousEquation,
        @endogenousEquation,
        @stateEquation,
        solve!

# This type holds the details for the model to be solved.
# There is an external constructor that only requires specifying the length
# of the simulation.
abstract Polynomial

type OrdinaryPolynomial <: Polynomial
  degree::Int
  equation::Expr
  coefficients::Array{Float64,1}
end

type DSGE
  simulationLength::Int
  maxLag::Int
  maxLead::Int
  timeIterator::Symbol
  parameters::Dict{Symbol,Float64}
  shocks::Dict{Symbol, Distribution{}}
  exogenousVariables::Dict{Symbol,Array{Float64,1}}
  exogenousEquations::Array{Expr}
  endogenousVariables::Dict{Symbol,Array{Float64,1}}
  endogenousEquations::Array{Expr}
  stateVariables::Dict{Symbol,Array{Float64,1}}
  stateEquations::Array{Expr}
  simulation_function!::Function
  approximatingEquation::Polynomial
end

# External constructor for the DSGE type. Returns type DSGE.
function DSGE(simulationLength::Int, maxLag::Int, maxLead::Int)
  m = DSGE( simulationLength,
            maxLag,
            maxLead,
            :t, #timeIterator
            Dict{Symbol, Float64}(), #parameters
            Dict{Symbol, Distribution{VariateForm, ValueSupport}}(), #shocks
            Dict{Symbol, Array{Float64,1}}(), #exogenousVariables
            Expr[], #exogenousEquations
            Dict{Symbol, Array{Float64,1}}(), #endogenousVariables
            Expr[], #endogenousEquations
            Dict{Symbol, Array{Float64,1}}(), #stateVariables
            Expr[], #stateEquations
            () -> nothing, #simulation_function!
            OrdinaryPolynomial(0,Expr(:nothing),Float64[])
            )
  return m
end

function alterSymbols(model, ex)
  for (index, arg) in enumerate(ex.args)
    if isa(arg, Symbol)
      if haskey(model.parameters, arg)
        ex.args[index] = Expr(:ref, :parameters, quot(arg))
      elseif haskey(model.exogenousVariables, arg)
        ex.args[index] = Expr(:ref, :exogenousVariables, quot(arg))
      elseif model.timeIterator == arg
        ex.args[index] = :timeIterator
      elseif haskey(model.shocks, arg)
        ex.args[index] = Expr(:call, :rand, Expr(:ref, :shocks, quot(arg)))
      elseif haskey(model.endogenousVariables, arg)
        ex.args[index] = Expr(:ref, :endogenousVariables, quot(arg))
      elseif haskey(model.stateVariables, arg)
        ex.args[index] = Expr(:ref, :stateVariables, quot(arg))
      end
    elseif isa(arg, Expr)
      alter_symbols(model, arg)
    end
  end

  return ex
end

############################################################
# Macros to set parameters, variables and equations for the
# model. Done via macros so the expressions/symbols aren't
# evaluated.
############################################################

# Define parameters for the model.
macro parameter(model, name, value)
  model = esc(model)
  model = Expr(:., model, quot(:parameters))
  name = quot(name) # Ensure name is a symbol when passed back
  quote
    $model[$name] = $value
  end
end

# Define the exogenous variables
macro exogenousVariable(model, name, values...)
  model = esc(model)
  simulationLength = Expr(:., model, quot(:simulationLength))
  maxLag = Expr(:., model, quot(:maxLag))
  maxLead = Expr(:., model, quot(:maxLead))

  model = Expr(:., model, quot(:exogenousVariables))
  name = quot(name)

  quote
    $model[$name] = zeros($simulationLength + $maxLead + $maxLag)
    startingValue = $maxLag + 1 - length($values)
    for i in 1:length($values)
      $model[$name][startingValue + i] = $values[i]
    end
  end
end

# Define endogenous variables
macro endogenousVariable(model, name)
  model = esc(model)
  simulationLength = Expr(:., model, quot(:simulationLength))
  maxLag = Expr(:., model, quot(:maxLag))
  maxLead = Expr(:., model, quot(:maxLead))

  model = Expr(:., model, quot(:endogenousVariables))
  name = quot(name)

  quote
    $model[$name] = zeros($simulationLength + $maxLead + $maxLag)
  end
end

macro stateVariable(model, name, values...)
  model = esc(model)
  simulationLength = Expr(:., model, quot(:simulationLength))
  maxLag = Expr(:., model, quot(:maxLag))
  maxLead = Expr(:., model, quot(:maxLead))

  model = Expr(:., model, quot(:stateVariables))
  name = quot(name)

  quote
    $model[$name] = zeros($simulationLength + $maxLead + $maxLag)
    startingValue = $maxLag + 1 - length($values)
    for i in 1:length($values)
      $model[$name][startingValue + i] = $values[i]
    end
  end
end

# Define shocks
# Uses distributions from the Distributions package.
macro shock(model, sym, dist)
    model = Expr(:., esc(model), quot(:shocks))
    sym = quot(sym)
    quote
        $model[$sym] = $dist
    end
end

# Define exogenous equations for the model
macro exogenousEquation(model, equation)
  # Quote equation so it isn't executed in calling environment
  model = esc(model)
  equation = quot(equation)
  # Turn model into reference to exog_eq array of the model
  arr = Expr(:., model, quot(:exogenousEquations))
  #alter_call = Expr(:call, alter_symbols, model, equation)
  #push_call = Expr(:call, :push!, arr, alter_call)
  quote
    #$push_call
    push!($arr, alterSymbols($model, $equation))
  end
end

macro endogenousEquation(model, equation)
  # Quote equation so it isn't executed in calling environment
  model = esc(model)
  equation = quot(equation)
  # Turn model into reference to exog_eq array of the model
  arr = Expr(:., model, quot(:endogenousEquations))
  #alter_call = Expr(:call, alter_symbols, model, equation)
  #push_call = Expr(:call, :push!, arr, alter_call)
  quote
    #$push_call
    push!($arr, alterSymbols($model, $equation))
  end
end

macro stateEquation(model, equation)
  # Quote equation so it isn't executed in calling environment
  model = esc(model)
  equation = quot(equation)
  # Turn model into reference to exog_eq array of the model
  arr = Expr(:., model, quot(:stateEquations))
  #alter_call = Expr(:call, alter_symbols, model, equation)
  #push_call = Expr(:call, :push!, arr, alter_call)
  quote
    #$push_call
    push!($arr, alterSymbols($model, $equation))
  end
end


function solve!(model)
  ###############
  # Part 1: Simulate exogenous variables
  ###############

  # Alter equations to point to model explicitly
  @eval begin
          function simulation_function!(model)
            params = model.params
            exog_vars = model.exog_vars
            shocks = model.shocks

            for _time_iterator = (1+model.max_lag):(model.T-model.max_lead)
              $(model.exog_eq...)
            end

            model.exog_vars = exog_vars
          end
        end
  #
  model.simulation_function! = simulation_function!
  model.simulation_function!(model)
end

# Module end
end
