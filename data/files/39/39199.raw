## Solver type for model fitting
immutable GradientSolver
  method::String  # SGD, SAG or Conjugate gradient
  stepSize::Float64 
  momentum::Float64 

  GradientSolver(m, s, mm) = 
    if ∉(m, ["SGD", "SAG", "CG"])
	  	error("Solver method must be \"SGD\", \"SAG\" or \"CG\"")
	  else 
	  	new(m, s, mm)
	  end 
end

solver() = GradientSolver("SGD", 0.1,0.0)
solver(method) = GradientSolver(method, 0.1,0.0)
solver(m, s, mm) = GradientSolver(m, s, mm)


## Model fitting options
immutable FitOptions
	solver::GradientSolver
	regularizer::String # L2Reg or maxNorm
	earlyStop::Bool 
	dropout::Bool
end

FitOptions() = FitOptions(solver(), "L2Reg", true, false)


## Regularizers 
immutable Regularizer 
	method::String 
	param::Float64

	Regularizer(m, p) = 
		if ∉(m, ["L2Reg", "MaxNorm"])
	  	error("Regularizer must be \"L2Reg\"or \"MaxNorm\"")
	  else 
	  	new(m, p)
	  end 
end



