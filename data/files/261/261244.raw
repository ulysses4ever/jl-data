using NonLinearDSGE

# Create model
m = DSGE(10,1,1)

# Define parameters and parameter values
@parameter m ρ 0.9

# Define exogenous variables
@exogVariable m a 1

# Define distribution of shocks
@shock m ϵ Normal(0,0.1)

# Define equations
@exogEquation m a[t+1] = a[t]^ρ*exp(ϵ)

solve!(m)
