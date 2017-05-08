push!(LOAD_PATH, ".")

# Simple 2d simulation of charged particle diffusion and coulomb repulsion
# Primary Purpose:
# Learn Julia and Julias Package system, test reimplemenation of Barnes-Hut Method in 2d


import ChargedParticleVisualization_PyPlot
import ChargedParticleVisualization_Gadfly
import ChargedParticleVisualization_BTree
using ChargedParticle_Base
using ChargedParticle_BTree

type ChargedParticleCapillarySimulation
  particles::Array{ChargedParticle,1}
  positions::Array{Float64,2}
  diffusionCoefficient::Float64
  Q::Float64
  c_R_m::Float64
  c_L_m::Float64
  zVelocityFunction::Function
  meanVelocity::Float64
end

ChargedParticleCapillarySimulation(nParticles,diffusionCoefficient,charge) = ChargedParticleCapillarySimulation(
  [ChargedParticle([0.0,0.0,0.0],charge) for i = 1:nParticles],
  zeros(3,nParticles),
  diffusionCoefficient,
  0.0,
  0.0,
  0.0,
  (z,r)->0,
  0.0
  )


function initSim(nParticles,diffusionCoefficient,charge)
  sim = ChargedParticleCapillarySimulation(nParticles,diffusionCoefficient,charge)
  return sim
end

function initDiscParticleCloud(sim,radius)
  for part in sim.particles
    R = rand()*radius
    phi = rand()*pi*2
    part.location=[R*cos(phi),R*sin(phi),0.0]
  end
  updatePositionsFromParticleCloud(sim)
end


function updatePositionsFromParticleCloud(sim)
  #sim.positions = zeros(3,length(sim.particles))
  for i in eachindex(sim.particles)
    if sim.particles[i].active == true
      sim.positions[:,i] = sim.particles[i].location
    end
  end
end

function diffuseParticlesOnXYPlane(part,diffusionCoefficient,dt)
    phi = rand()*2*pi
    dL = sqrt(4*dt*diffusionCoefficient)
    part.location[1]+= dL*cos(phi)
    part.location[2]+= dL*sin(phi)
end

function rPos(part)
  sqrt(part.location[1]^2.0 + part.location[2]^2.0)
end

function transportInZFlow(part,sim,dt)
  part.location[3]+= sim.zVelocityFunction(part.location[3],rPos(part))*dt
end

function collisonCapillaryWalls(part,sim)
  if (rPos(part) > sim.c_R_m)
    part.active = false
  end
end

function crossectionArea(sim)
  pi * sim.c_R_m^2.0
end

function laminarIncompressibleVelocityProfile(sim,Q)
        sim.meanVelocity = Q/crossectionArea(sim)
        sim.zVelocityFunction =
          function(z,r)
            2.0*sim.meanVelocity *(1-(r/sim.c_R_m)^2.0)
          end
end


function coulombRepulsion(part::ChargedParticle,eField::Array{Float64,1},dt::Float64)
  part.location+= eField*part.charge*part.mobility*dt
end

function runSim(ts=100,nParticles=10000;
                diffusionCoefficient = 5e-6,
                charge=1.0,
                flow=1.0,
                plotRate=20,
                doDiffusion=true,
                doBuildTree=true,
                doCalcEField=0)
  dt = 0.5e-5
  sim = initSim(nParticles,diffusionCoefficient,charge)
  sim.c_R_m = 5/1000.0/2.0
  sim.c_L_m = 16/100.0
  #initDiscParticleCloud(sim,sim.c_R_m*0.9)
  initDiscParticleCloud(sim,sim.c_R_m*0.2)
  #laminarIncompressibleVelocityProfile(sim,1.0/60000.0)

  treeMin = [-sim.c_R_m*2,-sim.c_R_m*2,0]
  treeMax = [ sim.c_R_m*2, sim.c_R_m*2,0]
  for i=0:ts
    if doBuildTree
      tree = BTree(treeMin,treeMax)
      for part in sim.particles
        #println("inserting particle:"*string(part))
        insertParticle(tree.root,part)
      end
      computeChargeDistribution(tree.root)
    end

    for part in sim.particles
      if part.active == true
        if doDiffusion
          diffuseParticlesOnXYPlane(part,diffusionCoefficient,dt)
        end
        transportInZFlow(part,sim,dt)
        if doCalcEField==1
          eField = calculateEFieldFromTree(tree.root,part)
          #print(eField)
          coulombRepulsion(part,eField,dt)
        end
        if doCalcEField==2
          eField = calculateEFieldFromTreeOpt(tree.root,part)
          #print(eField)
          coulombRepulsion(part,eField,dt)
        end

        collisonCapillaryWalls(part,sim)
      end
    end
    updatePositionsFromParticleCloud(sim)

    if i % plotRate == 0
      #ChargedParticleVisualization_BTree.plotBTree(tree,"treeTest_"*@sprintf("%05d", i))
      #ChargedParticleVisualization_PyPlot.plotParticlesXY(sim,"test_"*@sprintf("%05d", i))
      #ChargedParticleVisualization_PyPlot.plotParticles3d(sim,"test3d_"*@sprintf("%05d", i),sim.c_L_m/5)
      ChargedParticleVisualization_Gadfly.plot2dHistogramXY(sim,"testHist_XY_"*@sprintf("%05d", i))
      ChargedParticleVisualization_Gadfly.plot2dHistogramXZ(sim,"testHist_XZ_"*@sprintf("%05d", i))
    end
    if i % 1 == 0
      print(string(i)*"\n")
    end
  end
end

#runSim(100,1000,)

