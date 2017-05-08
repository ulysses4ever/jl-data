include("bomberman.jl")

try
	GAMEIP = "0.0.0.0"
	GAMEPORT = 40000
	player = Player(GAMEIP, GAMEPORT)

	p = @spawn recv_update(player.conn, player.data)

	print(typeof(player), "\n")

	while true
		print(fetch(player))	
	end

catch err
	print("connection ended with error $err\n")
end