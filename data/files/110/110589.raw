using HttpServer
using WebSockets

#=
The environment is a 3 dimensional grid. The first 2 dimensions (X, Y) represent the spatial dimensions of the grid. The 3rd dimension
represents the characteristics of that grid point. If there is a creature at that grid-point, then the 3rd dimension will contain information about that creature. If there is no creature, then the 3rd dimension will be mostly blank.

Z dimension characteristics by layer and the values representing different options for that layer:


1:
ENVIRONMENT - type of block.
	0 - blank space
	1 - obstacle
	2 - creature
2:
ENVIRONMENT - ambient energy available at block.
	Range: 0 to 255
	Desc: the energy content of the block. Energy is the fundamental "currency" of this ecosystem and determines the degree of many other attributes
3:
ATTRIBUTE - desire to stay alive. (FEAR)
	Range: 0 to 255
	Desc: how much a creature wants to stay alive. The high the value, the more risk-averse this creature will be
4:
ATTRIBUTE - desire for energy. (GREED)
	Range: 0 to 255
	Desc: how much a creature desires more energy. The higher this value, the more weight is given to any action which may result in the most energy gain
5:
ATTRIBUTE - desire for similarity. (SOCIAL)
	Range: 0 to 255
	Desc: how much the creature desires to be near to similar creatures. The higher this value, the more weight is given to any action which may result in being closer to similar creatures
6:
ATTRIBUTE - movement speed.
	Range: 0 to 255
	Desc: How quickly the creature can move. The lower the value the faster the creature. The cost of movement scales logarithmically with energy 
7: 
ATTRIBUTE - mating similarity requirement
	Range: 0 to Inf
	Desc: How similar a creature must be to another creature in order to mate. Similarity is counted as some kind of integer difference between creatures. Cost to mate scales with this number (larger number, more cost to mate)
8: 
ATTRIBUTE - attack capability.
	Range: 0 to Inf
	Desc: the level of attack the creature can output. Cost to attack scales logarithmically
9:
ATTRIBUTE - attack similarity
	Range: 0 to Inf
	Desc: how different another creature must be in order to merit being attacked. A "0" means this creature will attack any other creature, including creatures that are the exact same.
10: 
ATTRIBUTE - vision range.
	Range: 0 to Inf
	Desc: how many cells out a creature can see it's environment in a circle around itself. 
11:
ATTRIBUTE - energy capacity.
	Range: 0 to Inf
	Desc: how much energy a creature can hold until it is "full" and will not absorb/consume any longer
12:
VALUE - stored energy
	Range: 0 to energy capacity
	Desc: how much energy the creature has stored. A value of 0 means the creature will disappear from the grid
13:
VALUE - movement cooldown
	Range: 0 to movement speed
	Desc: how many turns until the creature can move. If 0, then the creature can move this turn. After a move this cooldown resets to the maximum value. Every cycle of the grid this number is decremented
14:
VALUE - movement boolean
	Range: 0 or 1
	Desc: this boolean value is set to true after the movement cooldown has been reset, and set to true once the movement cooldown reaches 0.
15:
VALUE - energy to move
	Range: 1 to Inf
	Desc: this value is the amount of energy it takes the creature to move in 1 turn. Dependent on movement speed attribute
16:
VALUE - metabolism
	Range: 1 to Inf
	Desc: how much energy it costs each creature regardless of other actions. Subtracted from the creature energy capacity after every turn
=#


#=
Creatures will be colored using rgb values that represent the 3 most essential characteristics that determine its behavior:

	Red - FEAR : how much the creature wants to stay alive
	Green - GREED : how much the creature wants energy
	Blue - SOCIAL : how much the creature wants to be near similar creatures
=#

GRID_DEPTH = 16; # depth of grid

CELL_TYPE = 1;
BLANK_CELL = 0;
OBSTACLE_CELL = 1;
CREATURE_CELL = 2;
AMBIENT_ENERGY = 2;

# Attributes
FEAR = 3;
GREED = 4;
SOCIAL = 5;
MOVEMENT_SPEED = 6;
MATING_SIMILARITY = 7;
ATTACK = 8;
ATTACK_SIMILARITY = 9;
VISION_RANGE = 10;
ENERGY_CAPACITY = 11;

# Values
STORED_ENERGY = 12;
MOVEMENT_COOLDOWN = 13;
HAS_MOVED = 14;
ENERGY_TO_MOVE = 15;
METABOLISM = 16;

BLANK_CELL_COLOR = "#000000"; # black
OBSTACLE_CELL_COLOR = "#2F2F2F"; # dark gray


#=
GLOBALS
=#
WIDTH = 360;
HEIGHT = 180;
MUTATION_RATE = 0.01;



# initialize the ecosystem grid
ecosystem = initialize_grid(HEIGHT, WIDTH, GRID_DEPTH);


# ecosystem display
ecosystem_display = cell(HEIGHT, WIDTH);
ecosystem_display[:,:] = BLANK_CELL_COLOR;

wsh = WebSocketHandler() do req, client
	while true
		# put all cell color values into a large string which will be parsed by the javascript client-side
		visual = join(ecosystem_display, ',');
		write(client, visual)
	end
end


#=
Returns 3D matrix of size [x,y,z]
=#
function initialize_grid(rows::Integer, columns::Integer, pages::Integer)
	map = zeros(rows, columns, pages);

	# Generate intial random map with different ambient energy values
	map[:,:,2] = simple_noise(rows, columns);
	
	return map;
end



#=
Generate simple random noise in the range of 0 to 255
=#
function simple_noise(rows::Integer, columns::Integer)
	map = int(rand(x,y) * 5);
end

#=
Calculates a value from 0 to 1 that indicates the level of difference between 2 creatures. Calculates this value by doing an average of the norm differences of the attributes between the 2 creatures.
A value of 0 indicates complete similarity, 1 indicates complete dissimilarity (should be technically impossible to get)
=#
function creature_difference(creature1::Array{Integer,1}, creature2::Array{Integer,1})
	attribute_count = length(creature1);
	sum_diff = 0;
	for i = 1:attribute_count
		diff = abs((creature1[i] - creature2[i]) / max(creature1[i],creature2[i]));
		sum_diff += diff;
	end

	# Return average difference
	return sum_diff / attribute_count;
end

#=
Given a non-living cell, returns a very basic creature that would spontaneously show up given the right energy conditions
=#
function spontaneous_life(cell::Array{Integer,1})
	new_cell = cell;
	# Make FEAR, GREED, and SOCIAL equal to 1
	new_cell[CELL_TYPE] = CREATURE_CELL;
	new_cell[FEAR] = 1;
	new_cell[GREED] = 1;
	new_cell[SOCIAL] = 1;

	# Return the new, living, cell
	return new_cell;
end


#=
Update the creature values given a creature
=#
function update_creature_values(creature::Array{Integer,1}))
	updated_creature = creature;

	if updated_creature[STORED_ENERGY] > 0
		# Add the ambient energy of the cell to the creature. This is basically photosynthesis, and all creatures engage in it.
		updated_creature[STORED_ENERGY] += creature[AMBIENT_ENERGY];

		# Subtract the metabolic requirement of the creature from its current energy store
		updated_creature[STORED_ENERGY] -= METABOLISM;

		# If the creature's movement cooldown is 0, then the creature can move. If the creature has moved, then reset the cooldown and set the has moved value to true
		if updated_creature[MOVEMENT_COOLDOWN] == 0
			if updated_creature[HAS_MOVED] == 1
				updated_creature[MOVEMENT_COOLDOWN] = updated_creature[MOVEMENT_SPEED];
				updated_creature[HAS_MOVED] = 0;
			end
		else
			# decrement movement cooldown
			updated_creature[MOVEMENT_COOLDOWN] -= 1;
		end
	else
		# If the creature has no energy stored, it is dead and the cell turns into an empty cell
		updated_creature[:] = 0;
	end

	return updated_creature;
end


#=
Calculates the state of the ecosystem given a state of the ecosystem
=#
function calculate_ecosystem(ecosystem::Array{Integer,3})

	# copy the initial ecosystem grid to the buffer, which contain all changes before they are copied to the actual ecosystem grid
	ecosystem_buffer = ecosystem;

	rows = size(ecosystem)[1];
	columns = size(ecosystem)[2];

	# Loop through all cells in the ecosystem
	for r = 1:rows
		for c = 1:columns
			# Get all cell values for this specific XY index
			cell = ecosystem[r,c,:];
			
			if cell[CELL_TYPE] == BLANK_CELL
				# Set display of cell to blank hex value
				ecosystem_display[r,c] = BLANK_CELL_COLOR;

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

						energy_sum += cell[r, c, AMBIENT_ENERGY];

					end
				end

				if energy_sum > SPONTANEOUS_LIFE_THRESHOLD
					ecosystem_buffer[r,c,:] = spontaneous_life(cell);
				end

			elseif cell[CELL_TYPE] == OBSTACLE_CELL
				# Set display of cell to obstacle hex value
				ecosystem_display[r,c] = OBSTACLE_CELL_COLOR;

			elseif cell[CELL_TYPE] == CREATURE_CELL

				fear = cell[FEAR]; # red
				greed = cell[GREED]; # green
				social = cell[SOCIAL]; # blue

				# Set the color of the creature
				ecosystem_display[r,c] = rgb_to_hex_string(fear, greed, social);

				# Move on to the next cell if the creature does not have the energy to move.
				# A creature can perform no actions if it does not have movement energy
				if cell[STORED_ENERGY] < cell[ENERGY_TO_MOVE]
					# Update the creature values
					ecosystem_buffer[r,c,:] = update_creature_values(cell);
				else
					# Vision range of this creature
					vis = cell[VISION_RANGE];

					# Loop through all cells around the creature according to its vision range.
					# Each cell examined will provide a [row, col] vector indicating desired motion.
					for i = (r - vis):(r + vis)
						# Ignore cells outside the scope of the board
						if i < 1 || i > HEIGHT
							continue;
						end

						for j = (c - vis):(c + vis)
							# Ignore cells outside the scope of the board
							if j < 1 || j > WIDTH
								continue;
							end

							# Calculate desired movement vector from this neighbor cell
							

						end
					end

					# Move according to desired movement vector and attributes. 
					# For any race conditions, default to whoever has the faster movement speed to get the empty spot
					
					
					# Update the creature values
					ecosystem_buffer[r,c,:] = update_creature_values(cell);
				end
			end
		end
	end

	# Update ambient energy values
	ecosystem_buffer[:,:,2] = simple_noise(rows, columns);

	# Copy over all changes from the ecosystem buffer to the ecosystem.
	# THIS SHOULD BE THE ONLY PLACE THE ECOSYSTEM CHANGES
	ecosystem = ecosystem_buffer;

	# Return the ecosystem
	return ecosystem;

end




#=
Return a string hex value of an RGB color
=#
function rgb_to_hex_string(r::Integer, g::Integer, b::Integer)
	c = hex((1 << 24) + (r << 16) + (g << 8) + b)[2:end];
	return "#$c";
end



# Run the server
server = Server(wsh)
run(server, 8080)



