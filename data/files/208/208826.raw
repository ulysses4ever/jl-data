####################### Fitting methods ###########################
function OptimizePolarization{T1 <: Real,T2 <: Real}(B0::Real, 
                                          field::Vector{T1}, 
                                          spect::Vector{T2}, 
                                          d::Real, 
                                          e::Real, 
                                          guess::Vector, 
                                          pgen::Function = SOPolarizedOcupation; 
                                          steps::Integer = 75)
                                          
  assert(length(guess) == 3)
  count = 0
  
  thetaphi = getThetaPhi(guess...)
                                          
  function f(p::Vector)
    xyz = getXYZ(p...)
    sim = RunSim(B0, field, d, e, pgen(xyz...), steps = steps)
    diff = spect - sim
    squares =  diff'*diff
    count += 1
    if count % 10 == 0
      println("Sum of squares: $squares")
    end
    return squares[1]
  end
  
  result = Optim.optimize(f, thetaphi)
  println("Found result: $result")
  result.minimum = getXYZ(result.minimum...)
  return result
end
