#######################################################################
#    Script for testing sensitivities calculated using Sundials.jl    #
#                                                                     #
#     Sensitivity equations are solved with a finite difference       #
#         approximation to the Jacobian computed by Sundials.         #
#                               content                               #
#                                                                     #
#     The example is chosen to allow calculation of analytical        #
#         sensitivities for comparison. These are implemented         #
#                              as well.                               #
#                                                                     #
#     Christian Haargaard Olsen <christianhaargaard@gmail.com>        #
#                                                                     #
#######################################################################

using Sundials

# Uncomment this to use QT interface for PyPlot
using PyCall
@pyimport(matplotlib)
pygui(:qt)
using PyPlot


# First we create the datatype used for parsing parameter values to 
# the right-hand-side function rhs.
type UserData
  parameters :: Array{Float64, 1}
end
  

# using the function f(t) = a*sin(b*t), f(0) = 0, we create an ODE by differentiating 
# with respect to t, to get fdot (t) = a*b*cos(b*t). We will then use this ODE to test
# the sensitivity capabilities of sundials, as the correct sensitivites are given by
# f_a = sin(b*t) and f_b = a*t*cos(b*t).

function rhs(
  t         :: Float64,
  x         :: Sundials.N_Vector,
  xdot      :: Sundials.N_Vector,
  data
  )

  x         = Sundials.asarray(x)                 :: Array{Float64,1}
  xdot      = Sundials.asarray(xdot)              :: Array{Float64,1}
  user_data = unsafe_pointer_to_objref(data)      :: UserData

  a = user_data.parameters[1]
  b = user_data.parameters[2]

  x1 = x[1]
  xdot[1] = a*b*cos(b*t)

  return Int32(0)
end

function true_solution(
  t                                  :: Array{Float64,1},
  data                               :: UserData
  )

  a             = data.parameters[1] :: Float64
  b             = data.parameters[2] :: Float64
  result        = a*sin(b*t)         :: Array{Float64,1}

  return result
end

function true_sens(
  t                                  :: Array{Float64,1},
  data                               :: UserData
  )

  neq = 1
  NS = length(data.parameters)

  sens = zeros(length(t),neq,NS) 

  a             = data.parameters[1] :: Float64
  b             = data.parameters[2] :: Float64
  sens[:,1,1] =  sin(b*t)            :: Array{Float64,1}
  sens[:,1,2] =  t.*a.*cos(b*t)      :: Array{Float64,1}

  return sens
end

function load_states()
  return ([0.0], UserData([1.0,1.0,1.0]))
end

function calcsens_finitedif(parameters :: Array{Float64,1}; step = sqrt(1e-6))
  (x, data)                 = load_states()               :: Tuple{Array{Float64,1}, UserData}
  data.parameters           = parameters                  :: Array{Float64,1}
  xdot                      = zeros(x)                    :: Array{Float64,1}
  t                         = collect(linspace(0,10,101)) :: Array{Float64,1}
  (reltol, abstol,sens_tol) = (1e-8, 1e-6, 1e-6)          :: Tuple{Float64,Float64, Float64}
  neq                       = length(x)
  NS                        = length(parameters)

  sols = zeros(length(t),neq,NS) # No need to copy initial condition, they are already zero
  sens = zeros(length(t),neq,NS) # No need to copy initial condition, they are already zero

  (t0, y0, x) = runmodel(parameters)
  @printf("calculating finite difference sensitivities for %i parameters.\n",NS)
  for i in 1:NS
    newparameters = zeros(parameters)
    newparameters = copy(parameters)
    newparameters[i] = (1.0+step)*newparameters[i]
    (t0, sols[:,:,i], x) = runmodel(newparameters)
    sens[:,:,i] = (sols[:,:,i]-y0)/(step*parameters[i])
    @printf("Done for parameter %i.\n",i)
    end

  return (sens)
end

function runsens(parameters :: Array{Float64,1})
  (x, data)                 = load_states()               :: Tuple{Array{Float64,1}, UserData}
  data.parameters           = parameters                  :: Array{Float64,1}
  xdot                      = zeros(x)                    :: Array{Float64,1}
  t                         = collect(linspace(0,10,101)) :: Array{Float64,1}
  (reltol, abstol,sens_tol) = (1e-8, 1e-6, 1e-6)          :: Tuple{Float64,Float64, Float64}
  neq                       = length(x)
  NS                        = length(parameters)


  #######################################################################
  #                         ODE solver settings                         #
  #######################################################################
  
  #cvode_mem = Sundials.CVodeCreate(Sundials.CV_BDF, Sundials.CV_FUNCTIONAL)
  cvode_mem = Sundials.CVodeCreate(Sundials.CV_BDF, Sundials.CV_NEWTON)
  flag = Sundials.CVodeInit(cvode_mem,rhs, t[1], x)
  flag = Sundials.CVodeSetUserData(cvode_mem, data)
  flag = Sundials.CVodeSStolerances(cvode_mem, reltol, abstol)
  flag = Sundials.CVDense(cvode_mem, neq)


  # List of parameters for which to calculate sensitivities
  plist = round(Int32,1:NS)
  println(plist)

  # scaling of parameters
  pbar = copy(data.parameters)

  # Tolerances for solving sensitivities for each parameter
  #sens_tol_vec = [abstol :: Float64 for i in 1:NS]

  # IDEA: Maybe these should be scaled with parameter value?
  sens_tol_vec = [abstol*data.parameters[i] :: Float64 for i in 1:NS]

  # Sundials want a (pointer to a) vector where each component corresponds to 
  # a parameter, and where the element is a pointer to an array with a place for
  # each state variable. 
  ySJ    = Array(Array{Float64,1}, NS);
  for i in 1:NS
    ySJ[i] = zeros(Float64,neq)*1.0;
  end
  ySjulia = [Sundials.nvector(ySJ[i]) for i in 1:NS]
  yS = pointer(ySjulia)
  

  #######################################################################
  #                         Sensitivity settigs                         #
  #######################################################################
  
  sensi_meth = Int32(Sundials.CV_SIMULTANEOUS) # CV_SIMULTANEOUS, CV_STAGGERED or CV_STAGGERED1
  flag = Sundials.CVodeSensInit1(cvode_mem, NS, sensi_meth, 0, yS);
  flag = Sundials.CVodeSensEEtolerances(cvode_mem);
  flag = Sundials.CVodeSetSensErrCon(cvode_mem, 0);
  #flag = Sundials.CVodeSensSStolerances(cvode_mem, reltol, sens_tol_vec);
  flag = Sundials.CVodeSetSensDQMethod(cvode_mem, Sundials.CV_CENTERED, 0.0);
  flag = Sundials.CVodeSetSensParams(cvode_mem, data.parameters, 0, 0);


  # Placeholder for solution and sensitivities
  solution = zeros(length(t), neq)
  solution[1,:] = copy(x)
  sens = zeros(length(t),neq,NS) # No need to copy initial condition, they are already zero

  tout = [t[1]] # Set first output time

  # Loop through all the output times
  for k in 2:length(t)
    # Extract the solution to x, and the sensitivities to yS
    flag = Sundials.CVode(cvode_mem, t[k], x, tout, Sundials.CV_NORMAL)
    flag = Sundials.CVodeGetSens(cvode_mem, tout, yS)

    #Save the results
    solution[k,:] = x
    for i in 1:NS
      sens[k,:,i] = Sundials.asarray(unsafe_load(yS,i))
    end
  end

  return (solution,sens)
end

#######################################################################
#                          Plot results                               #
#######################################################################
 
t = collect(linspace(0,10,101));
(x, data) = load_states()

(solution, sens) = runsens(data.parameters)
senstrue = true_sens(t,data)

figure(1)
plot(t,sens[:,1,1])
plot(t,senstrue[:,1,1])
show()

figure(2)
plot(t,sens[:,1,2])
plot(t,senstrue[:,1,2])
show()
