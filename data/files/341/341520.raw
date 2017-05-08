## Solve a linear dynamical system, dx/dt = A*x(t) + c(t)
function solve_linsys(A::Matrix{Float64},
                      x0::Vector{Float64},
                      ct::Matrix{Float64},
                      dt::Float64,
                      tmax::Float64)

    # Determine dimensions
    nx = length(x0)
    nt = 1 + int(tmax/dt)

    # Check inputs
    assert(nt == size(ct,2))
    assert(nx == size(A,1) == size(A,2) == size(ct,1))

    # Calculations needed for numerical integration
    Phi = expm(dt*A)
    Ainv = inv(A)

    # Solve system
    xt = zeros(nx,nt)
    xt[:,1] = x0
    for t = 1:(nt-1)
        xt[:,t+1] = Phi*xt[:,t] + Ainv*(Phi-1)*ct[:,t]
    end

    return xt
end

## Solve Boerlin spiking network
function solve_boerlin(A::Matrix{Float64}, # desired dynamics maxtrix (nx by nx)
                       Γ::Matrix{Float64}, # readout matrix (nx by N)
                       λd::Float64,        # synapse/readout decay rate
                       λV::Float64,        # membrane potential decay rate
                       ν::Float64,         # L1 penalty
                       μ::Float64,         # L2 penalty
                       c::Matrix{Float64}, # input to network (nx by nt)
                       dt::Float64,        # time step
                       tmax::Float64)      # length of simulation

    # Determine dimensions
    nx = size(Γ,1)      # number of states for the target linear system
    N  = size(Γ,2)      # number of neurons
    nt = 1+int(tmax/dt) # length of time vector

    # Check inputs
    assert(nx == size(A,1) == size(A,2) == size(c,1))
    assert(nt == size(c,2))

    # Calculate fast and slow synaptic weights
    Ωf = (Γ')*Γ + μ*(λd^2)*eye(N)
    Ωs = (Γ')*(A + λd*eye(nx))*Γ

    # Γ_i is the ith column of Γ, there are N columns of Γ, Γ_i is the effect of a spike for neuron i

    # Calculate spike thresholds for each neuron
    Thres = [ 0.5*(ν*λd + μ*λd^2 + norm(Γ[:,i])^2) for i = 1:N ]

    # Compute and store exponential synapse trace
    τ = 0.0
    h = [1.0]
    while h[end] > 1e-2
        τ += dt
        push!(h,exp(-λd*τ))
    end

    # Storage for system dynamics
    spk_ind = [(Int)[] for i=1:N] # list of spike indices for each neuron
    V = zeros(N,nt)      # membrane potential traces
    xhat = zeros(nx,nt)  # network readout trace

    # Main integration loop
    for t = 1:(nt-1)
        # Calculate fc[i] as the fast synaptic current onto each neuron, i
        fc = zeros(N) 
        for k = 1:N
            if V[k,t] > Thres[k]
                # Save spike index
                push!(spk_ind[k],t)

                # Add contribution to fast, recurrent synaptic currents
                for i = 1:N
                    fc[i] -= Ωf[i,k] 
                end

                # Add contribution to network readout
                for j = 1:nx
                    xhat[j,t] += Γ[j,k]
                end
            end

        end

        # Calculate sc[i] as the slow synaptic current onto each neuron, i
        sc = zeros(N)
        for k = 1:N
            # search backwards in time for spikes
            for u = 0:(length(spk_ind[k])-1)
                # z = number of time steps since the last spike
                z = t - spk_ind[k][end-u] + 1

                if z > length(h)
                    # All the spikes are too far in the past to care about, move to next neuron
                    break
                else
                    # Add synapses from neuron k -> i with activation h[z]
                    for i = 1:N
                        sc[i] += Ωs[i,k] * h[z]
                    end
                end
            end
        end

        # Update membrane potentials
        for i = 1:N
            # dVdt[i] = -λV*V[i,t] + sc[i] + dot(Γ[:,i],c[t])

            # Exponential-Euler integration for slow dynamics
            Vss = (sc[i] + dot(Γ[:,i],c[:,t])) / -λV # Steady-State for neuron i
            V[i,t+1] = Vss - (Vss - V[i,t])*exp(-dt/λV)

            # Then apply fast synaptic currents
            V[i,t+1] += fc[i]
        end

        # Update readout (decay term, spikes already taken into account)
        for j = 1:nx
            xhat[j,t+1] = -xhat[j,t] * exp(-dt/λd)
        end
    end

    # return
    return xhat,spk_ind,V
end
