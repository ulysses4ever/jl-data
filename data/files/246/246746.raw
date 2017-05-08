function MorrisLecar(state,forcing, externalField) #state = [V,W] at the present time
  # The parameters for the system
  #(V,N) = state
  # adjust the voltage based on the current state of the externalField; this may
  # be subject to change
  state[1]+=externalField
  Cm = 20 #μF/cm^2
  gK = 8 #mS/cm^2
  gL = 2 #mS/cm^2
  gCa = 4 #mS/cm^2 #see fig 1/table 2 in Tsumoto et al 2005
  VCa = 120 #mV
  VK = -80 #mV
  VL = -60 #mV
  V1 = -1.2 #mV potential where M is half-activated
  V2 = 18 #mV slope of activation voltage
  V3 = 12 #mV potential where the potassium current is half-activated
  V4 = 17.4 #mV
  ϕ = 1/15
  M∞ = .5*(1+tanh((state[1]-V1)/V2))
  N∞ = .5*(1+tanh((state[1]-V3)/V4))
  τN = 1/ϕ*sech((state[1]-V3)/2/V4)
  IL = -gL*(state[1]-VL)
  ICa = -gCa*M∞*(state[1]-VCa)
  IK = -gK*state[2]*(state[1]-VK)
  derivative = [1/Cm*(IL + ICa + IK + forcing), (N∞-state[2])/τN]
  return derivative
end
r=0
if r==0
  println(r)
end
r!=3

function findSteadyState(model,maxIter=10000,ϵ=1e-3, state, Forcing, externalField, Δt = .01)
  totstat=[state]
  prevState = 0
  for i=1:maxIter
    update = model(state,Forcing,externalField)
    state += Δt*update
    totstat = hcat(totstat,state)
    # We've returned to the same Voltage with a positive derivative
    if state[0]==-30 && update[0] >= 0
      #We're accurate enough to exit
      if prevState!=0 && norm(prevState-state,2)<ϵ

      end
      # Record it to compare next time
      prevState = state
    end

end




# These functions are included as a way of getting around rdiff's issues with multivariate functions
function MorrisLecar1(state,forcing, externalField) #state = [V,W] at the present time
  # The parameters for the system
  #(V,N) = state
  # adjust the voltage based on the current state of the externalField; this may
  # be subject to change
  state[1]+=externalField
  Cm = 20 #μF/cm^2
  gK = 8 #mS/cm^2
  gL = 2 #mS/cm^2
  gCa = 4 #mS/cm^2 #see fig 1/table 2 in Tsumoto et al 2005
  VCa = 120 #mV
  VK = -80 #mV
  VL = -60 #mV
  V1 = -1.2 #mV potential where M is half-activated
  V2 = 18 #mV slope of activation voltage
  V3 = 12 #mV potential where the potassium current is half-activated
  V4 = 17.4 #mV
  ϕ = 1/15
  M∞ = .5*(1+tanh((state[1]-V1)/V2))
  N∞ = .5*(1+tanh((state[1]-V3)/V4))
  τN = 1/ϕ*sech((state[1]-V3)/2/V4)
  IL = -gL*(state[1]-VL)
  ICa = -gCa*M∞*(state[1]-VCa)
  IK = -gK*state[2]*(state[1]-VK)
  return 1/Cm*(IL + ICa + IK + forcing)
end
function MorrisLecar2(state,forcing, externalField) #state = [V,W] at the present time
  # The parameters for the system
  #(V,N) = state
  # adjust the voltage based on the current state of the externalField; this may
  # be subject to change
  state[1]+=externalField
  Cm = 20 #μF/cm^2
  gK = 8 #mS/cm^2
  gL = 2 #mS/cm^2
  gCa = 4 #mS/cm^2 #see fig 1/table 2 in Tsumoto et al 2005
  VCa = 120 #mV
  VK = -80 #mV
  VL = -60 #mV
  V1 = -1.2 #mV potential where M is half-activated
  V2 = 18 #mV slope of activation voltage
  V3 = 12 #mV potential where the potassium current is half-activated
  V4 = 17.4 #mV
  ϕ = 1/15
  M∞ = .5*(1+tanh((state[1]-V1)/V2))
  N∞ = .5*(1+tanh((state[1]-V3)/V4))
  τN = 1/ϕ*sech((state[1]-V3)/2/V4)
  IL = -gL*(state[1]-VL)
  ICa = -gCa*M∞*(state[1]-VCa)
  IK = -gK*state[2]*(state[1]-VK)
  return (N∞-state[2])/τN
end