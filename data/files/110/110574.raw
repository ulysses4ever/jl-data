module Ecosystem

export initialize_grid,
       calculate_ecosystem,
       display_ecosystem

include("Constants.jl");



###############################################################################
#                                UTILITIES                                    #
###############################################################################



"""
Return a string hex value of an RGB color
"""
function rgb_to_hex_string(r::Int, g::Int, b::Int)
	c = hex((1 << 24) + (r << 16) + (g << 8) + b)[2:end];
	return "#$c";
end


"""
Appends all values to a string
"""
function display_ecosystem(ecosystem::Array{Int,3})
	visual = String[];
	for i = 1:HEIGHT
		for j = 1:WIDTH
			r = ecosystem[i,j,FEAR];
			g = ecosystem[i,j,GREED];
			b = ecosystem[i,j,SOCIAL];
			push!(visual, rgb_to_hex_string(r,g,b));
		end
	end
	return visual;
end



"""
Bounds a value to within the set upper and lower bounds
"""
function bound(value::Int, lower::Int, upper::Int)
	if value > upper
		return upper;
	elseif value < lower
		return lower;
	else
		return value;
	end
end



###############################################################################
#                          ENVIRONMENT RULES                                  #
###############################################################################



"""
Generate simple random noise in the range of 0 to whatever is defined in the 
range
"""
function simple_noise(rows::Int, columns::Int, range::Int)
	map = int(rand(rows,columns) * range);
end

"""
Generate more "natural" noise.
http://flafla2.github.io/2014/08/09/perlinnoise.html

Params:
	step: the "movement" in time between the last calculation
	min: the minimum ambient energy value
	max: the maximum ambient energy value
"""
function generate_ambient_energy(step::Float64, min::Int, max:Int)
	map = int(zeros(HEIGHT, WIDTH));

	# Loop through all 
	for r = 1:HEIGHT
		for c = 1:WIDTH
			map[r,c] = perlin()
		end
	end

	return map;

end

"""
Perlin noise implementation
"""
function perlin(x::Float64, y::Float64, z::Float64)

	
end

"""
Returns 3D matrix of size [rows,columns,pages]. The AMBIENT_ENERGY page is set 
to random values
"""
function initialize_grid(rows::Int, columns::Int)
	# Cast to integer values
	map = int(zeros(rows, columns, GRID_DEPTH));

	# Generate intial random map with different ambient energy values
	map[:,:,AMBIENT_ENERGY] = simple_noise(rows, columns, AMBIENT_ENERGY_RANGE);
	
	return map;
end



###############################################################################
#                           CREATURE RULES                                    #
###############################################################################

"""
Given a creature, calculates the metabolic rate of that creature
"""
function calculate_metabolism(creature::Array{Int,1})
	return METABOLISM_CONSTANT;
end

"""
Given a creature, calculates the movement cost of movement for that creature
"""
function calculate_movement_cost(creature::Array{Int,1})
	cost = MAX_MOVEMENT_TIME - creature[MOVEMENT_TIME];
	return bound(cost, 1, MAX_NUM);
end



"""
Bounds all traits that need to be bound to the acceptable limits.
This function should be called every time a creature is created
"""
function calculate_traits(creature::Array{Int,1})

	# Set all negative numbers to 0
	creature[find(creature .< 0)] = 0;

	# Bound basic traits
	creature[FEAR] = bound(creature[FEAR], MIN_FEAR, MAX_FEAR);
	creature[GREED] = bound(creature[GREED], MIN_GREED, MAX_GREED);
	creature[SOCIAL] = bound(creature[SOCIAL], MIN_SOCIAL, MAX_SOCIAL);

	# Set the creature's lifetime to 0
	creature[LIFETIME] = 0;

	# Set the creature's metabolism
	creature[METABOLISM] = calculate_metabolism(creature);

	# Calculate movement cost
	creature[MOVEMENT_TIME] = bound(creature[MOVEMENT_TIME], MIN_MOVEMENT_TIME, MAX_MOVEMENT_TIME);
	creature[MOVEMENT_COST] = calculate_movement_cost(creature);

	# Bound necessary values
	creature[MATING_ENERGY] = bound(creature[MATING_ENERGY], 1, MAX_NUM);

	return creature;
end



"""
Calculates a value from 0 to 1 that indicates the level of difference 
between 2 creatures. Calculates this value by doing an average of the 
norm differences of the attributes between the 2 creatures. A value of 
0 indicates complete similarity, 1 indicates complete dissimilarity 
(should be technically impossible to get)
"""
function creature_similarity(creature1::Array{Int,1}, creature2::Array{Int,1})
	attribute_count = length(creature1);
	sum_diff = 0;
	# Go through all attributes of the creatures to compare every attribute
	for i in ATTRIBUTE_LIST
		# Calculate the difference between attributes as the absolute difference
		diff = abs(creature1[i] - creature2[i]);

		# Divide difference by the maximum of either creature's attributes (or 1).
		# This ensures that the value of every difference will be between 0 and 1.
		larger_attribute = max(creature1[i], creature2[i]);
		diff = diff / max(larger_attribute, 1);

		# Sum up the difference to the sum of differences
		sum_diff += diff;
	end

	# Return average difference
	return sum_diff / attribute_count;
end



"""
Given a non-living cell, returns a very basic creature that would 
spontaneously show up given the right energy conditions
"""
function spontaneous_life(cell::Array{Int,1}, energy::Int)

	# Create a copy of the cell
	new_cell = copy(cell);

	# Make FEAR, GREED, and SOCIAL equal to 1
	new_cell[CELL_TYPE] = CREATURE_CELL;
	new_cell[FEAR] = 5;
	new_cell[GREED] = 5;
	new_cell[SOCIAL] = 5;
	new_cell[STORED_ENERGY] = SPONTANEOUS_LIFE_ENERGY;
	new_cell[ENERGY_CAPACITY] = energy;
	new_cell[MATING_ENERGY] = SPONTANEOUS_LIFE_MATING_ENERGY;
	
	# Calculate remaining traits
	new_cell = mutate(new_cell);

	# Return the new, living, cell
	return new_cell;
end



"""
Given a creature this function evolves its attributes according to the
mutation scale
"""
function mutate(creature::Array{Int,1})
	# Create a copy of the creature
	mutated_creature = copy(creature);

	# Calculate the mutations
	mutations = int(randn(length(ATTRIBUTE_LIST)) / MUTATION_SCALE);

	# Mutate all attributes in the new mutated creature
	mutated_creature[ATTRIBUTE_LIST] += mutations;

	# Calculate remaining traits
	mutated_creature = calculate_traits(mutated_creature);

	return mutated_creature;
end




"""
Given a creature this function returns the same creature with updated values
"""
function update_creature_values(creature::Array{Int,1})
	# Create a copy of the creature
	updated_creature = copy(creature);

	# Iterate the creature's life by 1
	updated_creature[LIFETIME] += 1;

	# Set the cell to "Has Acted", so it can't perform an
	# action until the next round
	updated_creature[HAS_ACTED] = 1;	

	if updated_creature[STORED_ENERGY] > 0
		# Add the ambient energy of the cell to the creature. 
		# This is basically photosynthesis, and all creatures engage in it.
		updated_creature[STORED_ENERGY] += creature[AMBIENT_ENERGY];

		# Subtract the metabolic requirement of the creature from its current energy store
		updated_creature[STORED_ENERGY] -= int(1/creature[METABOLISM] * creature[LIFETIME]);

		# if the creature can move at all
		if creature[MOVEMENT_TIME] < MAX_MOVEMENT_TIME
			# If the creature's movement cooldown is 0, 
			# then the creature can move.
			if creature[MOVEMENT_COOLDOWN] == 0
				# If the creature has moved, then reset the cooldown and set the has 
				# moved value to true
				if creature[HAS_MOVED] == 1
					updated_creature[MOVEMENT_COOLDOWN] = creature[MOVEMENT_TIME];
					updated_creature[HAS_MOVED] = 0;
				end
			else
				# decrement movement cooldown
				updated_creature[MOVEMENT_COOLDOWN] -= 1;
			end
		end
	else
		# If the creature has no energy stored, it is dead and the cell turns into an empty cell
		updated_creature[:] = 0;
	end

	return updated_creature;
end


###############################################################################
#                              CREATURE DECISIONS                             #
###############################################################################


"""
Returns a value indicating how much the creature wants to clone itself.

This value is dependent on how much stored energy the creature has and how
much it fears dying.
"""
function clone_desire(creature::Array{Int,1})

	# The creature's fear and greed determine this value
	desire = 0;

	if creature[STORED_ENERGY] > creature[MATING_ENERGY]

		# ratio of stored energy to mating energy
		ratio = creature[STORED_ENERGY] / creature[MATING_ENERGY];

		# Negative factor dependent on inverse of energy ratio
		greed = -(1/ratio * creature[GREED]);

		# Negative factor dependent on inverse of energy ratio
		fear = -(1/ratio * creature[FEAR]);

		# Positive factor dependent on energy ratio
		social = (ratio * creature[SOCIAL]);

		desire = greed + fear + social;

		if desire > MAX_NUM
	   		desire = MAX_NUM;
	   	else
	   		desire = int(desire);
	   	end
	end

	desire = int(bound(desire, 0, MAX_NUM));

	return desire;
end


"""
Returns a value indicating how much creature1 wants to attack creature2.


"""
function attack_desire(creature1::Array{Int,1}, creature2::Array{Int,1})
	
	# The creature's greed, fear, and social factors determine this value
	desire = 0;

	if creature2[CELL_TYPE] == 2 &&
	   creature1[STORED_ENERGY] > creature1[ATTACK_CAPABILITY] &&
	   creature1[ATTACK_CAPABILITY] > 0

	   	if creature2[ATTACK_CAPABILITY] > 0
			ratio = creature1[ATTACK_CAPABILITY] / creature2[ATTACK_CAPABILITY];
		else
			ratio = MAX_NUM;
		end

		similarity = creature_similarity(creature1, creature2);

		# Positive factor dependent on attack ratio
		greed = creature1[GREED] * ratio;

		# Negative factor dependent on inverse of attack ratio
		fear = -(creature1[FEAR] * 1/ratio);

		# Negative factor dependent on creature similarity
		social = -(creature1[SOCIAL] * similarity);

		desire = greed + fear + social;

		if desire > MAX_NUM
	   		desire = MAX_NUM;
	   	else
	   		desire = int(desire);
	   	end
	end
	
	desire = int(bound(desire, 0, MAX_NUM));

	return desire;

end


"""
Returns a value indicating how much creature1 wants to mate with creature2.


"""
function mate_desire(creature1::Array{Int,1}, creature2::Array{Int,1})

	# The creature's greed, fear, and social factors determine this value
	desire = 0;
	
	if creature2[CELL_TYPE] == 2 &&
	   creature1[STORED_ENERGY] > creature1[MATING_ENERGY] &&
	   creature2[STORED_ENERGY] > creature2[MATING_ENERGY]

		# ratio of stored energy to mating energy
	   	ratio = creature1[STORED_ENERGY] / creature1[MATING_ENERGY];

	   	# similarity of creatures
	   	similarity = creature_similarity(creature1, creature2);

	   	# Greed is a negative factor dependent on inverse of energy ratio
	   	greed = -(creature1[GREED] * 1/ratio);
	   
	   	# Fear is a negative factor dependent on energy ratio
	   	fear = -(creature1[FEAR] * 1/ratio + creature1[FEAR] * similarity);
	   
	   	# Social is a positive factor dependent on creature similarity
	   	social = creature1[SOCIAL] * ratio + creature1[SOCIAL] * similarity;

	   	desire = greed + fear + social;

	   	if desire > MAX_NUM
	   		desire = MAX_NUM;
	   	else
	   		desire = int(desire);
	   	end
	end

	desire = int(bound(desire, 0, MAX_NUM));

	return desire;
end


"""
Returns a value indicating how much a creature wants to move to a cell.


"""
function movement_desire(creature::Array{Int,1}, cell::Array{Int,1})

	# The creature's greed and fear factors determines this value
	desire = 0;

	if creature[STORED_ENERGY] > creature[MOVEMENT_COST] &&
	   cell[CELL_TYPE] == 0

		# Potiential energy gain
		gain = cell[AMBIENT_ENERGY] - creature[MOVEMENT_COST];

		# Stored energy vs. how much it costs to move
		ratio = creature[STORED_ENERGY] / creature[MOVEMENT_COST];

		# Greed is a positive factor dependent on gain 
		greed = creature[GREED] * gain;
		
		# Fear is a negative factor dependent on inverse of ratio
		fear = -(creature[FEAR] * 1/ratio);
		
		# Social is not a factor
		social = 0;

		desire = greed + fear + social;

		if desire > MAX_NUM
	   		desire = MAX_NUM;
	   	else
	   		desire = int(desire);
	   	end
	end

	desire = int(bound(desire, 0, MAX_NUM));

	return desire;
end






###############################################################################
#                              CREATURE ACTION                                #
###############################################################################

"""
Updates 2 creatures, both lose energy according to attack capability of the
other if creature2 has the energy. If it does not then creature1 consumes
creature2's energy and creature2 is no more.
"""
function attack(creature1::Array{Int,1}, creature2::Array{Int,1})

	if creature2[ATTACK_CAPABILITY] > creature2[STORED_ENERGY]
		creature1[STORED_ENERGY] -= creature2[ATTACK_CAPABILITY];
		creature2[STORED_ENERGY] -= creature1[ATTACK_CAPABILITY];
	else

		creature1[STORED_ENERGY] += creature2[STORED_ENERGY];
		creature2 = int(zeros(GRID_DEPTH));
	end

	return creature1, creature2;
end

"""
Updates a creature to move
"""
function move(creature::Array{Int,1})

	# Subtract the cost of movement from the creature's energy reserve
	creature[STORED_ENERGY] -= MOVEMENT_COST;
	
	# Set the movement boolean
	creature[HAS_MOVED] = 1;
	
	# Return the creature
	return creature;
end

"""
Given 1 creature this function returns a clone creature
"""
function clone(creature::Array{Int,1})

	child = mutate(creature);

	# The child gets the mating energy of its parent
	child[STORED_ENERGY] = creature[MATING_ENERGY];

	# Subtract energy from creature	
	creature[STORED_ENERGY] -= creature[MATING_ENERGY];

	return (creature, child); 
end

"""
Given 2 creatures this function returns an offspring creature
"""
function mate(creature1::Array{Int,1}, creature2::Array{Int,1})

	# Create child creature
	child = int(zeros(length(creature1)));
	# Set the child to a creature type
	child[CELL_TYPE] = CREATURE_CELL;
	# The child gets the mating energies used by both parents
	child[STORED_ENERGY] = creature1[MATING_ENERGY] + creature2[MATING_ENERGY];

	# Randomly pick attributes from each creature to get an offspring
	# by creating an array of 0s and 1s
	choice = int(round(rand(length(ATTRIBUTE_LIST))));

	creature1_attributes = find(choice .== 0);
	creature2_attributes = find(choice .== 1);

	attributes = int(zeros(length(ATTRIBUTE_LIST)));

	# All choice options that are 0 are attributes of creature1 that will
	# be passed on
	attributes[creature1_attributes] = creature1[ATTRIBUTE_LIST][creature1_attributes];

	# All choice options that are 1 are attributes of creature2 that will
	# be passed on
	attributes[creature2_attributes] = creature2[ATTRIBUTE_LIST][creature2_attributes];

	# Set child attributes
	child[ATTRIBUTE_LIST] = attributes;

	# Mutate the child and bound the necessary traits to within acceptable limits
	child = mutate(child);

	# Subtract energy from both creatures
	creature1[STORED_ENERGY] -= creature1[MATING_ENERGY];
	creature2[STORED_ENERGY] -= creature2[MATING_ENERGY];

	child[STORED_ENERGY] = creature1[MATING_ENERGY] + creature2[MATING_ENERGY];

	return creature1, creature2, child;
end




###############################################################################
#                                 SIMULATION                                  #
###############################################################################



"""
Calculates the state of the ecosystem given a state of the ecosystem
"""
function calculate_ecosystem(ecosystem::Array{Int,3})

	# Loop through all cells in the ecosystem
	for r = 1:HEIGHT
		for c = 1:WIDTH
			# Get all cell values for this specific XY index
			cell = ecosystem[r,c,:][:];
			
			if cell[CELL_TYPE] == BLANK_CELL

				# Sum up ambient energy of surrounding cells, if above a threshold, a new simple creature is born spontaneously!
				energy_sum = 0;

				for i = (r - 1):(r + 1)
					# Ignore cells outside the scope of the board
					if i < 1 || i > HEIGHT
						continue;
					end

					for j = (c - 1):(c + 1)
						# Ignore cells outside the scope of the board
						if j < 1 || j > WIDTH
							continue;
						end

						energy_sum += ecosystem[i,j,AMBIENT_ENERGY];

					end
				end

				if energy_sum > SPONTANEOUS_LIFE_THRESHOLD
					ecosystem[r,c,:] = spontaneous_life(cell, energy_sum);
				end

			elseif cell[CELL_TYPE] == OBSTACLE_CELL


			# If the cell is a creature and the creature has not acted yet
			elseif cell[CELL_TYPE] == CREATURE_CELL && cell[HAS_ACTED] == 0
				
				# Movement
				x_move = 0;
				y_move = 0;
				
				# Move if necessary, attack if necessary, reproduce if possible
				# If there is energy to move, and/or attack, and/or reproduce,
				# Then look at all neighboring cells to determine what action
				# to perform
				if cell[STORED_ENERGY] > cell[MOVEMENT_COST] ||
				   cell[STORED_ENERGY] > cell[ATTACK_CAPABILITY] ||
				   cell[STORED_ENERGY] > cell[MATING_ENERGY]

				   	empty_cells = Array((Int, Int), 0);
				   	# Loop through all cells around the creature to find empty cells
					for i = (r - 1):(r + 1)
						# Ignore cells outside the scope of the board
						if i < 1 || i > HEIGHT
							continue;
						end

						for j = (c - 1):(c + 1)
							# Ignore cells outside the scope of the board
							if j < 1 || j > WIDTH
								continue;
							end

							# Skip self
							if i == 0 && j == 0
								continue;
							end

							neighbor = ecosystem[i,j,:];

							if neighbor[CELL_TYPE] == 0
								push!(empty_cells, (i,j));
							end

						end
					end


				   	# Desire to attack
					att_des = 0;
					att_row = r;
					att_col = c;

					# Desire to move
					mov_des = 0;
					mov_row = r;
					mov_col = c;

					# Desire to clone
					clone_des = 0;

					# Desire to mate
					mate_des = 0;
					mate_row = r;
					mate_col = c;

					# Loop through all cells around the creature. Each cell
					# examined will provide a [row, col] vector indicating
					# desired motion.
					for i = (r - 1):(r + 1)
						# Ignore cells outside the scope of the board
						if i < 1 || i > HEIGHT
							continue;
						end

						for j = (c - 1):(c + 1)
							# Ignore cells outside the scope of the board
							if j < 1 || j > WIDTH
								continue;
							end

							# Skip self
							if i == 0 && j == 0
								continue;
							end
							
							neighbor = ecosystem[i,j,:][:];

							# Calculate max attack desire
							(att_des, att_ind) = findmax([att_des, attack_desire(cell, neighbor)]);
							# If the attack desire is greater for this new cell
							# being considered, then record the row and col
							# that the cell will attack
							if att_ind == 2
								att_row = i;
								att_col = j;
							end

							# The creature can only move if there are empty
							# cells nearby
							if !isempty(empty_cells)
								# Calculate max mate desire
								(mate_des, mate_ind) = findmax([mate_des, mate_desire(cell, neighbor)]);
								if mate_ind == 2
									mate_row = i;
									mate_col = j;
								end

								# Calculate max movement desire
								(mov_des, mov_ind) = findmax([mov_des, movement_desire(cell, neighbor)]);
								if mov_ind == 2
									mov_row = i;
									mov_col = j;
								end
							end
						end
					end

					# Only calculate if there are open cells
					if !isempty(empty_cells)
						# Clone desire calculation
						clone_des = clone_desire(cell);
					end

					# Place all desires into an array and find the maximum desire
					(_, desire) = findmax([att_des, mov_des, clone_des, mate_des]);

					# If the maximum desire of the creature is to attack
					if desire == 1 && att_des > 0

						# Get the victim creature
						victim = ecosystem[att_row, att_col,:][:];

						# Update the victim and creature with attack
						(cell, victim) = attack(cell, victim);

						# Update the victim and the cell
						ecosystem[att_row,att_col,:] = victim;
						ecosystem[r,c,:] = cell;

					# If the maximum desire of the creature is to move
					elseif desire == 2 && mov_des > 0

						# Set the creature HAS_MOVED tag
						cell[HAS_MOVED] = 1;

						# Update the creature with movement
						cell = move(cell);

						# Move the creature to the indicated position
						ecosystem[mov_row, mov_col,:] = cell;

						# Set the old position of the creature to empty
						ecosystem[r,c,:] = int(zeros(GRID_DEPTH));

					# If the maximum desire of the creature is to clone
					elseif desire == 3 && mate_des > 0
						
						# Create a clone child
						(cell, child) = clone(cell);

						# Find where to place the child
						idx = rand(1:length(empty_cells));

						(child_row, child_col) = empty_cells[idx];

						# Place the child at an open location near the creature
						ecosystem[child_row, child_col, :] = child;
						
						# Set the position
						ecosystem[r,c,:] = cell;

					# If the maximum desire of the creature is to mate
					elseif desire == 4 && clone_des > 0
						
						# Mate with the creature at the desired position
						partner = ecosystem[mate_row,mate_col,:][:];

						# Create a child with the desired creature
						(cell, partner, child) = mate(cell, partner);

						# Find where to place the child
						idx = rand(1:length(empty_cells));

						# Find where to put the child creature
						(child_row, child_col) = empty_cells[idx];

						# Place the child creature
						ecosystem[child_row, child_col,:] = child;

						# Update the ecosystem with the partner
						ecosystem[mate_row, mate_col, :] = partner;
					end
				end

				# Update the creature
				cell = update_creature_values(cell);
				ecosystem[r,c,:] = cell;
			end
		end
	end

	# Update all creatures to allow for acting on the next round
	ecosystem[:,:,HAS_ACTED] = 0;

	# Update ambient energy values
	ecosystem[:,:,AMBIENT_ENERGY] = simple_noise(HEIGHT, WIDTH, AMBIENT_ENERGY_RANGE);

	# Return the ecosystem
	return ecosystem;

end



end # End module