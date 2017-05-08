using JSON

type Player
	conn::Any
	data::Any

	Player(IP, PORT) = new(connect(IP, PORT), Response())
end

function recv_update(player)
	try
		bufsize = 1024
		strbuf = ""
		json = ""
		while true
			buf = zeros(Uint8, bufsize)
		    read(player.conn, buf)
		    strbuf = convert(ASCIIString, buf)
		    json = "$json$strbuf"
		    for c in strbuf
		    	if c == uint8('\n')
		    		json = split(json, '\n')
		    		data = tparse(JSON.parse(json[1]))
		    		print(data)
		    		if length(json) > 2
		    			json = json[3]
		    		end
		    		break
		    	end
		    end
		end
	catch err
		print("$err")
	end
end

function up(player)
	try
		write(player.conn, "up\n")
	catch err
		print $err
		close(player.conn)
	end
end

function down(player)
	try
		write(player.conn, "down\n")
	catch err
		print $err
		close(player.conn)
	end
end

function left(player)
	try
		write(player.conn, "left\n")
	catch err
		print $err
		close(player.conn)
	end
end

function right(player)
	try
		write(player.conn, "right\n")
	catch err
		print $err
		close(player.conn)
	end
end

function bomb(player)
	try
		write(player.conn, "bomb\n")
	catch err
		print $err
		close(player.conn)
	end
end

function coords(player)
  if player.data.X != 0 || player.data.Y != 0
    return (player.data.X, player.data.Y)
  end
end

function board(player)
	if player.data.Board[1][1] != nothing #this is a hack, not sure proper undefined checking
		return player.data.Board
	end
end

function disconnect(player)
	try
		close(player.conn)
	catch err
		print $err
	end
end

type Response
	Turn::Int64
	TurnDuration::Int64
	Name::UTF8String
	X::Int64
	Y::Int64
	LastX::Int64
	LastY::Int64
	Bombs::Int64
	MaxBomb::Int64
	MaxRadius::Int64
	Alive::Bool
	GameObject::Dict{UTF8String, UTF8String}
	Message::UTF8String
	Board::Array{UTF8String,2}
	
	Response() = new(0,0,"",0,0,0,0,0,0,0,false,Dict{UTF8String, UTF8String}(),"", Array(UTF8String,51,23))
end

function tparse(json::Dict{String,Any})
	r = Response()
	r.Turn = json["Turn"]
	r.TurnDuration = json["TurnDuration"]
	r.Name = json["Name"]
	r.X = json["X"]
	r.Y = json["Y"]
	r.LastX = json["LastX"]
	r.LastY = json["LastY"]
	r.Bombs = json["Bombs"]
	r.MaxBomb = json["MaxBomb"]
	r.MaxRadius = json["MaxRadius"]
	r.Alive = json["Alive"]
	r.GameObject["Name"] = json["GameObject"]["Name"]
	r.Message = json["Message"]
	
	for i = 1:51
		for j = 1:23
			r.Board[i,j] = json["Board"][i][j]["Name"]
		end
	end
	
	return r
end

try
	GAMEIP = "0.0.0.0"
	GAMEPORT = 40000
	player = Player(GAMEIP, GAMEPORT)

	print(typeof(player), "\n")

	recv_update(player)

	#gamestate = tparse(JSON.parse(readline(client)))

	#print(gamestate, "\n")

catch err
	print("connection ended with error $err\n")
end

