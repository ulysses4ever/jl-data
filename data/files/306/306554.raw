# Model Lion & Zebra (predetor vs. prey) over the course of 100 years.

# Using Lotka-Volterra equation, we have:
# dx/dt=x(α−βy)  dy/dt=−y(γ−δx)

start_time = 0;
end_time = 100;

# How much time passes between each successive calculation
time_step = 1/4 # In years
end_step = int(((end_time - start_time)/ time_step));

# The number of zebras when the simulation is started
initial_zebras = 30000;

# The number of lions when the simulation is started
initial_lions = 15;

# The number of zebras that must be killed for a lion to be born. (Zebras / Lion)

zebras_per_lion = 1000;

# The chance a zebra will die when a zebra lion cross paths
fighting_chance = 0.50;

meeting_chance = 0.02;

zebra_growth_rate = 0.20;

lion_death_rate = 0.10;

# Initialization

zebras_over_time = fill(0.0, end_step+1);
lions_over_time = fill(0.0, end_step+1);
model_time = fill(0.0, end_step+1);

zebras = initial_zebras;
lions = initial_lions;

zebras_over_time[1]	= zebras;
lions_over_time[1] = lions;


# Run the model

for sim_step = 1:end_step

	sim_time = start_time + sim_step * time_step;
	model_time[sim_step] = sim_time;

	# First we must calculate our flows (our rates)
	zebra_births = zebras * zebra_growth_rate;
	zebra_deaths  = min(zebras, meeting_chance*fighting_chance*zebras*lions);

	lion_births = 1/zebras_per_lion * zebra_deaths;
	lion_deaths = lions * lion_death_rate;

	# Update the stock levels
	zebras = zebras + zebra_births - zebra_deaths;
	lions = lions + lion_births - lion_deaths

	# Stock values always update in the next time step
	zebras_over_time[sim_step+1] = zebras;
	lions_over_time[sim_step+1] = lions;
end

println("Time, Zebras (Thousands), Lions");

for i = 1:end_step
	print(model_time[i]);
	print(",");
	print(zebras_over_time[i]/1000);
	print(",");
	println(lions_over_time[i]);
end
