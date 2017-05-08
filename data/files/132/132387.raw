# Model behavior of predator vs prey using the Lotka-Volterra equation. This
# example shows how to deal with two first-order nonlinear DEs. The rate of
# change of the predator population is inversely proportional to the prey
# population.

# Time Parameters [yrs]
t_start = 0
t_end = 100
dt = 0.25
nt_end = int( (t_end - t_start) / dt )

# Initial Conditions
prey_start = 30000
predator_start = 20

# Relationship between prey and predators (i.e. how many prey must be killed
# before a predator is born)
dPrey_dPredator = 100

# Probability that prey will cross paths with predator
p_meet = 0.02

# Probability that prey will be eaten when crossing paths with a predator
p_kill = 0.50

# Prey growth rates [1/yr]
gr_prey = 0.20

# Predator death rates [1/yr]
dr_predator = 0.10

# Initialize - Here, fill() will fill an array with the value "0.0" with
# dimensions "t_end + 1"
prey_over_time = fill(0.0, nt_end + 1)
predators_over_time = fill(0.0, nt_end + 1)
model_time = fill(0.0, nt_end + 1)

prey = prey_start
predators = predator_start

prey_over_time[1] = prey
predators_over_time[1] = predators

# Run Solver
for sim_step = 1:nt_end
  # Get time step
  sim_time = t_start + sim_step * dt
  model_time[sim_step] = sim_time

  # Calculate flow rates
  prey_births = prey * gr_prey
  prey_deaths = min(prey, p_kill * p_meet * predators * prey)

  predator_births = 1 / dPrey_dPredator * prey_deaths
  predator_deaths = predators * dr_predator

  # Update populations
  predators = predators + predator_births - predator_deaths
  prey = prey + prey_births - prey_deaths

  predators_over_time[sim_step + 1] = predators
  prey_over_time[sim_step + 1] = prey
end

# Strings are concatanated using *. Numbers are typecast to strings using
# the string() operator.
println("Time, Prey, Predators")
for i = 1:nt_end
  output = string(model_time[i]) * ", " * string(prey_over_time[i]) * ", " *
    string(predators_over_time[i])

  println(output)
end
