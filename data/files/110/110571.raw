"""
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
ATTRIBUTE - FEAR
	Range: 0 to 255
	Desc: how much a creature wants to stay alive. The higher this value, 
	      the more risk-averse this creature will be.

4:
ATTRIBUTE - GREED
	Range: 0 to 255
	Desc: how much a creature desires more energy. The higher this value, 
	      the more weight is given to any action which may result in the most 
	      energy gain

5:
ATTRIBUTE - SOCIAL
	Range: 0 to 255
	Desc: how much the creature desires to be near to similar creatures. The 
	      higher this value, the more weight is given to any action which may 
	      result in being closer to similar creatures.

	      This value also determines how much the creature wants to replicate.

6:
ATTRIBUTE - MOVEMENT_TIME.
	Range: MIN_MOVEMENT_TIME to MAX_MOVEMENT_TIME
	Desc: How quickly the creature can move. 
	      The lower the value the faster the creature.
	      A value of MAX_MOVEMENT_TIME indicates that the creature cannot move.
	      A value of MIN_MOVEMENT_TIME indicates that the creature can move
	      every cycle of the ecosystem.

	      This value also determines the amount of energy the creature must
	      expend in order to move. This amount is determined by MOVEMENT_COST
	      value.

7:
ATTRIBUTE - MATING_ENERGY
	Range: 1 to 2^63 - 1 (Int64 max value)
	Desc: How much energy this creature must expend in order to mate. 
	      This value also determines how much energy is given to the child of
	      the creature in the form of stored energy. Is used in both 
	      reproduction and cloning

8: 
ATTRIBUTE - ATTACK_CAPABILITY
	Range: 0 to 2^63 - 1 (Int64 max value)
	Desc: the level of attack the creature can output. The creature can attack
	      any creature that is in one of the 8 neighboring squares.

9:
ATTRIBUTE - energy capacity.
	Range: 0 to 2^63 - 1 (Int64 max value)
	Desc: how much energy a creature can hold until it is "full" and will not absorb/consume any longer

10:
ATTRIBUTE - LIFESPAN_MULTIPLIER
	Range: 0 to 2^63 - 1 (Int64 max value)
	Desc: This value is multiplied by the calculated metabolism of the
	      creature to determine how much the age of the creature affects
	      its metabolism. Initially set to 1.

11:
VALUE - stored energy
	Range: 0 to energy capacity
	Desc: how much energy the creature has stored. A value of 0 means the creature will disappear from the grid

12:
VALUE - movement cooldown
	Range: 0 to movement speed
	Desc: how many turns until the creature can move. If 0, then the creature can move this turn. After a move this cooldown resets to the maximum value. Every cycle of the grid this number is decremented

13:
VALUE - movement boolean
	Range: 0 or 1
	Desc: this boolean value is set to true after the movement cooldown has been reset, and set to true once the movement cooldown reaches 0.

14:
VALUE - METABOLISM
	Range: 0 to 2^63 - 1 (Int64 max value)
	Desc: How much energy it costs each creature regardless of other actions.
	      Subtracted from the creature energy capacity after every turn. This
	      value is dependent on the creature's movement speed, attack
	      capability, and vision range plus a constant

15:
VALUE - MOVEMENT_COST
	Range: 1 to 2^63 - 1 (Int64 max value)
	Desc: How much enrgy it costs the creature to move. This value is
	      calculated by the 'calculate_movement_cost' function.

16:
VALUE - LIFETIME
	Range: 0 to 2^63 - 1 (Int64 max value)
	Desc: How many iterations of the simulation the creature has survived.
	      This determines the metabolism rate of energy loss.


17:
VALUE - HAS_ACTED
	Range: 0 to 1
	Desc: Determines whether creature has acted or not

Creatures will be colored using rgb values that represent the 3 most essential characteristics that determine its behavior:

	Red - FEAR : how much the creature wants to stay alive
	Green - GREED : how much the creature wants energy
	Blue - SOCIAL : how much the creature wants to be near similar creatures


"""




# Environment
CELL_TYPE = 1;
AMBIENT_ENERGY = 2;

# Attributes
FEAR = 3;
GREED = 4;
SOCIAL = 5;
MOVEMENT_TIME = 6;
MATING_ENERGY = 7;
ATTACK_CAPABILITY = 8;
ENERGY_CAPACITY= 9;
LIFESPAN_MULTIPLIER = 10;

# Values
STORED_ENERGY = 11;
MOVEMENT_COOLDOWN = 12;
HAS_MOVED = 13;
METABOLISM = 14;
MOVEMENT_COST = 15;
LIFETIME = 16;
HAS_ACTED = 17;

# Depth of grid. Sum of number of environments, attributes, and values
GRID_DEPTH = 17;



# Environment constants
BLANK_CELL = 0;
OBSTACLE_CELL = 1;
CREATURE_CELL = 2;

# Range of possible ambient energy values
AMBIENT_ENERGY_RANGE = 10;

# Attribute constants
ATTRIBUTE_LIST = [FEAR,
                  GREED,
                  SOCIAL,
                  MOVEMENT_TIME,
                  MATING_ENERGY,
                  ATTACK_CAPABILITY,
                  ENERGY_CAPACITY,
                  LIFESPAN_MULTIPLIER];

# Arbitrary maximum number
MAX_NUM = 1000000;

# The limits of the 3 primary attributes all remain within RGB ranges
MIN_FEAR = 0;
MAX_FEAR = 255;

MIN_GREED = 0;
MAX_GREED = 255;

MIN_SOCIAL = 0;
MAX_SOCIAL = 255;

# This is the fastest movement time. It means the creature can move once
# every cycle
MIN_MOVEMENT_TIME = 1;

# This is a movement time that indicates no movement at all by the creature
MAX_MOVEMENT_TIME = 1000;

# Divisor of the normal distribution of mutation. Smaller this number is the
# more mutation there will be
MUTATION_SCALE = 2;

# Metabolism constant used to determine how much is subtracted from the
# creature's stored energy per turn. Energy lost per turn is proportional
# to the metabolism constant
METABOLISM_CONSTANT = 12;

# How similar creatures must be to mate (similarity determined by similarity 
# function)
MATING_SIMILARITY = 0.2;


# How much energy it takes to create spontaneous life
SPONTANEOUS_LIFE_THRESHOLD = 70;
SPONTANEOUS_LIFE_ENERGY = 15;
SPONTANEOUS_LIFE_MATING_ENERGY = 10;

BLANK_CELL_COLOR = "#2F2F2F"; # 
OBSTACLE_CELL_COLOR = "#2F2F2F"; # dark gray


# Ecosystem size
WIDTH = 100;
HEIGHT = 100;
