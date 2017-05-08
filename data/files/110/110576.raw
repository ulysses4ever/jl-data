using HttpServer;
using WebSockets;
using Ecosystem;

# These are all constants used in the ecosystem
include("Constants.jl");



# Initialize all global variables
global ecosystem = initialize_grid(HEIGHT, WIDTH); # ecosystem grid

# Run the websocket handler
wsh = WebSocketHandler() do req, client
	
	global ecosystem;

	while true

		# Update the ecosystem and ecosystem display
		ecosystem = calculate_ecosystem(ecosystem);	

		# put all cell color values into a large string which will be parsed
		# by the javascript client-side
		visual = join(display_ecosystem(ecosystem), ',');

		# send the string to the client to be parsed and displayed
		write(client, visual);

	end
end


# Run the server
server = Server(wsh)
run(server, 8080)