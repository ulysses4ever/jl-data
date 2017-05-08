include("KineticsReactions.jl")
include("ControlReactions.jl")

function Balances(t,x,data_dictionary)

  idx_small = find(x.<0)
  x[idx_small] = 0.0
	#@show x
  #@show t

  # Call my kinetics function -
  rate_array = KineticsReactions(t,x,data_dictionary)
   #@show x[7] #currently all zero-why?

  # Call my control function -
  control_array = ControlReactions(t,x,data_dictionary)
	#@show x[7] #fine, nonzero
  # Compute the modified rate -
  rate_array = rate_array.*control_array;

  dxdt_array = zeros(18)

  # define the balance equations -
  dxdt_array[1]  = -rate_array[2]-rate_array[1]                    # 1 Prothrombin FII
  dxdt_array[2]  = rate_array[2]+rate_array[1]-rate_array[4]       # 2 thrombin FIIa
	#@show t, rate_array[2],rate_array[1], rate_array[4]
  dxdt_array[3]  = -rate_array[3]                                  # 3 PC
  dxdt_array[4]  = rate_array[3]-rate_array[14]                    # 4 APC
  dxdt_array[5]  = -rate_array[4]                                  # 5 ATIII
  dxdt_array[6]  = 0.0                                             # 6 TM acts as an enzyme
  dxdt_array[7]  = 0.0                                             # 7 Trigger
  dxdt_array[8] = rate_array[9]-rate_array[12]                     # 8 Fibrin
  dxdt_array[9] = rate_array[10]+rate_array[11]-rate_array[13]     # 9 Plasmin
  dxdt_array[10] = -rate_array[5] - rate_array[18]                 # 10 Fibrinogen
  dxdt_array[11] = -rate_array[10] - rate_array[11]                # 11 Plasminogen
  dxdt_array[12] = -rate_array[15]                                 # 12 tPA
  dxdt_array[13] = -rate_array[16]                                 # 13 uPA
  dxdt_array[14] = 1.0(rate_array[5]-rate_array[6])                 # 14 Fibrin monomer
  dxdt_array[15] = rate_array[6]+rate_array[8]-rate_array[7]       # 15 Protofibril
  dxdt_array[16] = -rate_array[13]                                 # 16 Antiplasmin
  dxdt_array[17] = -rate_array[14]-rate_array[15]-rate_array[16]   # 17 PAI_1
  dxdt_array[18] = 1.0*(rate_array[7]-rate_array[9]-rate_array[17])# 18 Fibers

	#@show dxdt_array
  return dxdt_array
end
