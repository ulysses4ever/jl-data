## Functions
# K channel
function alpha_n(v)
    if v != 10
        return 0.01*(-v + 10)/(exp((-v + 10)/10) - 1)
    else
        return 0.1
    end
end

function beta_n(v)
    return 0.125*exp(-v/80)
end

function n_inf(v)
    return alpha_n(v)/(alpha_n(v) + beta_n(v))
end

# Na channel (activating)
function alpha_m(v)
    if v != 25
        return 0.1*(-v + 25)/(exp((-v + 25)/10) - 1)
    else
        return 1
    end
end

function beta_m(v)
    return 4*exp(-v/18)
end

function m_inf(v)
    return alpha_m(v)/(alpha_m(v) + beta_m(v))
end

# Na channel (inactivating)
function alpha_h(v)
      return 0.07*exp(-v/20)
end

function beta_h(v)
    return 1/(exp((-v + 30)/10) + 1)
end

function h_inf(v)
    return alpha_h(v)/(alpha_h(v) + beta_h(v))
end

### Channel Activity ###

## setup parameters and state variables
T     = 55    # ms
dt    = 0.025 # ms
L     = 1     # mm
dl    = 0.001 # mm
time  = linspace(0,T+dt,int(T/dt))
space = linspace(0,L+dl,int(L/dl))

## HH Parameters
V_rest  = 0      # mV
Cm      = 1      # uF/cm2
gbar_Na = 120    # mS/cm2
gbar_K  = 36     # mS/cm2
gbar_l  = 0.3    # mS/cm2
E_Na    = 115    # mV
E_K     = -12    # mV
E_l     = 10.613 # mV

Vm      = zeros((size(time)[1],size(space)[1])) # mV
Vm[1,:] = V_rest
m       = m_inf(V_rest)      
h       = h_inf(V_rest)
n       = n_inf(V_rest)

## Stimulus
I = zeros(size(time))
for (i, t) = enumerate(time)
  if ((5 <= t) && (t<= 30))
    I[i] = 10 # uA/cm2
  end
end

## Simulate Model
for (i,t) = enumerate(time)
  if (i>1)
    #calculate conductances
    g_Na = gbar_Na*(m^3)*h
    g_K  = gbar_K*(n^4)
    g_l  = gbar_l
    
    #calculate gating variables
    m += (alpha_m(Vm[i-1,1])*(1 - m) - beta_m(Vm[i-1,1])*m) * dt
    h += (alpha_h(Vm[i-1,1])*(1 - h) - beta_h(Vm[i-1,1])*h) * dt
    n += (alpha_n(Vm[i-1,1])*(1 - n) - beta_n(Vm[i-1,1])*n) * dt

    #calculate voltage
    Vm[i,1] = Vm[i-1,1] + (I[i-1] - g_Na*(Vm[i-1,1] - E_Na) - g_K*(Vm[i-1,1] - E_K) - g_l*(Vm[i-1,1] - E_l)) / Cm * dt
  end
end

print(Vm)
