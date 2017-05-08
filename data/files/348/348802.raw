#
# Solve the 2d wave equation using finite differencing
#
# @author arbennett
#

# Begin timing
#t_0 = time()

# Parameters for solving
const N = 50
const M = 50
const T = 6000
const dt = 0.1
const plot_frequency = 10
u = zeros(3,N,M)
f = open("solution.dat", "w")

# Set the initial conditions
for i=1:N
    for j=1:M
        u[2:3,i,j] = 1 + cos(2 * pi * (i/N)) + cos(2 * pi * (j/M))
        #u[3,i,j] = sin(2 * pi * ((i+1)/N)) + cos(2 * pi * ((j+1)/M))
    end
end

# Enforce boundary conditions
u[:,:,1] = u[:,:,2]
u[:,:,end] = u[:,:,end-1]
u[:,1,:] = u[:,2,:]    
u[:,end,:] = u[:,end-1,:]

# Do some timestepping
for t=1:int(T)    
    # Calculate the new u
    u[1,2:end-1,2:end-1] = (2*u[2,2:end-1,2:end-1] - u[3,2:end-1,2:end-1] + 
        dt^2 * (u[2,2:end-1,1:end-2] + u[2,2:end-1,3:end] + u[2,1:end-2,2:end-1] 
        + u[2,3:end,2:end-1] - 4*u[2,2:end-1,2:end-1]))

    # Enforce boundary conditions
    u[:,:,1] = u[:,:,2]
    u[:,:,end] = u[:,:,end-1]
    u[:,1,:] = u[:,2,:]
    u[:,end,:] = u[:,end-1,:]

    # Move the time forwards
    u = circshift(u,[1,0,0])
    if mod(t, plot_frequency) == 0
        writedlm("out/solution.dat."*lpad(string(t),length(string(int(T))),"0"), u[1,:,:]) 
    end
end

# Report the time taken
#t_1 = time()
#println("Time elapsed: ", t_1 - t_0, "s")

