
using PyPlot

function test()
  println(Tripletsim.scaledFieldHamiltonian(1,2,3,4))
  println(Tripletsim.D(1,2))
  println(Tripletsim.rotationMatrix(0,0))
  println(Tripletsim.qRotation(1,2))
  println(Tripletsim.zeroFieldVectors(0,0,1))
  println(Tripletsim.SOPolarizedAmplitude(0,0,1)(1,1))
end

function runsim()
  d = 461.0 - 15
  e = 47.0 + 15
  field = linspace(2500,4500,200)
  result = Tripletsim.RunSim(3400, field, d, e, Tripletsim.SOPolarizedOcupation(0.10, 0.20, 0.20))
  plot(field, result)
  readline(STDIN)  
  
  for i = 1:30
    println("Running step $i")
    Tripletsim.RunSim(3400, field, d, e, Tripletsim.SOPolarizedOcupation(0.10, 0.20, 0.20), steps = 50)
  end
  
end

function opt()
B0 = 3400.0
  d = 461.0 - 15
  e = 47.0 + 15
  field::Vector{Float32} = linspace(2500,4500,200)
  result = Tripletsim.RunSim(B0, field, d, e, Tripletsim.SOPolarizedOcupation(1/3, 2/3, 2/3))
  plot(field, result)
  
  sim = Tripletsim.OptimizePolarization(B0, field, result, d, e, [0.0, 1.0, 0.0]).minimum
  polarization = Tripletsim.SOPolarizedOcupation(sim...)
  result = Tripletsim.RunSim(B0, field, d, e, polarization, steps = 50)
  println("Polarization: $sim")
  plot(field, result)
  readline(STDIN)
end

function papersim()
  B0 = 3500.0
  d = waveToGauss(629)
  e = waveToGauss(172)
  p = [0.50 0.00 0.50]
  #p = [0.42 0.58 0.00]
  
  field::Vector{Float32} = linspace(2600, 4400, 256)
  
  polarization = Tripletsim.SOPolarizedOcupation(p...)
  result = Tripletsim.RunSim(B0, field, d, e, polarization, steps = 200)
  plot(field, result)
  readline(STDIN)
end

#test()
#runsim()
#opt()
#papersim()
