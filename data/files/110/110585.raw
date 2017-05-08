#=
Returns perlin noise based ambient energy distribution over map of size [x,y] of values from 0 to 255
=#
function ambient_energy(x::Integer, y::Integer, amplitudes::Array{Float64,1}, frequencies::Array{Integer,1})
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
function sin_noise(x::Integer, y::Integer, freq::Integer)
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