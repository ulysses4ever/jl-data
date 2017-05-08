push!(LOAD_PATH, ".")
using ChargedParticleSimulator_2d
using ProfileView

runSim(200,3000,doDiffusion=true,doBuildTree=true,doCalcEField=1,plotRate=2000,charge=1e8)
@profile runSim(200,3000,doDiffusion=true,doBuildTree=true,doCalcEField=1,plotRate=2000,charge=1e8)
ProfileView.view()
