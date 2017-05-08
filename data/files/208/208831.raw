
export optimizePolarization, annealPolarization, optimizePhase2D
# Methods for fitting triplet signals
import Optim


####################### Generalized fitting method ################
function genPolarization(B0::Real, 
                              field::Vector, 
                              spect::Vector, 
                              d::Real, 
                              e::Real, 
                              guess::Vector, 
                              pgen::Function,
                              optimizer::Function,
                              steps::Int = 50)
                                          
  assert(length(guess) == 3)
  
  # Clean up our types
  field = convert(Vector{Float64}, field)
  spect = convert(Vector{Float64}, spect)
  guess = convert(Vector{Float64}, guess)
  
  thetaphi = getThetaPhi(guess...)
  count = 0
                                          
  function f(p::Vector)
    scale = p[1]
    xyz = getXYZ(p[2:]...)
    sim = scale*tripletPowder(B0, field, d, e, pgen(xyz...), steps = steps)
    diff = spect - sim
    squares =  diff'*diff
    if count % 10 == 0
      println("Iteration $count, Sum of squares: $squares")
    end
    count += 1
    return squares[1]   # Get it out of the 1x1 array
  end
  
  result = optimizer(f, append!([1.0], thetaphi))
  result.minimum = append!([result.minimum[1]], getXYZ(result.minimum[2:]...))
  return result
end

####################### Fitting methods ###########################
function optimizePolarization(B0::Real, 
                              field::Vector, 
                              spect::Vector, 
                              d::Real, 
                              e::Real, 
                              guess::Vector, 
                              pgen::Function = SOPolarizedOcupation;
                              steps::Int = 50)
                                          
  
  result = genPolarization(B0::Real,field,spect,d,e,guess,pgen,Optim.optimize, steps)
  println("Found result: $result")
  return result
end

function annealPolarization(B0::Real, 
                              field::Vector, 
                              spect::Vector, 
                              d::Real, 
                              e::Real, 
                              guess::Vector,
                              pgen::Function = SOPolarizedOcupation;
                              iterations::Int = 1000,
                              starttemp::Real = 2.0,
                              steps::Int = 50)
  
  # Scale the iterations so that we still anneal to a reasonably low temperature, in this case 0.2
  #iterationTemp(iteration::Real) = Optim.log_temperature(iteration*100000/iterations)
  iterationTemp(iteration::Real) = starttemp*(1.0-iteration/iterations)
  anneal(f, guess) = Optim.simulated_annealing(f, guess, iterations = iterations, temperature = iterationTemp)
  
  result = genPolarization(B0::Real,field,spect,d,e,guess,pgen,anneal, steps)
  println("Found result: $result")
  return result
end

function optimizePhase2D(data::Array, t0::Int, startpoint::Int, endpoint::Int, guess::Vector = [0.0, 0.0])
    function f(phases)
      phase0, phase1 = phases
      workedup = fix2DTrace(data, t0, startpoint, endpoint, phase0 = phase0, phase1 = phase1)

      #plot(field, I, label = "Experimental $phase")
      diff = imag(workedup)
      squares = (diff'*diff)[1]
      println("Sum of squares: $squares at [$phase0, $phase1]")
      
      return squares
    end

    result = Optim.optimize(f, guess)
    return result
    
end
