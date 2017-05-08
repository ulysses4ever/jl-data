#=
The environment is a 3 dimensional grid. The first 2 dimensions (X, Y) represent the spatial dimensions of the grid. The 3rd dimension
represents the characteristics of that grid point. If there is a creature at that grid-point, then the 3rd dimension will contain information about that creature. If there is no creature, then the 3rd dimension will be mostly blank.

Z dimension characteristics by layer and the values representing different options for that layer:


1:
type of block.
	0 - blank space
	1 - obstacle
	2 - creature
2:
ambient energy available at block.
	Range: 0 to 255
	Desc: the energy content of the block. Energy is the fundamental "currency" of this ecosystem and determines the degree of many other attributes
3:
movement speed.
	Range: 0 to Inf
	Desc: energy to move scales logarithmically with energy 
4: 
mating similarity requirement
	Range: 0 to Inf
	Desc: how similar a creature must be to another creature in order to mate. Scales logarithmically with energy
5: 
attack capability.
	Range: 0 to Inf
	Desc: the level of attack the creature can output. Scales logarthmically with energy
6:
vision range.
	Range: 0 to Inf
	Desc: how many cells out a creature can see it's environment. 
7: 
8: 
9: 
10: 
11: 
12: 
13: 
14: 
15: 
16: 
17: 
18: 
19: 
20: 
=#

using HttpServer
using WebSockets

#=
GLOBALS
=#
width = 360;
height = 180;
ecosystem = initialize_grid(width, height, 6);

wsh = WebSocketHandler() do req, client
	while true
		# cells = string(int(round(ambient_energy(360,180, [.5, .2, .4, .3], [2, 4, 8, 16]))));
		cells = string(int());
		write(client, cells)
		# sleep(0.01)
	end
end


#=
Returns 3D matrix of size [x,y,z]
=#
function initialize_grid(x::Int64, y::Int64, z::Int64)
	map = zeros(x, y, z);

	# Generate intial random map
	map[:,:,2] = simple_noise(x,y);
	
	return map;
end

#=
Returns perlin noise based ambient energy distribution over map of size [x,y] of values from 0 to 255
=#
function ambient_energy(x::Int64, y::Int64, amplitudes::Array{Float64,1}, frequencies::Array{Int64,1})
	# Initialize map
	map = zeros(x, y);
	
	# Multiply noises by their respective amplitudes and get a weighted sum
	for i = 1:length(amplitudes)
		# Initialize different noise maps based on different frequencies
		noise_map = sin_noise(x, y, frequencies[i]);
		map += noise_map * amplitudes[i];
	end

	return (map / findmax(map)[1]) * 255;
end

#=
Generate sinusoidal noise over map of size [x,y] with a range of values from 0 to 1
=#
function sin_noise(x::Int64, y::Int64, freq::Int64)
	# Initialize the phase to some value within 0 and 2*pi
	phase = rand() * 2 * pi;
	# Create a map of x and y values to get a sinusoid curve over the actual x-y space
	noise_map = [(i + j) for i in linspace(1,x,x)/x, j in linspace(1,y,y)/y];

	# randomize the direction of the sinusoid, or in other words which corner of 
	# the matrix the max value of the noise map will be
	dir = rand(1:4);
	if dir == 1
		noise_map = noise_map;
	elseif dir == 2
		noise_map = flipdim(noise_map,1);
	elseif dir == 3
		noise_map = rot180(noise_map);
	elseif dir == 4
		noise_map = rot180(flipdim(noise_map,1));
	end

	noise_map = convert(Array{Float64, 2}, noise_map);
	# add 1 and divide by 2 to get the range within 0 and 1
	
	return (sin(2 * pi * freq * noise_map + phase) + 1) / 2;
end

function simple_noise(x::Int64, y::Int64)
	map = int(rand(x,y) * 255);
end



# Run the server
server = Server(wsh)
run(server, 8080)



