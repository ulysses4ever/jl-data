using HttpServer;
using WebSockets;
using Ecosystem;

# These are all constants used in the ecosystem
include("Constants.jl");

# Initialize all global variables
ecosystem = initialize_grid(HEIGHT, WIDTH); # ecosystem grid

for i = 1:1000
	# Update the ecosystem and ecosystem display
	ecosystem = calculate_ecosystem(ecosystem);
	# put all cell color values into a large string which will be parsed
	# by the javascript client-side
end




println(size(ecosystem))
# println(ecosystem[:,:,1])