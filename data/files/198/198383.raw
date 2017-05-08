include("bomberman.jl")

try
	GAMEIP = "0.0.0.0"
	GAMEPORT = 40000
	player = Player(GAMEIP, GAMEPORT)
	
	print(typeof(player), "\n")
	@async begin
		recv_update(player)
	end
	while true
		print(player.data)
	end

catch err
	print("connection ended with error $err\n")
end